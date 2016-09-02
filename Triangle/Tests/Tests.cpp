// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Triangle.h"

BOOST_AUTO_TEST_SUITE(TriangleTests)

struct TriangleTestsFixture_
{
	std::vector<TrianlgeType> incorrectTriangle = { TrianlgeType::None };
};

BOOST_FIXTURE_TEST_SUITE(TriangleTestsFixture, TriangleTestsFixture_)

BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_zero)
{
	/*
	BOOST_CHECK_THROW(GetTriangleType(0.f, 1.f, 1.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(1.f, 0.f, 1.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(1.f, 1.f, 0.f), CTriangleSideIncorrect);

	*/

	BOOST_CHECK(GetTriangleType(1.f, 1.f, 0.f) == incorrectTriangle);
	BOOST_CHECK(GetTriangleType(1.f, 0.f, 1.f) == incorrectTriangle);
	BOOST_CHECK(GetTriangleType(1.f, 1.f, 0.f) == incorrectTriangle);

}

BOOST_AUTO_TEST_CASE(throw_exeption_if_triangle_is_degenerate)
{
	BOOST_CHECK(GetTriangleType(1.f, 2.f, 3.f) == incorrectTriangle);
	BOOST_CHECK(GetTriangleType(3.f, 1.f, 2.f) == incorrectTriangle);
	BOOST_CHECK(GetTriangleType(2.f, 3.f, 1.f) == incorrectTriangle);
}

BOOST_AUTO_TEST_CASE(recognize_usual_triangle)// TODO : fix name the test
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(recognize_isosceles_triangle)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_CASE(recognize_equilateral_triangle)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()// TriangleTestsFixture

BOOST_AUTO_TEST_SUITE_END()// TriangleTests