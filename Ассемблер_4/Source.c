#include <stdio.h>
#include <locale.h>
#include <ctype.h>


short int** asm(char* A, char* B)
{
	short int* C[sizeof(A)/sizeof(A[0])];
	__asm { //-2 - (2 - (x + 4)*z) / (y + 6);
		//Вычисление числителя
		mov al, x; //Поместить x в AL
		cbw; //Расширить AL со знаком до слова
		add ax, 4; //Вычислить x + 4 
		imul z; //Вычислить z(x + 4) 
		neg ax; //Поменять знак младшего слово
		neg dx; //Поменять знак старшего слово
		dec dx;
		add ax, 2; //Вычислить младшее слово числителя
		adc dx, 0; //Вычислить старшее слово числителя

		//Вычисление знаменателя
		mov bx, ax; //Сохранить младшее слово числителя в BX
		mov al, y;// Поместить y в AL
		cbw; //Расширить AL со знаком до слова
		add ax, 6; //Вычислить знаменатель
		xchg ax, bx; //Поместить младшее слово числителя — в AX,знаменатель — в BX
		idiv bx; // Деление числителя на знаменатель(AX — частное, DX — остаток)
		neg ax; //Поменять знак
		sub ax, 2; //Вычесть 2 
		mov v_as, ax; //Результат — в v_as
	}
	return C;
}

int main()
{
	int input;
	setlocale(LC_ALL, "rus");
	

	printf("Выберите способ задания массива (1 - заранее заданный; 2 - с клавиатуры): ");
	scanf_s("%d", &input);
	switch (input)
	{
	case 1:
	{
		char A[] = { 8, 2, 3, 4, 4, 4, -4, -25, 5, 5, 0, 5, -3, -2, -6, -1 };
		char B[16] = { 0 };
		unsigned int* C[16];
		printf("Введённый массив А:  ");
		for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

		int count;
		_asm {
			xor ecx, ecx; ECX – счётчик цикла и адресация в массивах A и B
			xor ebx, ebx; EBX – для адресации в массиве A и счёта подходящих элементов
			BEG: 
			cmp ecx, LENGTH A
			jae END
			mov al, A[ecx * TYPE A] //элемент A[i] в регистр al(как байт)
			cmp al, -3
			jng L
			mov B[ecx * TYPE B], 1
			lea eax, A[ecx * TYPE A]
			mov C[ebx * TYPE C], eax
			inc ebx
			inc ecx
			jmp BEG

			L: 
			mov dl, A[ecx * TYPE A]
			mov B[ecx * TYPE B], dl
			inc ecx
			jmp BEG

			END: mov count, ebx
		}


		printf("\nПолученный массив B: ");
		for (int i = 0; i < sizeof(B) / sizeof B[0]; i++) printf("%d ", B[i]);
		printf("\nКоличество подходящих элементов: %d", count);
		printf("\nМассив адресов C: ");
		for (int i = 0; i < count; i++) printf("%x ", C[i]);
		break;
	}
	case 2:
	{
		int flag = 1;
		char A[4] = { 0 };
		char B[4] = { 0 };
		unsigned int* C[4];
		while (flag)
		{
			int tmp;
			for (int i = 0; i < sizeof(A) / sizeof A[0]; i++)
			{
				
				printf("Введите A[%d]: ", i);
				scanf_s("%d", &tmp);
				while (getchar() != '\n');
				A[i] = (char)tmp;
			}
			printf("\nВведенный массив А = ");
			for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

			int count;
			_asm {
				xor ecx, ecx; ECX – счётчик цикла и адресация в массивах A и B
				xor ebx, ebx; EBX – для адресации в массиве A и счёта подходящих элементов
				xor dl, dl
				xor eax, eax
				BEG1:
				cmp ecx, LENGTH A
					jae END1
					mov al, A[ecx * TYPE A] //элемент A[i] в регистр al(как байт)
					cmp al, -3
					jng L
					mov B[ecx * TYPE B], 1
					lea eax, A[ecx * TYPE A]
					mov C[ebx * TYPE C], eax
					inc ebx
					inc ecx
					jmp BEG1

					L1:
					mov dl, A[ecx * TYPE A]
					mov B[ecx * TYPE B], dl
					inc ecx
					jmp BEG1

					END1: mov count, ebx
			}
			printf("\nВведенный массив А = ");
			for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

			printf("\nПолученный массив B: ");
			for (int i = 0; i < sizeof(B) / sizeof B[0]; i++) printf("%c ", B[i]);
			printf("\nКоличество подходящих элементов: %d", count);
			printf("\nМассив адресов C: ");
			for (int i = 0; i < count; i++) printf("%x ", C[i]);

			printf("\nВведите 0, чтобы выйти: ");
			scanf_s("%d", &flag);
		}

	}
	default:
		printf("Некорректный способ задания");
		break;
	}


}

