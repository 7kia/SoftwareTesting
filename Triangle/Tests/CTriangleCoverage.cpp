#include "stdafx.h"
#include "../Triangle.h"
#include <windows.h>


BOOST_AUTO_TEST_SUITE(CTriangleCoverageTests)

struct CTriangleCoverageTestsFixture_
{
	CTriangle triangle;

	const float expectedFirst = 1;
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


BOOST_AUTO_TEST_CASE(set_sides)
{
	triangle.SetSide(expectedFirst, 0);
	triangle.SetSide(expectedSecond, 1);
	triangle.SetSide(expectedThird, 2);

	BOOST_CHECK(triangle.GetSide(0) == expectedFirst);
	BOOST_CHECK(triangle.GetSide(1) == expectedSecond);
	BOOST_CHECK(triangle.GetSide(2) == expectedThird);

}

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

BOOST_AUTO_TEST_CASE(set_side_must_be_more_zero)
{
	BOOST_CHECK(false);
}

BOOST_AUTO_TEST_SUITE_END()// CTriangleCoverageTestsFixture_

BOOST_AUTO_TEST_SUITE_END()// CTriangleCoverageTests