#include "stdafx.h"
#include "../Triangle.h"
#include <windows.h>

using namespace std;

BOOST_AUTO_TEST_SUITE(CTriangleCoverageTests)

struct CTriangleCoverageTestsFixture_
{
	CTriangle triangle;

	const float expectedFirst = 5;
	const float expectedSecond = 3;
	const float expectedThird = 4;

	CTriangleCoverageTestsFixture_()
	{
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
};


BOOST_FIXTURE_TEST_SUITE(CTriangleCoverageTests, CTriangleCoverageTestsFixture_)

/*
BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_or_equal_zero)
{
	//BOOST_CHECK_THROW(GetTriangleType(1.f, 1.f, 0.f), CTriangleSideIncorrect);
}

BOOST_AUTO_TEST_CASE(recognize_simple_triangle)
{
	//BOOST_CHECK(EqualTypes(GetTriangleType(2.f, 3.f, 4.f), { TrianlgeType::Simple }));
}
*/

BOOST_AUTO_TEST_SUITE(Sides)
	BOOST_AUTO_TEST_CASE(set_sides)
	{
		triangle.SetSide(expectedFirst, 0);
		triangle.SetSide(expectedSecond, 1);
		triangle.SetSide(expectedThird, 2);

		BOOST_CHECK(triangle.GetSide(0) == expectedFirst);
		BOOST_CHECK(triangle.GetSide(1) == expectedSecond);
		BOOST_CHECK(triangle.GetSide(2) == expectedThird);

	}
	BOOST_AUTO_TEST_SUITE(check_indexes)
		BOOST_AUTO_TEST_CASE(set_sides_check_indexes)
		{
			BOOST_CHECK_THROW(triangle.SetSide(expectedFirst, -1), runtime_error);
			BOOST_CHECK_THROW(triangle.SetSide(expectedFirst, 4), runtime_error);
		}
		BOOST_AUTO_TEST_CASE(get_sides_check_indexes)
		{
			BOOST_CHECK_THROW(triangle.GetSide(-1);, runtime_error);
			BOOST_CHECK_THROW(triangle.GetSide(4); , runtime_error);
		}
	BOOST_AUTO_TEST_SUITE_END()// check_indexes

	BOOST_AUTO_TEST_CASE(set_and_get_sides_check_index)
	{
		BOOST_CHECK_THROW(triangle.GetSide(-1), std::runtime_error);
		BOOST_CHECK_THROW(triangle.GetSide(3), std::runtime_error);

		BOOST_CHECK_THROW(triangle.SetSide(1.f, -1), std::runtime_error);
		BOOST_CHECK_THROW(triangle.SetSide(1.f, 3), std::runtime_error);
	}
	BOOST_AUTO_TEST_CASE(set_side_must_be_more_zero)
	{
		BOOST_CHECK_THROW(triangle.SetSide(0.f, 0), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(triangle.SetSide(0.f, 1), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(triangle.SetSide(0.f, 2), CTriangleSideIncorrect);

		BOOST_CHECK_THROW(triangle.SetSide(-1.f, 0), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(triangle.SetSide(-1.f, 1), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(triangle.SetSide(-1.f, 2), CTriangleSideIncorrect);
	}
BOOST_AUTO_TEST_SUITE_END()// Sides

BOOST_AUTO_TEST_SUITE(Constructor)
	BOOST_AUTO_TEST_CASE(check_default_constructor)
	{
		BOOST_CHECK(triangle.GetSide(0) == 0.f);
		BOOST_CHECK(triangle.GetSide(1) == 0.f);
		BOOST_CHECK(triangle.GetSide(2) == 0.f);
	}
	BOOST_AUTO_TEST_CASE(check_alternative_constructor)
	{
		CTriangle testTriangle(expectedFirst, expectedSecond, expectedThird);

		BOOST_CHECK(testTriangle.GetSide(0) == expectedFirst);
		BOOST_CHECK(testTriangle.GetSide(1) == expectedSecond);
		BOOST_CHECK(testTriangle.GetSide(2) == expectedThird);
	}
BOOST_AUTO_TEST_SUITE_END()// Constructor

BOOST_AUTO_TEST_SUITE(Square)
	BOOST_AUTO_TEST_CASE(get_square)
	{
		BOOST_CHECK_CLOSE(CTriangle(2.f, 2.f, 2.f).GetSquare(), 1.732f, 5.f);
		BOOST_CHECK_CLOSE(CTriangle(3.f, 4.f, 3.f).GetSquare(), 4.472f, 5.f);
		BOOST_CHECK_CLOSE(CTriangle(6.f, 4.f, 3.f).GetSquare(), 5.332f, 5.f);
	}
	BOOST_AUTO_TEST_CASE(get_square_throw_exception_if_triangle_is_degenerate)
	{
		BOOST_CHECK_THROW(CTriangle(1.f, 2.f, 3.f).GetSquare(), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(CTriangle(4.f, 20.f, 3.f).GetSquare(), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(CTriangle(5.f, 6.f, 16.f).GetSquare(), CTriangleSideIncorrect);
		BOOST_CHECK_THROW(CTriangle(50.f, 6.f, 1.f).GetSquare(), CTriangleSideIncorrect);
	}
BOOST_AUTO_TEST_SUITE_END()// Square

BOOST_AUTO_TEST_SUITE(Angle)
BOOST_AUTO_TEST_CASE(get_angle)
{
	BOOST_CHECK_CLOSE(CTriangle(6.f, 4.f, 3.f).GetAngle(0), 5.332f, 5.f);
	BOOST_CHECK_CLOSE(CTriangle(6.f, 4.f, 3.f).GetAngle(1), 5.332f, 5.f);
	BOOST_CHECK_CLOSE(CTriangle(6.f, 4.f, 3.f).GetAngle(2), 5.332f, 5.f);
}
BOOST_AUTO_TEST_CASE(get_angle_throw_exception_if_incorrect_get_index)
{
	BOOST_CHECK_THROW(CTriangle(6.f, 4.f, 3.f).GetAngle(-1), runtime_error);
	BOOST_CHECK_THROW(CTriangle(6.f, 4.f, 3.f).GetAngle(4), runtime_error);

}
BOOST_AUTO_TEST_CASE(get_angle_throw_exception_if_triangle_is_degenerate)
{
	BOOST_CHECK_THROW(CTriangle(50.f, 6.f, 1.f).GetAngle(0), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(50.f, 6.f, 1.f).GetAngle(1), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(50.f, 6.f, 1.f).GetAngle(2), CTriangleSideIncorrect);
}
BOOST_AUTO_TEST_SUITE_END()// Square



BOOST_AUTO_TEST_SUITE_END()// CTriangleCoverageTestsFixture_

BOOST_AUTO_TEST_SUITE_END()// CTriangleCoverageTests