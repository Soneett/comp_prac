#include <stdio.h>
#include <locale.h>
#include <ctype.h>


short int** asm(char* A, char* B)
{
	short int* C[sizeof(A)/sizeof(A[0])];
	__asm { //-2 - (2 - (x + 4)*z) / (y + 6);
		//���������� ���������
		mov al, x; //��������� x � AL
		cbw; //��������� AL �� ������ �� �����
		add ax, 4; //��������� x + 4 
		imul z; //��������� z(x + 4) 
		neg ax; //�������� ���� �������� �����
		neg dx; //�������� ���� �������� �����
		dec dx;
		add ax, 2; //��������� ������� ����� ���������
		adc dx, 0; //��������� ������� ����� ���������

		//���������� �����������
		mov bx, ax; //��������� ������� ����� ��������� � BX
		mov al, y;// ��������� y � AL
		cbw; //��������� AL �� ������ �� �����
		add ax, 6; //��������� �����������
		xchg ax, bx; //��������� ������� ����� ��������� � � AX,����������� � � BX
		idiv bx; // ������� ��������� �� �����������(AX � �������, DX � �������)
		neg ax; //�������� ����
		sub ax, 2; //������� 2 
		mov v_as, ax; //��������� � � v_as
	}
	return C;
}

int main()
{
	int input;
	setlocale(LC_ALL, "rus");
	

	printf("�������� ������ ������� ������� (1 - ������� ��������; 2 - � ����������): ");
	scanf_s("%d", &input);
	switch (input)
	{
	case 1:
	{
		char A[] = { 8, 2, 3, 4, 4, 4, -4, -25, 5, 5, 0, 5, -3, -2, -6, -1 };
		char B[16] = { 0 };
		unsigned int* C[16];
		printf("�������� ������ �:  ");
		for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

		int count;
		_asm {
			xor ecx, ecx; ECX � ������� ����� � ��������� � �������� A � B
			xor ebx, ebx; EBX � ��� ��������� � ������� A � ����� ���������� ���������
			BEG: 
			cmp ecx, LENGTH A
			jae END
			mov al, A[ecx * TYPE A] //������� A[i] � ������� al(��� ����)
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


		printf("\n���������� ������ B: ");
		for (int i = 0; i < sizeof(B) / sizeof B[0]; i++) printf("%d ", B[i]);
		printf("\n���������� ���������� ���������: %d", count);
		printf("\n������ ������� C: ");
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
				
				printf("������� A[%d]: ", i);
				scanf_s("%d", &tmp);
				while (getchar() != '\n');
				A[i] = (char)tmp;
			}
			printf("\n��������� ������ � = ");
			for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

			int count;
			_asm {
				xor ecx, ecx; ECX � ������� ����� � ��������� � �������� A � B
				xor ebx, ebx; EBX � ��� ��������� � ������� A � ����� ���������� ���������
				xor dl, dl
				xor eax, eax
				BEG1:
				cmp ecx, LENGTH A
					jae END1
					mov al, A[ecx * TYPE A] //������� A[i] � ������� al(��� ����)
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
			printf("\n��������� ������ � = ");
			for (int i = 0; i < sizeof(A) / sizeof A[0]; i++) printf("%d ", A[i]);

			printf("\n���������� ������ B: ");
			for (int i = 0; i < sizeof(B) / sizeof B[0]; i++) printf("%c ", B[i]);
			printf("\n���������� ���������� ���������: %d", count);
			printf("\n������ ������� C: ");
			for (int i = 0; i < count; i++) printf("%x ", C[i]);

			printf("\n������� 0, ����� �����: ");
			scanf_s("%d", &flag);
		}

	}
	default:
		printf("������������ ������ �������");
		break;
	}


}

