// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
//#include "../Triangle.h"
#include <Triangle.h>
#include <windows.h>

bool EqualTypes(const std::vector<TrianlgeType> & first, const std::vector<TrianlgeType> & second)
{
	for (const auto & element : second)
	{
		// Чтобы порядок не влиял на проверку
		auto iter = std::find(first.begin(), first.end(), element);
		if (iter == first.end())
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(CTriangle_GetTriangleType)

struct TriangleTestsFixture_
{
	std::vector<TrianlgeType> incorrectTriangle = { TrianlgeType::None };

	TriangleTestsFixture_()
	{
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
};

BOOST_FIXTURE_TEST_SUITE(TriangleTestsFixture, TriangleTestsFixture_)

BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_or_equal_zero)
{
	BOOST_CHECK_THROW(CTriangle(1.f, 1.f, 0.f).GetTriangleType(), CTriangleSideIncorrect);

	BOOST_CHECK_THROW(CTriangle(1.f, 0.f, 1.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(0.f, 1.f, 1.f).GetTriangleType(), CTriangleSideIncorrect);

	BOOST_CHECK_THROW(CTriangle(1.f, 1.f, -1.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(1.f, -1.f, 1.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(-1.f, 1.f, 1.f).GetTriangleType(), CTriangleSideIncorrect);

	BOOST_CHECK_THROW(CTriangle(-1.f, -1.f, -1.f).GetTriangleType(), CTriangleSideIncorrect);
}

BOOST_AUTO_TEST_CASE(throw_exeption_if_triangle_is_degenerate)
{
	BOOST_CHECK_THROW(CTriangle(1.f, 2.f, 3.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(4.f, 20.f, 3.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(5.f, 6.f, 16.f).GetTriangleType(), CTriangleSideIncorrect);
	BOOST_CHECK_THROW(CTriangle(50.f, 6.f, 1.f).GetTriangleType(), CTriangleSideIncorrect);
}

BOOST_AUTO_TEST_CASE(recognize_simple_triangle)
{
	BOOST_CHECK(EqualTypes(CTriangle(2.f, 3.f, 4.f).GetTriangleType(), { TrianlgeType::Simple }));
	BOOST_CHECK(EqualTypes(CTriangle(5.f, 2.f, 4.f).GetTriangleType(), { TrianlgeType::Simple }));
	BOOST_CHECK(EqualTypes(CTriangle(6.f, 4.f, 3.f).GetTriangleType(), { TrianlgeType::Simple }));
}

BOOST_AUTO_TEST_CASE(recognize_isosceles_triangle)
{
	BOOST_CHECK(EqualTypes(CTriangle(2.f, 2.f, 3.f).GetTriangleType(), { TrianlgeType::Isosceles } ));
	BOOST_CHECK(EqualTypes(CTriangle(3.f, 4.f, 4.f).GetTriangleType(), { TrianlgeType::Isosceles } ));
	BOOST_CHECK(EqualTypes(CTriangle(3.f, 4.f, 3.f).GetTriangleType(), { TrianlgeType::Isosceles } ));
}

BOOST_AUTO_TEST_CASE(recognize_equilateral_triangle)
{
	BOOST_CHECK(EqualTypes(CTriangle(2.f, 2.f, 2.f).GetTriangleType(), { TrianlgeType::Equilateral }));
	BOOST_CHECK(EqualTypes(CTriangle(30.f, 30.f, 30.f).GetTriangleType(), { TrianlgeType::Equilateral }));
}

BOOST_AUTO_TEST_CASE(recognize_isosceles_and_equilateral_triangle)
{
	BOOST_CHECK(EqualTypes(CTriangle(3.f, 3.f, 3.f).GetTriangleType(), { TrianlgeType::Equilateral
															, TrianlgeType::Isosceles }));
}

BOOST_AUTO_TEST_SUITE_END()// TriangleTestsFixture

BOOST_AUTO_TEST_SUITE_END()// CTriangle_GetTriangleType