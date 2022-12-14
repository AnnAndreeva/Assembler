// LR03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
int error = 0;
int calc(int* arr, int n) {
	int min = arr[1], max = arr[0];
	__asm {
		xor	esi, esi; //подготовим регистр индекса в массиве
		mov	ebx, arr; //ebx указывает на начало массива
		mov ecx, n;// счётчик цикла по всем элементам массива
		jcxz exit_1; //завершить если длина массива 0	

		//минимальный i-нечётный
		mov	esi, 1; //<esi> = 1 для подсчета нечетных по индексу
		mov	edx, min;// присваиваем начальное минимальное значение
		begin_loop_min :
		    mov	eax, [ebx + esi * 4]; //определяем текущий элемент
			cmp	eax, edx;	//сравнение arr[i] и d
			jge	end_loop_min;	//если если больше или равно, то завершаем цикл
			jl  set_min;  // если меньше, то приравниваем

		set_min: 
			mov edx, eax; //< edx > = eax приравниваем для нахождения MIN
			jmp end_loop_min; //завершаем цикл

	    end_loop_min:
		    add	esi, 2;// переходим к следующему нечетному элементу
			cmp	esi, n; //сравниваем esi и длину массива
			jge return_min; //если больше или равно, то возвращаем MIN
			loop begin_loop_min;// повторяем цикл для всех элементов массива

		return_min: 
			or edx, edx; //сравнение d и 0
			je	error_; //ошибка деление на ноль, т.к. потом будем делить на MIN
			mov min, edx; //min = edx
			mov ecx, n; //счётчик цикла по всем элементам массива
			mov	esi, 0; //переходим на 0 элемент массива
			mov	edx, max; //присваиваем начальное максимальное значение
			jmp begin_loop_max; //переходим к подсчету MAX

		//максимальный i-чётный		
	    begin_loop_max:
		    mov	eax, [ebx + esi * 4]; //определяем текущий элемент			
			cmp	eax, edx;	//сравнение a[i] и d
			jle	end_loop_max;	//если меньше или равно, то завершаем цикл
			jg  set_max;  // если больше, то приравниваем

		set_max: 
			mov edx, eax; //< edx > = eax приравниваем для нахождения MAX
		    jmp end_loop_max; //завершаем цикл

	    end_loop_max:
		    add	esi, 2;// переходим к следующему четному элементу
			cmp	esi, n;// сравниваем esi и длину массива
		    jge return_max; //если больше или равно, то возвращаем MIN
			loop begin_loop_max; //повторяем цикл для всех элементов массива

		return_max: 
			mov max, edx; //max = edx
			mov ecx, n; //счётчик цикла по всем элементам массива
			mov	esi, 0; //переходим на 0 элемент массива
			jmp begin_loop; // переходим к подсчету a[i]

		// подсчет по правилу
		begin_loop:
		    mov	eax, [ebx + esi * 4];// определяем текущий элемент
			add eax, max; //<eax> = a[i] + MAX
			cdq;// eax == > edx:eax подготовка к делению
			idiv min; //<eax> = (a[i] + MAX) / MIN
			mov dword ptr[ebx + esi * 4], eax;// приравниваем элемент массива к eax
			inc	esi; //переходим к следующему элементу
			loop begin_loop; //повторяем цикл для всех элементов массива
			jmp exit_1; 

		error_: mov error, 1;
		exit_1:
	}	
	std::cout << "MIN(A(i-нечётный)) =  " << min << std::endl;
	std::cout << "MAX(A(i-чётный)) =  " << max << std::endl;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	std::cout << "Лабораторная работа 3" << std::endl
		<< "Выполнила: Андреева Анна" << std::endl << "Группа:6113-020302D"
		<< std::endl << "Вариант 57" << std::endl << "Задание:	Сформировать новый массив "
		<< std::endl << "из одномерного массива A={a[i]} целых чисел по следующему правилу:"
		<< std::endl << "    ai + MAX(A(i-чётный))" << std::endl << "ai = ---------------------"
		<< std::endl << "      MIN(A(i-нечётный))" << std::endl;
	int n;
	std::cout << "Размер массива N: " << std::endl;
	std::cin >> n;

	if (n <= 0) {
		printf("Неверная длина. Будет создан массив длинны 5\n");
		n = 5;
	}

	int* arr = new int[n];
	int* Carr = new int[n];
	
	

	std::cout << "Введите элементы массива: " << std::endl;
	for (int i = 0; i < n; i++)
		std::cin >> arr[i];

	for (int i = 0; i < n; i++)
		Carr[i] = arr[i];

	
	int max = Carr[0];
	int min = Carr[1];

	for (int i = 0; i < n ; i += 2) {
		if (max < Carr[i]) {
			max = Carr[i];
		}
	}
	for (int i = 1; i < n; i += 2) {
		if (min > Carr[i]) {
			min = Carr[i];
		}
	}
	calc(arr, n);
	if (error == 1) {
		printf("Деление на 0!(MIN = 0)");
	}
	else {
		printf("Результат на ассемблере:\n");
		for (int i = 0; i < n; i++)
			std::cout << arr[i] << "  ";
		printf("\nРезультат на C++:\n");
		for (int i = 0; i < n; i++)
			std::cout << (Carr[i] + max) / min << "  ";

	}
	printf("\n");
	system("PAUSE");
	return 0;
}

