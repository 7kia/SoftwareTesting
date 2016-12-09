# coding=utf-8
'''
	1. Напишите модульные тесты для функций calculateSquare(), calculateAngle(), isTriangle(), getType().
	2. В некоторых из этих функций есть ошибки, поэтому правильно написанные тесты должны падать (обнаруживать эти ошибки)
	3. Исправьте ошибки. Теперь тесты должны проходить (у всех тестов статус ОК).
	4. В указанных функциях есть места, написанные не очень эффективно. Перепишите их. 
	   Удостоверьтесь, что ничего не сломано — все ваши тесты проходят.
	5. Посчитайте покрытие тестами. Для этого используйте инструмент coverage https://pypi.python.org/pypi/coverage
'''

import unittest
import math

MESSAGE_AMOUNT_ARGUMENTS_IS_INCORRECT =  "Укажите длины сторон в качестве параметров." \
                                         "Формат ввода: triangle.exe a b c"
class Triangle:
    '''
		a, b, c — стороны треугольника
		класс позволяет определить, является ли это треугольником
		какого типа этот треугольник
		посчитать периметр и площадь
	'''

    def __init__(self, a, b, c):
        self.triangle = [a, b, c]

    def getA(self):
        return self.triangle[0]

    def getB(self):
        return self.triangle[1]

    def getC(self):
        return self.triangle[2]

    def calculatePerimeter(self):
        '''
			расчет периметра
		'''
        return sum(self.triangle)

    def calculateSquare(self):
        '''
			расчет площади по формуле Герона
		'''
        a = self.triangle[0]
        b = self.triangle[1]
        c = self.triangle[2]

        p = (a + b + c) / 2.0
        s = math.sqrt(p * (p - a) * (p - b) * (p - c))
        return s

    def calculateAngle(self, angle):
        '''
			Расчет угла по теореме косинусов.
			В качестве параметров передается alpha, beta, gamma — название угла, который нужно посчитать.
			Угол находится напротив соответствующей стороны (a, b, c)
			Возвращает величину угла в градусах
		'''

        if (not self.isTriangle()):
            return 0

        a = self.triangle[0]
        b = self.triangle[1]
        c = self.triangle[2]

        if (angle == 'alpha'):
            adj1 = b
            adj2 = c
            opp = a
        elif (angle == 'beta'):
            adj1 = a
            adj2 = c
            opp = b
        elif (angle == 'gamma'):
            adj1 = a
            adj2 = b
            opp = c
        else:
            return 0

        f = (adj1 ** 2 + adj2 ** 2 - opp ** 2) / (2.0 * adj1 * adj2)
        return math.degrees(math.acos(f))


    def isTriangle(self):
        '''
			Проверка, что треугольник с введенными сторонами вообще может существовать
		'''
        a = self.triangle[0]
        b = self.triangle[1]
        c = self.triangle[2]

        return a > 0 and \
               b > 0 and \
               c > 0 and \
               a < (b + c) and \
               b < (a + c)and \
               c < (a + b)

    def getType(self):
        '''
			Возвращает тип треугольника:
			common — просто треугольник
			isosceles — равнобедренный
			equilateral — равносторонний
			right — прямоугольный
		'''
        if (not self.isTriangle()):
            return 'degenerate'

        type = 'common'
        a = self.triangle[0]
        b = self.triangle[1]
        c = self.triangle[2]

        if ((a == b) and (a == c)):
            type = 'equilateral'
        elif (a == b) and (a != c):
            type = 'isosceles'
        elif (a == c) and (a != b):
            type = 'isosceles'
        elif (b == c) and (b != a):
            type = 'isosceles'
        elif (a ** 2 == b ** 2 + c ** 2):
            type = 'right'
        elif (b ** 2 == a ** 2 + c ** 2):
            type = 'right'
        elif (c ** 2 == a ** 2 + b ** 2):
            type = 'right'

        return type


