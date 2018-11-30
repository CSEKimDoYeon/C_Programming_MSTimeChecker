#include "AppIO.h"
#include <stdio.h>

void AppIO_out(char* aMessage) {
	printf(aMessage);
}

int AppIO_in_order(void) {
	//사용자로부터 마방진의 차수를 입력받고 return
	int a;
	printf("\n? 마방진 차수를 입력하시오:");
	scanf("%d", &a);
	return a;
}