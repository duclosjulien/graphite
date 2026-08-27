#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <limits>
#include <iterator>
#include <cstdlib>
#include <stdexcept>

#include "curve.h"
#include "terminal.h"

Curve createSinus(
	const double amplitude,
	const double frequency,
	const double phase,
	const double offset,
	const char curveChar,
	const Color color) {

	Curve curve{};
	curve.curveType = CurveType::Sinus;

	curve.parameterValues = {
		amplitude,
		frequency,
		phase,
		offset
	};

	curve.parameterNames = {
		"amplitude",
		"frequency",
		"phase",
		"offset"
	};

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

Curve createCosinus(
	const double amplitude,
	const double frequency,
	const double phase,
	const double offset,
	const char curveChar,
	const Color color) {

	Curve curve{};
	curve.curveType = CurveType::Cosinus;

	curve.parameterValues = {
		amplitude,
		frequency,
		phase,
		offset
	};

	curve.parameterNames = {
		"amplitude",
		"frequency",
		"phase",
		"offset"
	};

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

Curve createTangent(
	const double amplitude,
	const double frequency,
	const double phase,
	const double offset,
	const char curveChar,
	const Color color) {

	Curve curve{};
	curve.curveType = CurveType::Tangent;

	curve.parameterValues = {
		amplitude,
		frequency,
		phase,
		offset
	};

	curve.parameterNames = {
		"amplitude",
		"frequency",
		"phase",
		"offset"
	};

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

Curve createPolynomial(const std::size_t degree, const char curveChar, const Color color) {
	Curve curve{};
	curve.curveType = CurveType::Polynomial;

	if (degree > maxPolynomialDegree) {
		throw std::invalid_argument("polynomial degree exceeds the supported maximum");
	}

	const std::size_t parameterCount = degree + 1;

	for (std::size_t i = 0; i < parameterCount; ++i)
		curve.parameterNames.push_back("parameter " + std::to_string(i + 1));

	curve.parameterValues.assign(parameterCount, 1.0);

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

Curve createExponential(
	const double verticalScale,
	const double base,
	const double horizontalScale,
	const double horizontalOffset,
	const double verticalOffset,
	const char curveChar,
	const Color color) {

	Curve curve{};
	curve.curveType = CurveType::Exponential;

	curve.parameterValues = {
		verticalScale,
		base,
		horizontalScale,
		horizontalOffset,
		verticalOffset
	};

	curve.parameterNames = {
		"verticalScale",
		"base",
		"horizontalScale",
		"horizontalOffset",
		"verticalOffset"
	};

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

Curve createLogarithmic(
	const double verticalScale,
	const double base,
	const double horizontalScale,
	const double horizontalOffset,
	const double verticalOffset,
	const char curveChar,
	const Color color) {

	Curve curve{};
	curve.curveType = CurveType::Logarithmic;

	curve.parameterValues = {
		verticalScale,
		base,
		horizontalScale,
		horizontalOffset,
		verticalOffset
	};

	curve.parameterNames = {
		"verticalScale",
		"base",
		"horizontalScale",
		"horizontalOffset",
		"verticalOffset"
	};

	curve.curveChar = curveChar;
	curve.color = color;

	return curve;
}

char getRandomLetter() {
	return static_cast<char>('A' + std::rand() % 26);
}

Color getRandomColor() {
	static constexpr Color curveColors[] = {
		Color::red,
		Color::grn,
		Color::ylw,
		Color::blu,
		Color::mag,
		Color::cyn,
		Color::_red,
		Color::_grn,
		Color::_ylw,
		Color::_blu,
		Color::_mag,
		Color::_cyn
	};

	return curveColors[static_cast<std::size_t>(std::rand()) % std::size(curveColors)];
}

int getRandomNumber(int min, int max) {
	if (min > max) {
		throw std::invalid_argument("min cannot be greater than max");
	}

	return min + std::rand() % (max - min + 1);
}

static double processSinus(const double x, const Curve& curve) {
	return curve.parameterValues.at(0) * std::sin(curve.parameterValues.at(1) * x + curve.parameterValues.at(2)) + curve.parameterValues.at(3);
}

static double processCosinus(const double x, const Curve& curve) {
	return curve.parameterValues.at(0) * std::cos(curve.parameterValues.at(1) * x + curve.parameterValues.at(2)) + curve.parameterValues.at(3);
}

static double processTangent(const double x, const Curve& curve) {
	return curve.parameterValues.at(0) * std::tan(curve.parameterValues.at(1) * x + curve.parameterValues.at(2)) + curve.parameterValues.at(3);

}

static double processPolynomial(const double x, const Curve& curve) {
	double y{};
	const std::size_t parameterCount = curve.parameterValues.size();
	for (std::size_t i = 0; i < parameterCount; ++i) {
		y += curve.parameterValues.at(i) * std::pow(x, i);
	}
	return y;
}

static double processExponential(const double x, const Curve& curve) {
	return curve.parameterValues.at(0) * std::pow(curve.parameterValues.at(1), curve.parameterValues.at(2) * x + curve.parameterValues.at(3)) + curve.parameterValues.at(4);
}

static double processLogarithmic(const double x, const Curve& curve) {
	const double a = curve.parameterValues.at(0);
	const double b = curve.parameterValues.at(1);
	const double c = curve.parameterValues.at(2);
	const double d = curve.parameterValues.at(3);
	const double e = curve.parameterValues.at(4);

	if (b <= 0.0 || b == 1.0) {
		return std::numeric_limits<double>::quiet_NaN();
	}

	const double argument = c * x + d;
	if (argument <= 0) {
		return std::numeric_limits<double>::quiet_NaN();
	}
	const double logarithm = std::log(argument) / std::log(b);

	return a * logarithm + e;
}

double process(const double x, const Curve& curve) {
	switch (curve.curveType) {
		case CurveType::Sinus:
			return processSinus(x, curve);

		case CurveType::Cosinus:
			return processCosinus(x, curve);

		case CurveType::Tangent:
			return processTangent(x, curve);

		case CurveType::Polynomial:
			return processPolynomial(x, curve);

		case CurveType::Exponential:
			return processExponential(x, curve);

		case CurveType::Logarithmic:
			return processLogarithmic(x, curve);

		case CurveType::None:
			return 0;
	}
	return 0;
}

void modifyParameter(
	Curve& curve,
	const double increment,
	const std::size_t parameterIndex
) {
	if (parameterIndex >= curve.parameterValues.size()) {
		return;
	}

	curve.parameterValues[parameterIndex] += increment;
}

void draw(const Curve& curve, const Graph& graph) {
	if (curve.curveType == CurveType::None) return;

	setColors({ graph.box.fillColors.background, curve.color });

	const int max = getWidth(graph.box.geometry) - 1;
	
	for (int x = 1; x <= max; ++x) {

		IntPoint boxPoint = { x, 0 }; 
		RealPoint graphPoint = boxToGraphCoord(boxPoint, graph);

		const double y = process(graphPoint.x, curve);

		if (!std::isfinite(y)) {
			continue;
		}

		RealPoint curvePoint = { graphPoint.x, y};
		IntPoint screenPoint = graphToBoxCoord(curvePoint, graph);

		if (screenPoint.x >= graph.box.geometry.topLeft.x + 1 && screenPoint.x <= graph.box.geometry.bottomRight.x - 1 &&
			screenPoint.y >= graph.box.geometry.topLeft.y + 1 && screenPoint.y <= graph.box.geometry.bottomRight.y - 1) {
			gotoxy(screenPoint.x + 1, screenPoint.y + 1);
			std::cout << curve.curveChar;
		}
	}
}

std::string toString(const Curve& curve, const int precision) {
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision);

	switch (curve.curveType) {
	case CurveType::None:
		return "";

	case CurveType::Sinus:
		ss << "y = " << curve.parameterValues.at(0)
		   << " * sin( " << curve.parameterValues.at(1)
		   << " x + " << curve.parameterValues.at(2)
		   << " ) + " << curve.parameterValues.at(3);
		break;

	case CurveType::Cosinus:
		ss << "y = " << curve.parameterValues.at(0)
		   << " * cos( " << curve.parameterValues.at(1)
		   << " x + " << curve.parameterValues.at(2)
		   << " ) + " << curve.parameterValues.at(3);
		break;

	case CurveType::Tangent:
		ss << "y = " << curve.parameterValues.at(0)
		   << " * tan( " << curve.parameterValues.at(1)
	       << " x + " << curve.parameterValues.at(2)
		   << " ) + " << curve.parameterValues.at(3);
		break;

	case CurveType::Polynomial:
		ss << "y = ";
		for (std::size_t i = 0; i < curve.parameterValues.size(); ++i) {
			if (i > 0) ss << " + ";
			ss << curve.parameterValues.at(i) << "*x^" << i;
		}
		break;

	case CurveType::Exponential:
		ss << "y = " << curve.parameterValues.at(0)
		   << " * " << curve.parameterValues.at(1)
		   << "^(" << curve.parameterValues.at(2)
		   << " * x + " << curve.parameterValues.at(3)
		   << ") + " << curve.parameterValues.at(4);
		break;

	case CurveType::Logarithmic:
		ss << "y = " << curve.parameterValues.at(0)
		   << " * log_" << curve.parameterValues.at(1)
		   << "( " << curve.parameterValues.at(2)
		   << " * x + " << curve.parameterValues.at(3)
		   << " ) + " << curve.parameterValues.at(4);
		break;
	}

	return ss.str();
}
