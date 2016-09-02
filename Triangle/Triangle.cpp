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
	std::vector<TrianlgeType> types;

	try
	{
		CheckCorrectnessSides(firstSide
							, secondSide
							, thirdSide);
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


	bool isEqualFirstAndSecond = (firstSide == secondSide);
	bool isEqualFirstAndThird = (firstSide == thirdSide);
	bool isEqualSecondAndThird = (secondSide == thirdSide);
	
	if (isEqualFirstAndSecond && isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Equilateral);
	}
	if (isEqualFirstAndSecond || isEqualFirstAndThird || isEqualSecondAndThird)
	{
		types.push_back(TrianlgeType::Isosceles);
	}
	
	if(types.empty())
	{
		types.push_back(TrianlgeType::Usual);// TOOD : fix name
	}

	return types;
}

void CheckCorrectnessSides(float firstSide
							, float secondSide
							, float thirdSide)
{
	CheckCorrectnessSide(firstSide);
	CheckCorrectnessSide(secondSide);
	CheckCorrectnessSide(thirdSide);

	CheckSum(firstSide, secondSide, thirdSide);
	CheckSum(thirdSide, firstSide, secondSide);
	CheckSum(secondSide, thirdSide, firstSide);

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