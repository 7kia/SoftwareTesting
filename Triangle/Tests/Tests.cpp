// Lab2-1Test.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "../Triangle.h"
#include <windows.h>

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

	TriangleTestsFixture_()
	{
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);

	}
};

BOOST_FIXTURE_TEST_SUITE(TriangleTestsFixture, TriangleTestsFixture_)

BOOST_AUTO_TEST_CASE(throw_exeption_if_side_less_zero)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 1.f, 0.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 0.f, 1.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(0.f, 1.f, 1.f), incorrectTriangle));

	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, 1.f, -1.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(1.f, -1.f, 1.f), incorrectTriangle));
	BOOST_CHECK(EqualTypes(GetTriangleType(-1.f, 1.f, 1.f), incorrectTriangle));

	BOOST_CHECK(EqualTypes(GetTriangleType(-1.f, -1.f, -1.f), incorrectTriangle));

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

BOOST_AUTO_TEST_CASE(triangle_with_additional_type)
{
	BOOST_CHECK(EqualTypes(GetTriangleType(3.f, 3.f, 3.f), { TrianlgeType::Equilateral
															, TrianlgeType::Isosceles }));
}

BOOST_AUTO_TEST_SUITE_END()// TriangleTestsFixture

BOOST_AUTO_TEST_SUITE_END()// TriangleTests