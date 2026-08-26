#pragma once

#include <string>
#include <vector>
#include <cstddef>

#include "colors.h"
#include "graph.h"

inline constexpr std::size_t maxPolynomialDegree = 7;

enum class CurveType {
	None, 			// 
	Sinus, 			// y = a * sin(b * x + c) + d
	Cosinus, 		// y = a * cos(b * x + c) + d
	Tangent,		// y = a * tan(b * x + c) + d
	Polynomial,		// y = SUM(a_i*x^i, i=0, i=n) = a_0 + a_1*x + a_2*x^2 + a_3*x^3 + ... + a_n*x^n   
	Exponential,	// y = a * b^(c * x + d) + e
	Logarithmic		// y = a * log_b(c * x + d) + e
};

struct Curve {
	CurveType curveType;
	std::vector<double> parameterValues;
	std::vector<std::string> parameterNames;
	char curveChar;
	Color color;
};
 
char getRandomLetter();
int getRandomNumber(int min, int max);
Color getRandomColor();


Curve createSinus(double amplitude = 1.0,
				  double frequency = 1.0,
				  double phase = 0.0,
				  double offset = 0.0,
				  char curveChar = getRandomLetter(), 
				  Color color = getRandomColor());

Curve createCosinus(double amplitude = 1.0,
					double frequency = 1.0,
					double phase = 0.0,
					double offset = 0.0,
					char curveChar = getRandomLetter(), 
					Color color = getRandomColor());

Curve createTangent(double amplitude = 1.0,
					double frequency = 1.0,
					double phase = 0.0,
					double offset = 0.0,
					char curveChar = getRandomLetter(), 
					Color color = getRandomColor());

Curve createPolynomial(
	std::size_t order = static_cast<std::size_t>(getRandomNumber(1, 5)),
	char curveChar = getRandomLetter(),
	Color color = getRandomColor()
);

Curve createExponential(double verticalScale = 1.0,
						double base = 2.0,
						double horizontalScale = 1.0,
						double horizontalOffset = 0.0,
						double verticalOffset = 0.0,
						char curveChar = getRandomLetter(), 
						Color color = getRandomColor());

Curve createLogarithmic(double verticalScale = 1.0,
						double base = 2.0,
						double horizontalScale = 1.0,
						double horizontalOffset = 0.0,
						double verticalOffset = 0.0,
						char curveChar = getRandomLetter(), 
						Color color = getRandomColor());


double process(double x, const Curve& curve);

void draw(const Curve& curve, const Graph& graph);

void modifyParameter(Curve& curve, double increment, std::size_t parameterIndex);

std::string toString(const Curve& curve, int precision = 2);
