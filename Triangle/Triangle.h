#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>

enum class TrianlgeType
{
		None
	,	Usual
	,	Isosceles// Равнобедренный
	,	Equilateral // Равносторонний
};

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

void CheckCorrectnessSides(float firstSide
							, float secondSide
							, float thirdSide);

void CheckCorrectnessSide(float side);

void CheckSum(float firstSide
			, float secondSide
			, float thirdSide);

