// LR05.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
int error = 0;
double calc(double a, double b, double eps) {
	int s = 0;
	const double c119 = 119.0; const double c32 = 32.0;
	const double c88 = 88.0; const double c2 = 2.0; const double c22 = 22.0; const double c36 = 36.0;
	const double c264 = 264.0; const double c8 = 8.0; const double c288 = 288.0; const double c198 = 198.0;
	do {
		__asm {
			finit;	инициализация сопроцессора
			fld 	qword ptr[b];	st(0) = b
			fld 	qword ptr[a];	st(0) = a
			fcomi 	st, st(1); сравниваем a и b
			jb	find_f; переход если a < b //jbe
			jae	exit_1; переход на конец программы если a >= b
			jmp	exit_1; переход на конец программы

			find_f : //f(x) = 119 + 32*x - 88*x^3 + 2*x^4 + 36*x^8 - 22*x^9       st                                 st(1)       
			fld c32;                                                          //32                                  a                                        
			fmulp st(1), st;                                                  //32*a              
			fld a;                                                            //a                                   32*a
			fmul st, st;                                                      //a*a                                 32*a
			fld a;                                                            //a                                   a*a                                    32*a
			fmulp st(1), st;                                                  //a^3                                 32*a
			fld c88;                                                          //88                                  a^3                                    32*a
			fmulp st(1), st;                                                  //88*a^3                              32*a
			fsubp st(1), st;                                                  //32*a-88*a^3 
			fld a;                                                            //a                                   32*a-88*a^3 
			fmul st, st;                                                      //a*a                                 32*a-88*a^3 
			fmul st, st;                                                      //a^4                                 32*a-88*a^3 
			fld c2;                                                           //2                                   a^4                                    32*a-88*a^3 
			fmulp st(1), st;                                                  //2*a^4                               32*a-88*a^3 
			faddp st(1), st;                                                  //32*a-88*a^3+2*a^4  
			fld a;                                                            //a                                   32*a-88*a^3+2*a^4  
			fmul st, st;                                                      //a*a                                 32*a-88*a^3+2*a^4  
			fmul st, st;                                                      //a^4                                 32*a-88*a^3+2*a^4  
			fmul st, st;                                                      //a^8                                 32*a-88*a^3+2*a^4  
			fld c36;                                                          //36                                  a^8                                    32*a-88*a^3+2*a^4 
			fmulp st(1), st;                                                  //36*a^8                              32*a-88*a^3+2*a^4
			faddp st(1), st;                                                  //32*a-88*a^3+2*a^4+36*a^8   
			fld a;                                                            //a                                   32*a-88*a^3+2*a^4+36*a^8   
			fmul st, st;                                                      //a*a                                 32*a-88*a^3+2*a^4+36*a^8   
			fmul st, st;                                                      //a^4                                 32*a-88*a^3+2*a^4+36*a^8   
			fmul st, st;                                                      //a^8                                 32*a-88*a^3+2*a^4+36*a^8 
			fld a;                                                            //a                                   a^8                                    32*a-88*a^3+2*a^4+36*a^8 
			fmulp st(1), st;                                                  //a^9                                 32*a-88*a^3+2*a^4+36*a^8 
			fld c22;                                                          //22                                  a^9                                    32*a-88*a^3+2*a^4+36*a^8 
			fmulp st(1), st;                                                  //22*a^9                              32*a-88*a^3+2*a^4+36*a^8 
			fsubp st(1), st;                                                  //32*a-88*a^3+2*a^4+36*a^8-22*a^9  
			fld c119;                                                         //119                                 32*a-88*a^3+2*a^4+36*a^8-22*a^9 
			faddp st(1), st;                                                  //32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			
			jmp find_df;

		    find_df://f'(x) = 32 - 264*x^2 + 8*x^3 + 288*x^7 - 198*x^8
			fld a;                                                            //a                                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                     //a*a                                  32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld c264;                                                         //264                                  a*a                                                                         32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //264*a^2                              32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fchs;                                                             //-264*a^2                             32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                   -264*a^2                                                                     32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a*a                                 -264*a^2                                                                     32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                    a*a                                       -264*a^2                          32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //a^3                                 -264*a^2                                                                     32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld c8;                                                           //8                                    a^3                                       -264*a^2                          32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //8*a^3                               -264*a^2                                  32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			faddp st(1), st;                                                  //-264*a^2+8*a^3                       32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                   -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a*a                                 -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a^4                                 -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                    a^4                                      -264*a^2+8*a^3                      32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a*a                                  a^4                                      -264*a^2+8*a^3                      32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //a^6                                 -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                   a^6                                       -264*a^2+8*a^3                       32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //a^7                                 -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld c288;                                                         //288                                 a^7                                       -264*a^2+8*a^3                     32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //288*a^7                             -264*a^2+8*a^3                            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			faddp st(1), st;                                                  //-264*a^2+8*a^3+288*a^7              32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld a;                                                            //a                                   -264*a^2+8*a^3+288*a^7                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a*a                                 -264*a^2+8*a^3+288*a^7                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a^4                                 -264*a^2+8*a^3+288*a^7                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmul st, st;                                                      //a^8                                 -264*a^2+8*a^3+288*a^7                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld c198;                                                         //198                                 a^8                                      -264*a^2+8*a^3+288*a^7              32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fmulp st(1), st;                                                  //198*a^8                             -264*a^2+8*a^3+288*a^7                    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fsubp st(1), st;                                                  //-264*a^2+8*a^3+288*a^7-198*a^8      32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			fld c32;                                                          //32                                  -264*a^2+8*a^3+288*a^7-198*a^8            32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			faddp st(1), st;                                                  //32-264*a^2+8*a^3+288*a^7-198*a^8    32*a-88*a^3+2*a^4+36*a^8-22*a^9+119
			
			jmp count;

		    count:                                                            //df                                       f      
			ftst; сравнение df с 0
			je	error_; переход если df = 0
			fxch st(1);                                                       //f                                       df  
			fdivr  st(1), st;                                                 //f                                       f/df
			fabs;                                                             //|f|                                     f/df
			fld eps;                                                          //eps                                      |f|                                   f/df
			fcomi st, st(1); сравнение eps с | f |
			jae exit_0; eps >= | f |
			ffreep st;                                                        //|f|                                      f/df 
			ffreep st;                                                        //f/df 
			fabs;
			fld a;                                                            //a                                       f/df  
			fsubp st(1), st;                                                  //f/df - a
            fchs;                                                             //a-f/df      	
			fst a; a = a - f / df
				jmp find_f;  повторяем программу

				error_: mov error, 1;
		    exit_1:
		    exit_0:
			mov  s, 1;
		}
	}while (s == 0);
	if (s == 1) {
		std::cout << "Результат на ассемблере: " << std::endl
		<< "x = ";
	   std::cout.precision(5);
	   std::cout << a << std::endl;
	}
	else
		std::cout << "" << std::endl;
		
}


