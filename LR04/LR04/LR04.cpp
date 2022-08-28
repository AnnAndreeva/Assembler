// LR04.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
int error = 0;

double calc(double a, double b) {
	double res = 0; const double c5 = 1.25; const double c4 = 0.25; const double c = 5.0;
	__asm {
		                                                    //st0	                             st1
		finit;	инициализация сопроцессора
		fld 	qword ptr[b];                               //b
		fld 	qword ptr[a];                               //a                                  b
		fcomi 	st, st(1); сравниваем a и b
			ja	l_bigger; переход если a > b
			je  l_equals; если a = b
			jb	l_smaller; переход если a < b
			jmp	exit_1; переход на конец программы

		l_bigger : //sin^2(b)*cos(a), если a>b
		ffree st(1);                                    //a
		fcos;                                           //cos(a)
		fld c;                                          //5                                  cos(a)
		fmulp st(1), st;                                //5*cos(a)
		fld b;                                          //b                                  5*cos(a)
		fsin;                                           //sin(b)                             5*cos(a)
		fmul st, st;                                    //sin^2(b)                           5*cos(a)
		fadd st, st(1);                                 //sin^2(b)+5*cos(a)
		jmp	exit_1;

	l_equals:  //b^2/sqrt((a-1)), если a=b
		ffree st(1);                                    //a
		ffree st(1);                                    //a
		fld1;                                           //1                                a
		fxch st(1);                                     //a                                1
		fcomi st, st(1); сравниваем a и 1
		jle	error_; переход если 1 >= a
		fsub st, st(1);                                //a-1
		fsqrt;                                         //sqrt((a - 1))
		fld b;                                         //b                                 sqrt((a - 1))
		fmul st, st;                                   //b^2                               sqrt((a - 1))
		fdiv st, st(1);                                //b ^ 2 / sqrt((a - 1))
		jmp	exit_1;

	    l_smaller: //5/4 + 1/4*sqrt(b)-a^2, если a<b 
		ffreep st;                                    //b
		ftst; сравнение b с 0
		jg	error_; переход если b < 0
		fsqrt;                                         //sqrt(b)
		fld c4;                                        //1 / 4                             sqrt(b)
		fmulp st(1), st;                               //1 / 4 * sqrt(b)
		fld a;                                         //a                                 1 / 4 * sqrt(b)  
		fmul st, st;                                   //a ^ 2                             1 / 4 * sqrt(b)  
		fsubp st(1), st;                               //1 / 4 * sqrt(b) - a ^ 2
		fld c5;                                        //5/4                               1 / 4 * sqrt(b) - a ^ 2 
		faddp st(1), st(0);                            //5 / 4 + 1 / 4 * sqrt(b) - a ^ 2
        jmp	exit_1;	     
			
	error_: mov error, 1;
	exit_1: 
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа 4" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl << "Группа: 6113-020302D"
		<< std::endl << "Вариант 57" << std::endl << "Задание:"
		<< std::endl << "    sin^2(b)+5*cos(a), если a>b" << std::endl << "X = b^2/sqrt((a-1)), если a=b"
		<< std::endl << "    5/4 + 1/4*sqrt(b)-a^2, если a<b" << std::endl;
	double a, b;
	std::cout << "a = ";
	std::cin >> a;
	std::cout << "b = ";
	std::cin >> b;
	double res;
	double res_cpp;
	res = calc(a, b);
	if (error == 1) {
		printf("Ошибка!\n");
	}
	else {
		if (a > b) {
			res_cpp = pow(sin(b), 2) + 5 * cos(a);
		}
		else if (a == b) {
			res_cpp = pow(b, 2) / sqrt((a - 1));
		}
		else if (a < b) {
			res_cpp = 1.25 + 0.25 * sqrt(b) - pow(a, 2);
		}
		printf("Результат на ассемблере: ");
		std::cout.precision(5);
		std::cout << res << std::endl;
		printf("Результат на C++: ");
		std::cout.precision(5);
		std::cout << res_cpp << std::endl;
	}
	
	system("PAUSE");
	return 0;
}


