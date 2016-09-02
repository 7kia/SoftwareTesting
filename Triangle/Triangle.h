#pragma once

#include <stdexcept>

enum class TrianlgeType
{
		None
	,	Usual
	,	Isosceles// Равнобедренный
	,	Equilateral // Равносторонний
};

// TODO : transfer to other place
template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

TrianlgeType GetTriangleType(float firstSide
							, float secondSide
							, float thirdSide);

void CheckCorrectnessSides(float firstSide
							, float secondSide
							, float thirdSide);

void CheckCorrectnessSide(float side);

void CheckCorrectnessSides(float firstSide
	, float secondSide
	, float thirdSide);
