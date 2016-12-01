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
	for (const auto & element : types)
	{

		switch (element)
		{
		case TrianlgeType::None:
			result += "Не треугольник";// Is not triangle
			break;
		case TrianlgeType::Equilateral:
			result += "Равносторонний";//Equilateral 
			break;
		case TrianlgeType::Isosceles:
			result += "Равнобедренный";//Isosceles 
			break;
		case TrianlgeType::Simple:
			result += "Обычный";// Simple 
			break;
		default:
			break;
		}
	
	}
	return result;
}
