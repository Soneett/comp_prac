#include <stdio.h>
#include <locale.h>
#include <ctype.h>

int main()
{
	setlocale(LC_ALL, "rus");
	int flag = 1;
	while (flag) {

		char A_1[16];
		int tmp;
		for (int i = 0; i < sizeof(A_1) / sizeof A_1[0]; i++)
		{

			printf("Введите A[%d]: ", i);
			if(!scanf_s("%d", &tmp) || tmp >127 || tmp < -128)
			{
				printf("Введенное значение не соответствует допустимому диапазону\n");
				flag = 0;
				goto stop;
			}
			while (getchar() != '\n');
			A_1[i] = (char)tmp;
		}
		char B_1[16] = {0};
		unsigned int* C_1[16];
		printf("Введённый массив А: ");
		for (int i = 0; i < sizeof(A_1) / sizeof A_1[0]; i++) printf("%d ", A_1[i]);

		int count;
		_asm {
			xor ecx, ecx //ECX – счётчик цикла и адресация в массивах A и B
			xor ebx, ebx //EBX – для адресации в массиве A и счёта подходящих элементов
			BEG :
			cmp ecx, LENGTH A_1
				jae END
				mov al, A_1[ecx * TYPE A_1] //элемент A[i] в регистр al(как байт)
				cmp al, -3
				jng L
				mov B_1[ecx * TYPE B_1], 1
				lea eax, A_1[ecx * TYPE A_1]
				mov C_1[ebx * TYPE C_1], eax
				inc ebx
				inc ecx
				jmp BEG

				L :
			mov dl, A_1[ecx * TYPE A_1]
				mov B_1[ecx * TYPE B_1], dl
				inc ecx
				jmp BEG

				END : mov count, ebx
		}

		printf("\nПолученный массив B: ");
		for (int i = 0; i < sizeof(B_1) / sizeof B_1[0]; i++) printf("%d ", B_1[i]);
		printf("\nКоличество подходящих элементов: %d", count);
		printf("\nМассив адресов C: ");
		for (int i = 0; i < count; i++) printf("%x ", C_1[i]);
		stop:
		printf("\nВведите 0, чтобы выйти: ");
		scanf_s("\n%d", &flag);
		while (getchar() != '\n');
	}
	printf("\nПрограмма завершена\n");

	return 0;
}

/*
int main()
{
	setlocale(LC_ALL, "rus");
	int flag = 1;
	while (flag) {

		short int A_1[16];
		int tmp;
		for (int i = 0; i < sizeof(A_1) / sizeof A_1[0]; i++)
		{

			printf("Введите A[%d]: ", i);
			scanf_s("%d", &tmp);
			while (getchar() != '\n');
			A_1[i] = (char)tmp;
		}
		short int B_1[16] = { 0 };
		int* C_1[16];
		printf("Введённый массив А: ");
		for (int i = 0; i < sizeof(A_1) / sizeof A_1[0]; i++) printf("%d ", A_1[i]);

		int count;
		_asm {
			xor ecx, ecx //ECX – счётчик цикла и адресация в массивах A и B
			xor ebx, ebx //EBX – для адресации в массиве A и счёта подходящих элементов
			BEG :
			cmp ecx, LENGTH A_1
				jae END
				mov ax, A_1[ecx * TYPE A_1] //элемент A[i] в регистр al(как байт)
				cmp ax, -3
				jng L
				mov B_1[ecx * TYPE B_1], 1
				lea eax, A_1[ecx * TYPE A_1]
				mov C_1[ebx * TYPE C_1], eax
				inc ebx
				inc ecx
				jmp BEG

				L :
			mov dx, A_1[ecx * TYPE A_1]
				mov B_1[ecx * TYPE B_1], dx
				inc ecx
				jmp BEG

				END : mov count, ebx
		}

		printf("\nПолученный массив B: ");
		for (int i = 0; i < sizeof(B_1) / sizeof B_1[0]; i++) printf("%d ", B_1[i]);
		printf("\nКоличество подходящих элементов: %d", count);
		printf("\nМассив адресов C: ");
		for (int i = 0; i < count; i++) printf("%x ", C_1[i]);

		printf("\nВведите 0, чтобы выйти: ");
		scanf_s("\n%d", &flag);
		while (getchar() != '\n');
	}
	printf("\nПрограмма завершена\n");

	return 0;
}
*/
