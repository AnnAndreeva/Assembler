#include "pch.h"
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

double calc (double x, double eps, int N) {
	int status;
	int k = 1;
	const double c4 = 4.0; const int c2 = 2; const int c3 = 3;
	double res;
	__asm {
		                                                    //st0	                      st1	             st2       	             st3         	st4         	st5
		mov	 ecx, N;
		finit;	инициализация сопроцессора
		fld qword ptr[eps];	                                //eps
		fld qword ptr[x];	                                //x	                          eps
		fldz;	                                            //sum = 0	                  x	                 eps
		fld qword ptr[x];	                                //x	                          sum                x	                     eps
		fld qword ptr[c4];	                                //4                           x	                 sum                     x	            eps
		fdivp st(1), st;	                                //s = x/4                     sum                x	                     eps
		jmp count;

	count: 
		fadd 	st(1), st;	                                //s	                          sum + s	         x	                     eps
		inc 	k; 	увеличиваем счётчик

		fmul st, st(2);	                                    //s*x	                      sum + s	          x	                     eps
		fmul st, st(2);	                                    //s*x^2	                      sum + s	          x	                     eps
		fld c4;	                                            //4                           s*x^2		          sum + s	             x	             eps
		fdivp st(1), st;	                                //s*x^2/4		              sum + s	          x	                     eps
		fild k;	                                            //k                           s*x^2/4		      sum + s	             x	             eps
		fild c2;	                                        //2                           k                   s*x^2/4                sum + s	     x	             eps
		fmulp st(1), st;	                                //2*k                         s*x^2/4             sum + s	             x	             eps
		fld1;	                                            //1                           2*k                 s*x^2/4                sum + s	     x	             eps
		fsubp st(1), st;	                                //2*k-1                       s*x^2/4             sum + s	             x	             eps
		fdivp st(1), st;	                                //s*x^2/(4*(2k-1))            sum + s	          x	                     eps

		fild k;	                                            //k                           s*x^2/(4*(2k-1))	  sum + s	             x	             eps
		fild c2;	                                        //2                           k                   s*x^2/(4*(2k-1))       sum + s	     x	             eps
		fmulp st(1), st;	                                //2*k                         s*x^2/(4*(2k-1))    sum + s	             x	             eps
		fild c3;	                                        //3                           2*k                 s*x^2/(4*(2k-1))       sum + s	     x	             eps
		fsubp st(1), st;	                                //2*k-3                       s*x^2/(4*(2k-1))             sum + s	             x	             eps
		fmulp st(1), st;	                                //s*x^2*(2*k-3)/(4*(2k-1))     sum + s	          x	                     eps
		fchs;

		jmp compare;


	compare:
		fldz;	                                            //0                           s                   sum + s	          x	             eps
		fadd st, st(1);	                                    //s                           s                   sum + s	          x	             eps
		fabs;                                               //|s|                         s                   sum + s	          x	             eps
		fcomp 	st(3); сравниваем погрешность с текущим членом ряда
		jl 	endcount; переход на конец, если достигли погрешность
		cmp 	ecx, k;	сравниваем достижение количества членов
		jg 	count;	переход на начало

		endcount:
		fadd 	st(1), st;	                                //s	                  sum + s	         x	             eps
		fstp 	res;	сброс с вершины стека текущего члена s
	    fstp 	res;	сохранение результата sum
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа 7" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl << "Группа: 6113-020302D"
		<< std::endl << "Вариант 4" << std::endl << "Задание: " 
		<< std::endl << "                                                                   (-1)^(n-1) * x^(2n-1)"
		<< std::endl << "Вычислить значение функции y  = (Сумма от 1 до бесконечности по n) ---------------------"
		<< std::endl << "                                                                        4^n * (2n-1)    "
		<< std::endl;

	double eps, x, res, res_cpp;
	int N;
	std::cout << "Введите x:"
		<< std::endl << "x = ";
	std::cin >> x;
	std::cout << "Введите eps:"
		<< std::endl << "eps = ";
	std::cin >> eps;
	std::cout << "Введите N (ограничение количества слагаемых сверху):"
		<< std::endl << "N = ";
	std::cin >> N;

	std::cout << "Таблица значений : " << std::endl;
	std::cout.width(5);
	std::cout << "n";
	std::cout.width(15);
	std::cout << "Sn";
	std::cout.width(25);
	std::cout << "Sn+1";
	std::cout.width(25);
	std::cout << "SUM";
	std::cout.width(25);
	std::cout << "k";
	std::cout.width(25);
	std::cout << "|Sn+1 - Sn|" << std::endl;

	double sum = 0.0,  sn, sn1;
	int k = 1;
	double coef = ((-1) * pow(x, 2)) * (2 * k - 3) / (4 * (2 * k - 1));
	sn = x / 4;
	std::cout.width(5);
	std::cout << k-1;
	std::cout.width(15);
	std::cout << sn;
	std::cout.width(25);
	std::cout << 0;
	std::cout.width(25);
	std::cout << 0;
	std::cout.width(25);
	std::cout << coef;
	std::cout.width(25);
	std::cout << fabs(sn) << std::endl;
	while ((fabs(sn) > eps) && (k <= N)){
		sum += sn;
		k++;
		sn1 = sn;

		std::cout.width(5);
		std::cout << k-1;
		std::cout.width(15);
		std::cout << sn1;
		std::cout.width(25);

		coef = ((-1) * pow(x, 2)) * (2 * k - 3) / (4 * (2 * k - 1));
		sn *= coef;

		std::cout << sn;
		std::cout.width(25);
		std::cout << sum;
		std::cout.width(25);
		std::cout << coef;
		std::cout.width(25);
		std::cout << fabs(sn-sn1) << std::endl;
	} 

	res_cpp = sum;
	std::cout << "Результат на C++: " << std::endl
		<< "y = ";
	std::cout.precision(5);
	std::cout << res_cpp << std::endl;

	res = calc(x, eps, N);
	std::cout << "Результат на ассемблере: " << std::endl
		<< "y = ";
	std::cout.precision(5);
	std::cout << res << std::endl;

	system("PAUSE");
	return 0;
}	
