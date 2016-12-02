#include "stdafx.h"
#include "Triangle.h"

using namespace std;

// TODO : transfer to other place
template <typename T>
bool IsBetween(const T& value, const T& lowerBound, const T& upperBound)
{
	return (value >= lowerBound) && (value <= upperBound);
}

CTriangleSideIncorrect::CTriangleSideIncorrect(const std::string & message)
	: std::exception(message.c_str())
{
}

std::string ToString(const std::vector<TrianlgeType>& types)
{
	std::string result;
	for (auto element : types)
	{
		result += TrianlgeTypeStringPresentation[size_t(element)];	
	}
	return result;
}

CTriangle::CTriangle()
{
	m_sides[0] = 0.f;
	m_sides[1] = 0.f;
	m_sides[2] = 0.f;
}

CTriangle::CTriangle(float firstSide
					, float secondSide
					, float thirdSide)
{
	SetSide(firstSide, 0);
	SetSide(secondSide, 1);
	SetSide(thirdSide, 2);
}

void CTriangle::SetSide(float value, size_t index)
{
	CheckIndex(index);
	CheckCorrectnessSide(value);
	m_sides[index] = value;
}

float CTriangle::GetSide(size_t index)
{
	CheckIndex(index);
	return m_sides[index];
}

void CTriangle::CheckIndex(size_t index)
{
	if (!IsBetween(index, size_t(0), AMOUNT_SIDES - 1))
	{
		throw std::runtime_error("Side have the index not exist");
	}
}

void CTriangle::CheckCorrectnessSide(float side)
{
	if (side <= 0.f)
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}


void CTriangle::CheckCorrectnessSides()
{
	CheckCorrectnessSide(m_sides[0]);
	CheckCorrectnessSide(m_sides[1]);
	CheckCorrectnessSide(m_sides[2]);

	CheckSumSides(m_sides[0], m_sides[1], m_sides[2]);
	CheckSumSides(m_sides[2], m_sides[0], m_sides[1]);
	CheckSumSides(m_sides[1], m_sides[2], m_sides[0]);
}

void CTriangle::CheckSumSides(float firstSide
						, float secondSide
						, float thirdSide)
{
	if (!((firstSide + secondSide) > thirdSide))
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}


std::vector<TrianlgeType> CTriangle::GetTriangleType()
{
	std::vector<TrianlgeType> types;

	CheckCorrectnessSides();

	AddTypeBySides(types);

	return types;
}


void CTriangle::AddTypeBySides(std::vector<TrianlgeType>& types)
{
	bool isEqualFirstAndSecond = (m_sides[0] == m_sides[1]);
	bool isEqualFirstAndThird = (m_sides[0] == m_sides[2]);
	bool isEqualSecondAndThird = (m_sides[1] == m_sides[2]);

	if (isEqualFirstAndSecond || isEqualFirstAndThird || isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Isosceles);
	}
	if (isEqualFirstAndSecond && isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Equilateral);
	}

	if (types.empty())
	{
		types.push_back(TrianlgeType::Simple);
	}
}