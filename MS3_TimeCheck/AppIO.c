#include "AppIO.h"
#include <stdio.h>

int AppIO_in_order(void) {
	int a;
	printf("\n? ������ ������ �Է��Ͻÿ�:");
	scanf("%d", &a);
	return a;
}

void AppIO_out(char* aString) {
	printf(aString);
}
void AppIO_out_executionTime(int anOrder, double anExecutionTime) {
	printf("����: %2d, �ð�: %ld (����ũ�� ��)\n", anOrder, (double)anExecutionTime);
}