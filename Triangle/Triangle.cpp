#include "Triangle.h"

TrianlgeType GetTriangleType(float firstSide
							, float secondSide
							, float thirdSide)
{
	CheckCorrectnessSides(firstSide
						, secondSide
						, thirdSide);


	return TrianlgeType();
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
		throw std::runtime_error("Side must be more zero");
	}
}
