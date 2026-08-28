#include <fstream>
#include <string>
#include <charconv>
#include <cctype>
#include <cmath>
#include <utility>
#include <optional>
#include <iostream>
#include <string_view>

#include "curvePersistence.h"
#include "application.h"

namespace {
    std::string trim(std::string_view text) {
        auto start = text.find_first_not_of(" \t\r\n");

        if (start == std::string_view::npos) {
            return {};
        }

        auto end = text.find_last_not_of(" \t\r\n");

        return std::string{
            text.substr(start, end - start + 1)
        };
    }

    bool readNextNonEmptyLine(std::istream& input, std::string& line) {
        while (std::getline(input, line)) {
            if (!trim(line).empty()) {
                return true;
            }
        }

        return false;
    }

    std::optional<std::string> parseField(std::string_view line, std::string_view expectedName) {
        constexpr char delimiter = '=';

        const std::size_t delimiterPosition = line.find(delimiter);

        if (delimiterPosition == std::string_view::npos) {
            return std::nullopt;
        }

        const std::string name = trim(line.substr(0, delimiterPosition));
        const std::string value = trim(line.substr(delimiterPosition + 1));

        if (name != expectedName || value.empty()) {
            return std::nullopt;
        }

        return value;
    }

    std::optional<std::size_t> parseSize(std::string_view text) {
        if (text.empty()) {
            return std::nullopt;
        }

        std::size_t size{};

        const char* const begin = text.data();
        const char* const end = text.data() + text.size();

        const auto [ptr, ec] = std::from_chars(begin, end, size);

        if (ec != std::errc{} || ptr != end) {
            return std::nullopt;
        }

        return size;
    }

    std::optional<int> parseInteger(std::string_view text) {
        if (text.empty()) {
            return std::nullopt;
        }

        int value{};

        const char* const begin = text.data();
        const char* const end = text.data() + text.size();

        const auto [ptr, ec] = std::from_chars(begin, end, value);

        if (ec != std::errc{} || ptr != end) {
            return std::nullopt;
        }

        return value;
    }

    std::optional<double> parseDouble(std::string_view text) {
        if (text.empty()) {
            return std::nullopt;
        }

        double value{};

        const char* const begin = text.data();
        const char* const end = text.data() + text.size();

        const auto [ptr, ec] = std::from_chars(begin, end, value);

        if (ec != std::errc{} || ptr != end) {
            return std::nullopt;
        }

        if (!std::isfinite(value)) {
            return std::nullopt;
        }

        return value;
    }

    std::optional<char> parseChar(std::string_view text) {
        const std::string value = trim(text);

        if (value.size() != 1) {
            return std::nullopt;
        }

        const char character = value.front();

        if (!std::isprint(static_cast<unsigned char>(character))) {
            return std::nullopt;
        }

        return character;
    }

    std::optional<Color> parseColor(std::string_view text) {
        const auto value = parseInteger(text);

        if (!value) {
            return std::nullopt;
        }

        constexpr int firstColor = static_cast<int>(Color::blk);
        constexpr int lastColor = static_cast<int>(Color::_wht);

        if (*value < firstColor || *value > lastColor) {
            return std::nullopt;
        }

        return static_cast<Color>(*value);
    }

    std::optional<std::vector<double>> parseCoefficients(std::string_view text) {
        const std::string value = trim(text);

        if (
            value.size() < 2 ||
            value.front() != '{' ||
            value.back() != '}'
        ) {
            return std::nullopt;
        }

        const std::string content = trim(
            std::string_view{value}.substr(1, value.size() - 2)
        );

        std::vector<double> coefficients;

        if (content.empty()) {
            return coefficients;
        }

        const std::string_view values{content};
        std::size_t start = 0;

        while (start < values.size()) {
            const std::size_t comma = values.find(',', start);

            const std::string_view tokenView =
                comma == std::string_view::npos
                    ? values.substr(start)
                    : values.substr(start, comma - start);

            const std::string token = trim(tokenView);

            if (token.empty()) {
                return std::nullopt;
            }

            const auto coefficient = parseDouble(token);

            if (!coefficient) {
                return std::nullopt;
            }

            coefficients.push_back(*coefficient);

            if (comma == std::string_view::npos) {
                break;
            }

            start = comma + 1;

            if (start == values.size()) {
                return std::nullopt; // Trailing comma
            }
        }

        return coefficients;
    }

    std::optional<CurveType> parseCurveType(std::string_view text) {
        if (text == "sin") {
            return CurveType::Sinus;
        }

        if (text == "cos") {
            return CurveType::Cosinus;
        }

        if (text == "tan") {
            return CurveType::Tangent;
        }

        if (text == "exp") {
            return CurveType::Exponential;
        }

        if (text == "log") {
            return CurveType::Logarithmic;
        }

        if (text == "pol") {
            return CurveType::Polynomial;
        }

        return std::nullopt;
    }

