// LR06.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>


double f(double x)
{
	return log(1 + cos(x));
}

double calc(double a, double b, int n) {
	// ln(1 + cos(x)) = FYL2X(FLDLN2, 1 + cos(x))   
	int t = 0;
	const double c4 = 4.0; const double c2 = 2.0; const double c3 = 3.0;
	double x, h, S = 0;

	do {
		__asm {
			finit;	инициализация сопроцессора
			fld b;                                                            //b                                    
			fld a;                                                            //a                                    b                                    
			fsubp st(1), st;                                                  //b-a                                  
			fild n;                                                           //n                                    b-a                                  
			fdivp st(1), st;                                                  //(b-a)/n 
			fst h; h = (b - a) / n
			fld a;                                                            //a                                   (b-a)/n 
			faddp st(1), st;                                                  //a+(b-a)/n     
			fst x; x = a + (b - a) / n
			fld b;                                                           //b                                    a+(b-a)/n  
			fcomip st, st(1);
			jb error; b <= x
			ffreep  st;
			jmp find;

		find:
			fld x;                                                            //x
			fcos;                                                             //cos(x)                                                                      
			fld1;                                                             //1                                    cos(x)
			faddp st(1), st;                                                  //1+cos(x)
			fldln2;                                                           //ln(2)                                1+cos(x)
			fxch;                                                             //1+cos(x)                             ln(2)
			fyl2x;                                                            //ln(1+cos(x)) = f(x) 
			fld c4;                                                           //4                                    f(x) 
			fmulp st(1), st;                                                  //4*f(x) 
			fld S;                                                            //S                                    4*f(x) 
			faddp st(1), st;                                                  //S+4*f(x) 
			fstp S; S = S + f(x)
			fld h;                                                            //h 
			fld x;                                                            //x 
			faddp st(1), st;                                                  //x+h
			fst x; x = x + h
			fld b;                                                            //b                                    x+h
			fcomip st, st(1)                                                  //x+h
			jbe count;

			fcos;                                                             //cos(x+h) 
			fld1;                                                             //1                                    cos(x+h)
			faddp st(1), st;                                                  //1+cos(x+h)
			fldln2;                                                           //ln(2)                                1+cos(x+h)
			fxch;                                                             //1+cos(x+h)                             ln(2)
			fyl2x;                                                            //ln(1+cos(x+h)) = f(x+h)
			fld c2;                                                           //2                                    f(x+h) 
			fmulp st(1), st;                                                  //2*f(x+h)

			fld S;                                                            //S                                    2*f(x+h) 
			faddp st(1), st;                                                  //S+2*f(x+h) 
			fstp S; S = S + f(x + h)
			fld h;                                                            //h 
			fld x;                                                            //x 
			faddp st(1), st;                                                  //x+h
			fst x; x = x + h
			fld b;                                                            //b                                    x+h
			fcomip st, st(1)                                                  //x+h
			jbe count;
			ffree st;
			ffree st(1)
		    ffree st(2)                                                       //очищаем весь стек
			ffree st(3)
			ffree st(4)
			ffree st(5)
			ffree st(6)
			ffree st(7)
			jmp find;

		count:
			fld a;                                                            //a          
			fcos;                                                             //cos(a)                                                                      
			fld1;                                                             //1                                    cos(a)
			faddp st(1), st;                                                  //1+cos(a)
			fldln2;                                                           //ln(2)                                1+cos(a)
			fxch;                                                             //1+cos(a)                             ln(2)
			fyl2x;                                                            //ln(1+cos(a)) = f(a) 

			fld b;                                                            //b                                    f(a)
			fcos;                                                             //cos(b)                               f(a)                                       
			fld1;                                                             //1                                    cos(b)                  f(a)
			faddp st(1), st;                                                  //1+cos(b)                             f(a)
			fldln2;                                                           //ln(2)                                1+cos(b)                f(a)
			fxch;                                                             //1+cos(b)                             ln(2)                   f(a)
			fyl2x;                                                            //ln(1+cos(b)) = f(b)                  f(a)
			faddp st(1), st;                                                  //f(b)+f(a)

			fld S;                                                            //S                                    f(b)+f(a)
			faddp st(1), st;                                                  //S+f(b)+f(a)
			fld h;                                                            //h                                    S+f(b)+f(a)                 
			fld c3;                                                           //3                                    h                       S+f(b)+f(a)
			fdivp st(1), st;                                                  //h/3                                  S+f(b)+f(a)
			fmulp st(1), st;                                                  //(h / 3)*(S + f(a) + f(b))
			fstp S;
			jmp exit_0;

		error:
		exit_0:
			mov  t, 1;
		}
	} while (t == 0);
	return S;
}


int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа 6" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl << "Группа: 6113-020302D"
		<< std::endl << "Вариант 4" << std::endl << "Задание: "
		<< std::endl << "Вычислить логарифм от ln(1+cos(x)) по промежутку [0;pi/4]"
		<< std::endl;

	double a = 0, b = M_PI / 4, res, res_cpp;
	int n, n1;
	std::cout << "a = 0"
		<< std::endl << "b = pi/4" << std::endl;
	std::cout << "Введите числo интервалов:"
		<< std::endl << "N = ";
	std::cin >> n1;
	n = n1;
	std::cout << "Таблица значений : " << std::endl;
	std::cout.width(5);
	std::cout << "i";
	std::cout.width(15);
	std::cout << "xi";
	std::cout.width(25);
	std::cout << "f(xi)";
	std::cout.width(25);
	std::cout << "k";
	std::cout.width(25);
	std::cout << "k*f(xi)" << std::endl;

	double h = (b - a) / n;
	double x = a + h;
	double S = 0;
	int i = 0;

	std::cout.width(5);
	std::cout << i;
	std::cout.width(15);
	std::cout << x;
	std::cout.width(25);
	std::cout << f(x);
	std::cout.width(25);
	std::cout << 1;
	std::cout.width(25);
	std::cout << f(x) << std::endl;

	while (x < b)
	{
		S = S + 4 * f(x);
		x = x + h;
		i++;

		std::cout.width(5);
		std::cout << i;
		std::cout.width(15);
		std::cout << x;
		std::cout.width(25);
		std::cout << f(x);
		std::cout.width(25);
		std::cout << 4;
		std::cout.width(25);
		std::cout << 4 * f(x) << std::endl;

		if (x >= b) break;
		S = S + 2 * f(x);
		i++;
		x = x + h;

		std::cout.width(5);
		std::cout << i;
		std::cout.width(15);
		std::cout << x;
		std::cout.width(25);
		std::cout << f(x);
		std::cout.width(25);
		std::cout << 2;
		std::cout.width(25);
		std::cout << 2 * f(x) << std::endl;
	}
	S = (h / 3)*(S + f(a) + f(b));

	res_cpp = S;
	std::cout << "" << std::endl;
	std::cout << "Результат на C++: " << std::endl
		<< "I = ";
	std::cout.precision(5);
	std::cout << res_cpp << std::endl;

	n = n1;
	res = calc(a, b, n);
	std::cout << "Результат на ассемблере: " << std::endl
		<< "I = ";
	std::cout.precision(5);
	std::cout << res << std::endl;

	system("PAUSE");
	return 0;
}
