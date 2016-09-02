#include "stdafx.h"
#include "Triangle.h"


CTriangleSideIncorrect::CTriangleSideIncorrect(const std::string & message)
	: std::exception(message.c_str())
{
}


TrianlgeType GetTriangleType(float firstSide
							, float secondSide
							, float thirdSide)
{
	CheckCorrectnessSides(firstSide
						, secondSide
						, thirdSide);


	return TrianlgeType::Usual;
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