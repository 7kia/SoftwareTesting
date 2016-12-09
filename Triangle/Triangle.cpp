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

void CTriangle::CheckCorrecntnessType() const
{
	auto types = GetTriangleType();

	if (types == std::vector<TrianlgeType>(1, TrianlgeType::None))
	{
		throw std::runtime_error("The triangle is degenerate, it not have square");
	}

}

void CTriangle::CheckIndex(size_t index) const
{
	if (!IsBetween(index, size_t(0), AMOUNT_SIDES - 1))
	{
		throw std::runtime_error("Side have the index not exist");
	}
}

void CTriangle::CheckCorrectnessSide(float side) const
{
	if (side <= 0.f)
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}


void CTriangle::CheckCorrectnessSides() const
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
							, float thirdSide) const
{
	if (!((firstSide + secondSide) > thirdSide))
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}


std::vector<TrianlgeType> CTriangle::GetTriangleType() const
{
	std::vector<TrianlgeType> types;

	CheckCorrectnessSides();

	AddTypeBySides(types);

	return types;
}

float CTriangle::GetSquare() const
{
	CheckCorrecntnessType();

	float first = m_sides[0];
	float second = m_sides[1];
	float third = m_sides[2];


	float selfPerimeter = (first + second + third) / 2.f;
	
	return sqrt(selfPerimeter * (selfPerimeter - first)
								* (selfPerimeter - second)
								* (selfPerimeter - third)
				);
}

float CTriangle::GetAngle(size_t index) const
{
	CheckIndex(index);
	CheckCorrecntnessType();

	float first = m_sides[0];
	float second = m_sides[1];
	float third = m_sides[2];

	switch (index)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
	/*
	if (angle == 'alpha') :
			adj1 = b
			adj2 = c
			opp = a
			elif(angle == 'beta') :
			adj1 = a
			adj1 = c
			opp = b
			elif(angle == 'gamma') :
			adj1 = a
			adj2 = b
			opp = c
		else:
	return False

		f = (adj1 ** 2 + adj2 ** 2 - opp ** 2) / (2.0 * adj1 * adj2)
		return math.degrees(math.acos(f))
	*/
		

	return 0.0f;
}


void CTriangle::AddTypeBySides(std::vector<TrianlgeType>& types) const
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