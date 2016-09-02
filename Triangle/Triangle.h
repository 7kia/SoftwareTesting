#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <array>

static const float IN_DEGREES = 57.29f;
static const float EPSILON = 0.1f;

enum class TrianlgeType
{
		None
	,	Versatile// Разносторонний
	,	Isosceles// Равнобедренный
	,	Equilateral // Равносторонний
	,	AcuteAngled// Остроугольный
	,	Rectangular// Прямоугольный
	,	Obtuse// Тупоугольный
};

using TriangleSides = std::array<float, 3>;

namespace Messages
{
	static const std::string MESSAGE_SIDE_LESS_ZERO = "Side must be more zero";
	static const std::string MESSAGE_TRIANGLE_IS_DEGENERATE = "The triangle is degenerate";
}


class CTriangleSideIncorrect :
	public std::exception
{
public:
	CTriangleSideIncorrect(const std::string & message);// TODO : add parametres
};

// TODO : transfer to other place
template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

std::vector<TrianlgeType> GetTriangleType(float firstSide
										, float secondSide
										, float thirdSide);

void CheckCorrectnessSides(const TriangleSides & sides);

void CheckCorrectnessSide(float side);

void CheckSum(float firstSide
			, float secondSide
			, float thirdSide);

void AddTypeBySides(std::vector<TrianlgeType> & types, const TriangleSides & sides);
void AddTypeByAngles(std::vector<TrianlgeType>& types, const TriangleSides & sides);

// Get in degreeds
float GetAngleBetweenFirstAndSecondSides(float firstSide
										, float secondSide
										, float thirdSide);