int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа 5" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl << "Группа: 6113-020302D"
		<< std::endl << "Вариант 57" << std::endl << "Задание:"
		<< std::endl << "f(x) = 119 + 32*x - 88*x^3 + 2*x^4 + 36*x^8 - 22*x^9"
		<< std::endl << "Производная:"
		<< std::endl << "f'(x) = 32 - 264*x^2 + 8*x^3 + 288*x^7 - 198*x^8" << std::endl;

	double a, b, eps, res, res_cpp;

	std::cout << "Введите отрезок [a;b]:" << std::endl;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	std::cout << "Введите точность:"
		<< std::endl << "eps = ";
	std::cin >> eps;
	if (error == 1) {
		printf("Ошибка!\n");
	}
	if (a > b) // если пользователь перепутал границы отрезка, меняем их местами
	{
		double v = a;
		a = b;
		b = v;
	}
	double f, f1,fa,fb, df; int iter = 0;
	fa = 119 + 32 * a - 88 * pow(a, 3) + 2 * pow(a, 4) + 36 * pow(a, 8) - 22 * pow(a, 9);
	fb = 119 + 32 * b - 88 * pow(b, 3) + 2 * pow(b, 4) + 36 * pow(b, 8) - 22 * pow(b, 9);
	if (fa*fb > 0 ) // если знаки функции на краях отрезка одинаковые, то здесь нет корня
		std::cout << "На этом интервале корней нет" << std::endl;
	else
	{
			
		std::cout << "Таблица значений : " << std::endl;
		std::cout.width(5);
		std::cout << "x";
		std::cout.width(15);
		std::cout << "f(x)";
		std::cout.width(25);
		std::cout << "f'(x)";
		std::cout.width(30);
		std::cout << "f(x)/f'(x)" << std::endl;
		do {
			f = 119 + 32 * a - 88 * pow(a, 3) + 2 * pow(a, 4) + 36 * pow(a, 8) - 22 * pow(a, 9);
			df = 32 - 264 * pow(a, 2) + 8 * pow(a, 3) + 288 * pow(a, 7) - 198 * pow(a, 8);
			f1 = f; 
			std::cout.width(10);
			std::cout << a;
			std::cout.width(15);
			std::cout << f;
			std::cout.width(25);
			std::cout << df;
			std::cout.width(25);
			std::cout << fabs(f1/df) << std::endl;
			a = a - f / df;

		} while (fabs(f) > eps  && a < b);
        calc(a, b, eps);
		res_cpp = a;
		std::cout << "" << std::endl;
	    std::cout << "Результат на C++: " << std::endl
		<< "x = ";
	    std::cout.precision(5);
 	    std::cout << res_cpp << std::endl;
	}
	system("PAUSE");
	return 0;
}