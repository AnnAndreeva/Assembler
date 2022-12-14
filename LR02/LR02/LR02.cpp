// LR02.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int error = 0;

int calc(int a, int b) {
	int result = 0;
	__asm {
		mov	eax, a;//< eax >= a
		mov	ebx, b;//< ebx >= b
		cmp	eax, ebx; //сравнение a и b
		jg	l_bigger; //переход если a > b
		jl	l_smaller;// переход если a < b
		mov	eax, -22;// < eax >= -22 если a = b
		jmp	exit_1; //переход на конец программы
		l_bigger :
		    or ebx, ebx; //сравнение b и 0
			je	error_; //ошибка деление на ноль
			cdq;// eax == > edx:eax
			idiv ebx; //<eax> = a / b
			add eax, 22; //<eax> = a / b + 22
			jmp	exit_1;
		l_smaller :
		    or ebx, ebx; //сравнение b и 0
			je	error_; //ошибка деление на ноль
			imul 	eax; //<eax> = a * a
			jo	error_; //ошибка переполнение
			add eax, -22; //<eax> = a * a - 22
			cdq;// eax == > edx:eax
			idiv ebx; //< eax> = (a * a - 22) / b
			jmp	exit_1;
		error_:
			mov error, 1;
		exit_1:
			mov result, eax;
	}
	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа  2" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl
		<< "Группа:6113-020302D"<< std::endl 
		<< "Вариант 57" << std::endl 
		<< "Задание:"<< std::endl 
		<< "    a/b+22, если a>b" << std::endl 
		<< "X = -22, если a=b"<< std::endl 
		<< "    (a*a-22)/b, если a<b" << std::endl;
	int a, b;
	std::cout << "a = ";
	std::cin >> a;
	printf("b = ");
	scanf_s("%d", &b);
	int res = calc(a, b);
	int res_cpp;

	if (error == 1)
	{
		std::cout << "Деление на 0!" << std::endl;
	}
	else {
		if (a > b) {
			res_cpp = a / b + 22;
		}
		else if (a == b) {
			res_cpp = -22;
		}
		else if (a < b) {
			res_cpp = (a * a - 22) / b;
		}
		printf("Результат на ассемблере: %d\n", res);
	    printf("Результат на C++: %d\n", res_cpp);
	}	
	system("PAUSE");
	return 0;
}
