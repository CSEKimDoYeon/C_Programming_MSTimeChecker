#include "Timer.h"
#include "AppController.h"
#include <stdio.h>

#define MAX_NUMBER 1000
/*
int main(void) {
	AppController* appController = AppController_new();
	appController = AppController_new(); // appController ��ü ����
	AppController_run(appController); // app ����
	AppController_delete(appController);// appController ��ü ����
	return 0;
} // end of main()
*/

int main(void)
{
	int i, sum;
	double excutionTime;
	Timer* timer;
	timer = Timer_new();
	Timer_start(timer); // Start Timer
					
	AppController* appController = AppController_new();
	appController = AppController_new(); // appController ��ü ����
	AppController_run(appController); // app ����
	AppController_delete(appController);// appController ��ü ����						
						// ���⿡ ����ð��� ������ �ڵ�
	i = 0;
	sum = 0;
	while (i < MAX_NUMBER) {
		sum = sum + i;
		i++;
	}
	Timer_stop(timer); // Stop Timer
	excutionTime = Timer_duration(timer); // �ڵ� ���� �ð� ( ����: micro second)
	printf("\n����ð� : %ld(micro seconds)", (long) excutionTime );
		Timer_delete(timer);

		system("pause");
	return 0;
}