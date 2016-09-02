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

	try
	{
		CheckCorrectnessSides(sides);
	}
	catch (const CTriangleSideIncorrect & exeption)
	{
		cout << exeption.what() << endl;
		types.push_back(TrianlgeType::None);
		return types;
	}
	catch (const exception & exeption)// TODO : fix
	{
		throw;// Отправка исключения наружу
	}


	AddTypeBySides(types, sides);
	AddTypeByAngles(types, sides);

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
		throw CTriangleSideIncorrect(Messages::MESSAGE_SIDE_LESS_ZERO);
	}
}

void CheckSum(float firstSide
			, float secondSide
			, float thirdSide)
{
	if (!((firstSide + secondSide) > thirdSide))
	{
		throw CTriangleSideIncorrect(Messages::MESSAGE_TRIANGLE_IS_DEGENERATE);
	}
}

void AddTypeBySides(std::vector<TrianlgeType>& types, const TriangleSides & sides)
{
	bool isEqualFirstAndSecond = (sides[0] == sides[1]);
	bool isEqualFirstAndThird = (sides[0] == sides[2]);
	bool isEqualSecondAndThird = (sides[1] == sides[2]);

	if (isEqualFirstAndSecond && isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Equilateral);
	}
	if (isEqualFirstAndSecond || isEqualFirstAndThird || isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Isosceles);
	}

	if (types.empty())
	{
		types.push_back(TrianlgeType::Versatile);
	}
}

void AddTypeByAngles(std::vector<TrianlgeType>& types, const TriangleSides & sides)
{
	float angleBetweenFirstAndSecond = GetAngleBetweenFirstAndSecondSides(sides[0], sides[1], sides[2]);
	float angleBetweenSecondAndThird = GetAngleBetweenFirstAndSecondSides(sides[1], sides[2], sides[0]);
	float angleBetweenFirstAndThird = GetAngleBetweenFirstAndSecondSides(sides[0], sides[2], sides[1]);


	if ((IsBetween(angleBetweenFirstAndSecond, 90.f - EPSILON, 90.f + EPSILON))
		|| (IsBetween(angleBetweenSecondAndThird, 90.f - EPSILON, 90.f + EPSILON))
		|| (IsBetween(angleBetweenFirstAndThird, 90.f - EPSILON, 90.f + EPSILON)))
	{
		types.push_back(TrianlgeType::Rectangular);
	}
	else if ((angleBetweenFirstAndSecond > 90.f)
		|| (angleBetweenSecondAndThird > 90.f)
		|| (angleBetweenFirstAndThird > 90.f))
	{
		types.push_back(TrianlgeType::Obtuse);
	}
	else
	{
		types.push_back(TrianlgeType::AcuteAngled);
	}
}

float GetAngleBetweenFirstAndSecondSides(float firstSide
										, float secondSide
										, float thirdSide)
{
	return acos((firstSide * firstSide + secondSide * secondSide - thirdSide * thirdSide)
				/ (2.f * firstSide * secondSide)) * IN_DEGREES;
}
