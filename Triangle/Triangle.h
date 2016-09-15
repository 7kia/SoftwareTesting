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
	,	Simple// Разносторонний
	,	Isosceles// Равнобедренный
	,	Equilateral // Равносторонний
};

using TriangleSides = std::array<float, 3>;

namespace Messages
{
	static std::string MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT = "Укажите длины сторон в качестве параметров. Формат ввода: triangle.exe a b c";
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


std::string ToString(const std::vector<TrianlgeType>& types);



