#include "stdafx.h"
#include "Triangle.h"

using namespace std;

CTriangleSideIncorrect::CTriangleSideIncorrect(const std::string & message)
	: std::exception(message.c_str())
{
}


std::vector<TrianlgeType> GetTriangleType(float firstSide
										, float secondSide
										, float thirdSide)
{
	TriangleSides sides = { firstSide, secondSide, thirdSide };
	std::vector<TrianlgeType> types;


		CheckCorrectnessSides(sides);
	


	AddTypeBySides(types, sides);

	return types;
}

void CheckCorrectnessSides(const TriangleSides & sides)
{
	CheckCorrectnessSide(sides[0]);
	CheckCorrectnessSide(sides[1]);
	CheckCorrectnessSide(sides[2]);

	CheckSum(sides[0], sides[1], sides[2]);
	CheckSum(sides[2], sides[0], sides[1]);
	CheckSum(sides[1], sides[2], sides[0]);
}

void CheckCorrectnessSide(float side)
{
	if (side <= 0.f)
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}

void CheckSum(float firstSide
			, float secondSide
			, float thirdSide)
{
	if (!((firstSide + secondSide) > thirdSide))
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT);
	}
}

void AddTypeBySides(std::vector<TrianlgeType>& types, const TriangleSides & sides)
{
	bool isEqualFirstAndSecond = (sides[0] == sides[1]);
	bool isEqualFirstAndThird = (sides[0] == sides[2]);
	bool isEqualSecondAndThird = (sides[1] == sides[2]);

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



std::string ToString(const std::vector<TrianlgeType>& types)
{
	std::string result;
	for (auto element : types)
	{
		result += TrianlgeTypeStringPresentation[int(element)];	
	}
	return result;
}

CTriangle::CTriangle()
{
	SetSide(0.f, 0);
	SetSide(0.f, 1);
	SetSide(0.f, 2);
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

	m_sides[index] = value;
}

float CTriangle::GetSide(size_t index)
{
	CheckIndex(index);
	return m_sides[index];
}

void CTriangle::CheckIndex(size_t index)
{
	if (!IsBetween(index, size_t(0), AMOUNT_SIDES))
	{
		throw std::runtime_error("Side have the index not exist");
	}
}