class TriangleTest(unittest.TestCase):
    def setUp(self):
        print "Test started"

    def tearDown(self):
        print "Test finished"

    def testGetSides(self):
        t = Triangle(2, 3, 4)
        self.assertEqual(t.getA(), 2)
        self.assertEqual(t.getB(), 3)
        self.assertEqual(t.getC(), 4)

        t = Triangle(1, 1, 1)
        self.assertEqual(t.getA(), 1)
        self.assertEqual(t.getB(), 1)
        self.assertNotEqual(t.getC(), 4)


    def testCalculatePerimeter(self):
        t = Triangle(2, 3, 4)
        self.assertEqual(t.getA(), 2)
        self.assertEqual(t.getB(), 3)
        self.assertEqual(t.getC(), 4)

        t = Triangle(1, 1, 1)
        self.assertEqual(t.getA(), 1)
        self.assertEqual(t.getB(), 1)
        self.assertNotEqual(t.getC(), 4)

    # Проверяем, что на корректных значениях программа работает
    def testIsTriangle(self):
        t = Triangle(2, 3, 4)
        self.assertTrue(t.isTriangle())
        t = Triangle(1, 1, 1)
        self.assertTrue(t.isTriangle())
        t = Triangle(4, 4, 2)
        self.assertTrue(t.isTriangle())


    # Complete
    def testTriangle_is_degenerate_if_side_less_or_equal_zero(self):
        tList = { Triangle(1, 1, 0), Triangle(1, 0, 1), Triangle(0, 1, 1),
                  Triangle(1, 1, -1), Triangle(1, -1, 1),  Triangle(-1, 1, 1)}
        for t in tList:
            self.assertEquals(t.getType(), 'degenerate')
            self.assertFalse(t.isTriangle())

    # Complete
    def testTriangle_is_degenerate_if_sides_not_comply_other_rules(self):
        self.assertEquals(Triangle(1, 2, 3).getType(), 'degenerate')
        self.assertEquals(Triangle(4, 20, 3).getType(), 'degenerate')
        self.assertEquals(Triangle(5, 6, 16).getType(), 'degenerate')
        self.assertEquals(Triangle(50, 6, 1).getType(), 'degenerate')

    # Complete
    def testRecognize_common_triangle(self):
        self.assertEquals(Triangle(2, 3, 4).getType(), 'common')
        self.assertEquals(Triangle(5, 2, 4).getType(), 'common')
        self.assertEquals(Triangle(6, 4, 3).getType(), 'common')

    # Complete
    def testRecognize_isosceles_triangle(self):
        self.assertEquals(Triangle(2, 2, 3).getType(), 'isosceles')
        self.assertEquals(Triangle(3, 4, 4).getType(), 'isosceles')
        self.assertEquals(Triangle(3, 4, 3).getType(), 'isosceles')

    # Complete
    def testRecognize_equilateral_triangle(self):
        self.assertEquals(Triangle(2, 2, 2).getType(), 'equilateral')
        self.assertEquals(Triangle(30, 30, 30).getType(), 'equilateral')

    # Complete
    def testRecognize_right_triangle(self):
        self.assertEquals(Triangle(3, 4, 5).getType(), 'right')
        self.assertEquals(Triangle(5, 3, 4).getType(), 'right')
        self.assertEquals(Triangle(4, 5, 3).getType(), 'right')

    # Complete
    def testCalculate_square(self):
        t = Triangle(1, 1, 1)
        self.assertAlmostEqual(t.calculateSquare(), 0.4330127018922193)
        t = Triangle(3, 4, 5)
        self.assertAlmostEqual(t.calculateSquare(), 6.0)

    # Complete
    def testCalculate_angle(self):
        t = Triangle(2, 2, 2)
        self.assertAlmostEqual(t.calculateAngle('alpha'), 60)
        self.assertAlmostEqual(t.calculateAngle('beta'), 60)
        self.assertAlmostEqual(t.calculateAngle('gamma'), 60)

        t = Triangle(3, 5, 4)
        self.assertAlmostEqual(t.calculateAngle('alpha'), 36.86989764584401)
        self.assertAlmostEqual(t.calculateAngle('beta'), 90.0)
        self.assertAlmostEqual(t.calculateAngle('gamma'), 53.13010235415599)

        t = Triangle(3, 5, 3)
        self.assertAlmostEqual(t.calculateAngle('alpha'), 33.55730976192071)
        self.assertAlmostEqual(t.calculateAngle('beta'), 112.88538047615857)
        self.assertAlmostEqual(t.calculateAngle('gamma'), 33.55730976192071)

    # Complete
    def testCalculate_angle_get_zero_if_triangle_is_degenerate(self):
        t = Triangle(1, 2, 3)
        self.assertEqual(t.calculateAngle('alpha'), 0)
        self.assertEqual(t.calculateAngle('beta'), 0)
        self.assertEqual(t.calculateAngle('gamma'), 0)

    # Complete
    def testCalculate_angle_get_zero_if_incorrect_get_name_angle(self):
        self.assertEqual(Triangle(3, 5, 4).calculateAngle('unknow'), 0)


if __name__ == '__main__':
    unittest.main()