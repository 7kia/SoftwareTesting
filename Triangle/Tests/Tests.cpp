// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Triangle.h"

BOOST_AUTO_TEST_SUITE(TriangleTests)

BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_zero)
{
	BOOST_CHECK_THROW(GetTriangleType(0.f, 1.f, 1.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(1.f, 0.f, 1.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(1.f, 1.f, 0.f), CTriangleSideIncorrect);
}

BOOST_AUTO_TEST_CASE(throw_exeption_if_triangle_is_degenerate)
{
	BOOST_CHECK_THROW(GetTriangleType(1.f, 2.f, 3.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(3.f, 1.f, 2.f), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(GetTriangleType(2.f, 3.f, 1.f), CTriangleSideIncorrect);
}



BOOST_AUTO_TEST_SUITE_END()