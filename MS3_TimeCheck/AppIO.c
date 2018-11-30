#include "AppIO.h"
#include <stdio.h>

int AppIO_in_order(void) {
	int a;
	printf("\n? 마방진 차수를 입력하시오:");
	scanf("%d", &a);
	return a;
}

void AppIO_out(char* aString) {
	printf(aString);
}
void AppIO_out_executionTime(int anOrder, double anExecutionTime) {
	printf("차수: %2d, 시간: %ld (마이크로 초)\n", anOrder, (double)anExecutionTime);
}