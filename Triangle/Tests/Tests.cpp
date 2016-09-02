// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Triangle.h"

bool EqualTypes(const std::vector<TrianlgeType> & first, const std::vector<TrianlgeType> & second)
{
	for (const auto & element : second)
	{
		auto iter = std::find(first.begin(), first.end(), element);
		if (iter == first.end())
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(TriangleTests)

struct TriangleTestsFixture_
{
	std::vector<TrianlgeType> incorrectTriangle = { TrianlgeType::None };
	std::vector<TrianlgeType> isoscelesTriangle = { TrianlgeType::Isosceles };

	std::vector<TrianlgeType> isoscelesRectangularTriangle = { TrianlgeType::Rectangular
															, TrianlgeType::Isosceles
															};
	std::vector<TrianlgeType> equilateralTriangle = { TrianlgeType::Equilateral
													, TrianlgeType::Isosceles
													, TrianlgeType::AcuteAngled
													};

};

BOOST_FIXTURE_TEST_SUITE(TriangleTestsFixture, TriangleTestsFixture_)

BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_zero)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 1.f, 0.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 0.f, 1.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 1.f, 0.f), incorrectTriangle));
}

BOOST_AUTO_TEST_CASE(throw_exeption_if_triangle_is_degenerate)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 2.f, 3.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 1.f, 2.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 3.f, 1.f), incorrectTriangle));
}

BOOST_AUTO_TEST_CASE(recognize_isosceles_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 2.f, 3.f), { TrianlgeType::Isosceles } ));
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 2.f, 2.f), { TrianlgeType::Isosceles } ));
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 3.f, 2.f), { TrianlgeType::Isosceles } ));
}

BOOST_AUTO_TEST_CASE(recognize_equilateral_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 2.f, 2.f), { TrianlgeType::Equilateral }));
	BOOST_CHECK(EqualTypes(GetTriangleType(30.f, 30.f, 30.f), { TrianlgeType::Equilateral }));
}

BOOST_AUTO_TEST_CASE(recognize_versatile_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 3.f, 4.f), { TrianlgeType::Versatile } ));
	BOOST_CHECK(EqualTypes(GetTriangleType(4.f, 2.f, 3.f), { TrianlgeType::Versatile } ));
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 4.f, 2.f), { TrianlgeType::Versatile } ));
}

BOOST_AUTO_TEST_CASE(recognize_acute_angled_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 3.f, 3.f), { TrianlgeType::AcuteAngled }));
	BOOST_CHECK(EqualTypes(GetTriangleType(2.5f, 2.f, 2.f), { TrianlgeType::AcuteAngled }));
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 3.4f, 2.7f), { TrianlgeType::AcuteAngled }));
}

BOOST_AUTO_TEST_CASE(recognize_rectangular_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 4.f, 5.f), { TrianlgeType::Rectangular }));
	BOOST_CHECK(EqualTypes(GetTriangleType(5.f, 3.f, 4.f), { TrianlgeType::Rectangular }));
	BOOST_CHECK(EqualTypes(GetTriangleType(4.f, 5.f, 3.f), { TrianlgeType::Rectangular }));
}

BOOST_AUTO_TEST_CASE(recognize_obtuse_triangle)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 2.f, 3.f), { TrianlgeType::Obtuse }));
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 2.f, 2.f), { TrianlgeType::Obtuse }));
	BOOST_CHECK(EqualTypes(GetTriangleType(2.f,3.f, 2.f), { TrianlgeType::Obtuse }));
}

BOOST_AUTO_TEST_SUITE_END()// TriangleTestsFixture

BOOST_AUTO_TEST_SUITE_END()// TriangleTests