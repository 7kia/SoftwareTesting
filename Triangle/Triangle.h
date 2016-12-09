#pragma once

#include <stdexcept>
#include <vector>
#include <iostream>
#include <array>
#include <map>

enum class TrianlgeType
{
		None
	,	Simple// ��������������
	,	Isosceles// ��������������
	,	Equilateral // ��������������
};

static std::map<size_t, std::string> TrianlgeTypeStringPresentation = {
		{ int(TrianlgeType::None) , "�� �����������" }
	,	{ int(TrianlgeType::Equilateral) , "��������������" }
	,	{ int(TrianlgeType::Isosceles) , "��������������" }
	,	{ int(TrianlgeType::Simple) , "�������" }
};

std::string ToString(const std::vector<TrianlgeType>& types);


namespace Messages
{
	static std::string MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT = 
		"������� ����� ������ � �������� ����������.\
������ �����: triangle.exe a b c";
}


class CTriangleSideIncorrect :
	public std::exception
{
public:
	CTriangleSideIncorrect(const std::string & message);// TODO : add parametres
};

class CTriangle
{
public:
	CTriangle();
	CTriangle(float firstSide
			, float secondSide
			, float thirdSide);

//////////////////////////////////////////////////////////////////////
// Static data
public:
	static const size_t AMOUNT_SIDES = 3;

//////////////////////////////////////////////////////////////////////
// Methods
public:
	void						SetSide(float value, size_t index);
	float						GetSide(size_t index);

	std::vector<TrianlgeType>	GetTriangleType() const;

	float						GetSquare() const;
	float						GetAngle(size_t index) const;
private:
	void			CheckCorrecntnessType() const;
	void			CheckIndex(size_t index) const;
	void			CheckCorrectnessSide(float side) const;

	void			CheckCorrectnessSides() const;
	void			CheckSumSides(float firstSide
								, float secondSide
								, float thirdSide) const;
	void			AddTypeBySides(std::vector<TrianlgeType>& types) const;

//////////////////////////////////////////////////////////////////////
// Data
private:
	float			m_sides[3];
};