    bool hasValidCoefficientCount(CurveType type, std::size_t count) {
        switch (type) {
            case CurveType::Sinus: {
                return count == 4;
            }
            case CurveType::Cosinus: {
                return count == 4;
            }
            case CurveType::Tangent: {
                return count == 4;
            }
            case CurveType::Exponential: {
                return count == 5;
            }
            case CurveType::Logarithmic: {
                return count == 5;
            }
            case CurveType::Polynomial: {
                return count >= 1 && count <= maxPolynomialDegree + 1;
            }
            case CurveType::None: {
                return false;
            }
            default: { return false; }
        }
    }

    std::optional<Curve> buildCurve(CurveType type, const std::vector<double>& coefficients, char drawingCharacter, Color color) {
        if (!hasValidCoefficientCount(type, coefficients.size())) {
            return std::nullopt;
        }

        switch (type) {
            case CurveType::Sinus: {
                return createSinus(
                    coefficients[0],
                    coefficients[1],
                    coefficients[2],
                    coefficients[3],
                    drawingCharacter,
                    color);
            }
            case CurveType::Cosinus: {
                return createCosinus(
                    coefficients[0],
                    coefficients[1],
                    coefficients[2],
                    coefficients[3],
                    drawingCharacter,
                    color);
            }
            case CurveType::Tangent: {
                return createTangent(
                    coefficients[0],
                    coefficients[1],
                    coefficients[2],
                    coefficients[3],
                    drawingCharacter,
                    color);
            }
            case CurveType::Exponential: {
                return createExponential(
                    coefficients[0],
                    coefficients[1],
                    coefficients[2],
                    coefficients[3],
                    coefficients[4],
                    drawingCharacter,
                    color);
            }
            case CurveType::Logarithmic: {
                return createLogarithmic(
                    coefficients[0],
                    coefficients[1],
                    coefficients[2],
                    coefficients[3],
                    coefficients[4],
                    drawingCharacter,
                    color);
            }
            case CurveType::Polynomial: {
                return createPolynomial(coefficients, drawingCharacter, color);
            }
            case CurveType::None: {
                return std::nullopt;
            }
            default: { return std::nullopt;}
        }
    }

}

CurveLoadResult loadCurves(std::istream& input) {
    std::string line{};

    if (!readNextNonEmptyLine(input, line)) {
        return {.curves = {}, .error = "missing n_curves field"};
    }

    const auto countText = parseField(line, "n_curves");

    if (!countText) {
        return {.curves = {}, .error = "invalid n_curves field"};
    }

    const auto curveCount = parseSize(*countText);

    if (!curveCount) {
        return {.curves = {}, .error = "invalid curve count"};
    }

    std::vector<Curve> curves;

    for (std::size_t i = 0; i < *curveCount; ++i) {
        // [curve]
        if (
            !readNextNonEmptyLine(input, line) ||
            trim(line) != "[curve]"
        ) {
            return {.curves = {}, .error = "missing [curve] section"};
        }

        // type
        if (!readNextNonEmptyLine(input, line)) {
            return {.curves = {}, .error = "missing curve type"};
        }

        auto field = parseField(line, "type");

        if (!field) {
            return {.curves = {}, .error = "invalid curve type field"};
        }

        const auto type = parseCurveType(*field);

        if (!type) {
            return {.curves = {}, .error = "unknown curve type"};
        }

        // coefficients
        if (!readNextNonEmptyLine(input, line)) {
            return {.curves = {}, .error = "missing coefficients"};
        }

        field = parseField(line, "coef");

        if (!field) {
            return {.curves = {}, .error = "invalid coefficient field"};
        }

        const auto coefficients = parseCoefficients(*field);

        if (!coefficients) {
            return {.curves = {}, .error = "invalid coefficients"};
        }

        // character
        if (!readNextNonEmptyLine(input, line)) {
            return {.curves = {}, .error = "missing character"};
        }

        field = parseField(line, "char");

        if (!field) {
            return {.curves = {}, .error = "invalid character field"};
        }

        const auto drawingCharacter = parseChar(*field);

        if (!drawingCharacter) {
            return {.curves = {}, .error = "invalid drawing character"};
        }

        // color
        if (!readNextNonEmptyLine(input, line)) {
            return {.curves = {}, .error = "missing color"};
        }

        field = parseField(line, "color");

        if (!field) {
            return {.curves = {}, .error = "invalid color field"};
        }

        const auto color = parseColor(*field);

        if (!color) {
            return {.curves = {}, .error = "invalid color"};
        }

        const auto curve = buildCurve(
            *type,
            *coefficients,
            *drawingCharacter,
            *color
        );

        if (!curve) {
            return {.curves = {}, .error = "invalid curve parameters"};
        }

        curves.push_back(*curve);
    }

    return {.curves = std::move(curves), .error = {}};
}
