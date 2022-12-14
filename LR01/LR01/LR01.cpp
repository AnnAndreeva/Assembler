// LR01.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>

int error = 0;

int calc(int a, int b, int c) {
	int result = 0;
	
	__asm {
		mov eax, a;// <eax> = a
		mov ebx, b;// <ebx> = b
		mov ecx, c;// <ecx> = c
		or ecx, ecx;// проверка деления на 0
		je error_; 
		imul ecx;// <eax> = a * c
		sub eax, ebx;//<eax> = a * c - b
		dec eax;// <eax> = a * c - b - 1
		je error_; // проверка деления на 0
		push eax; //в стеке  a * c - b - 1
		mov eax, a;// <eax> = a
		cdq; //eax == > edx:eax
		mov ebx, 2; //<ebx> = 2
		imul ebx;//<eax> = a * 2
		idiv  ecx;// <eax> = a * 2 / c
		add eax, 25;//<eax> = a * 2 / c + 25
		pop ebx; //<ebx> = a * c - b - 1
		cdq; //eax == > edx:eax
		idiv ebx; //<eax> = (a * 2 / c + 25) / (a * c - b - 1)
		mov result, eax; //result = eax
		jmp exit_1;

	error_:
		mov error, 1;
	exit_1:
	}
	return result;
}

int main()
{
	system("color F0");
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа  1" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl 
		<< "Группа:6113-020302D"<< std::endl
		<< "Вариант 57" << std::endl 
		<< "Задание: (25 + 2*a/c)/(c*a – b – 1)" << std::endl;
	int a, b, c;
	std::cout << "a = ";
	std::cin >> a;
	printf("b = ");
	scanf_s("%d", &b);
	std::cout << "c = ";
	std::cin >> c;
	int res = calc(a, b, c);
	int res_cpp;
	if (error == 1)
	{
		std::cout << "Деление на 0!" << std::endl;
	}
	else {
		res_cpp = (25 + 2 * a / c) / (c * a - b - 1);
		printf("Результат на ассемблере: %d\n", res);
		printf("Результат на C++: %d\n", res_cpp);
	}	
	system("PAUSE");
	return 0;
}

