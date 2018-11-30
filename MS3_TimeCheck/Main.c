#include "Timer.h"
#include "AppController.h"
#include <stdio.h>

#define MAX_NUMBER 1000
/*
int main(void) {
	AppController* appController = AppController_new();
	appController = AppController_new(); // appController 객체 생성
	AppController_run(appController); // app 실행
	AppController_delete(appController);// appController 객체 삭제
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
	appController = AppController_new(); // appController 객체 생성
	AppController_run(appController); // app 실행
	AppController_delete(appController);// appController 객체 삭제						
						// 여기에 실행시간을 측정할 코드
	i = 0;
	sum = 0;
	while (i < MAX_NUMBER) {
		sum = sum + i;
		i++;
	}
	Timer_stop(timer); // Stop Timer
	excutionTime = Timer_duration(timer); // 코드 실행 시간 ( 단위: micro second)
	printf("\n실행시간 : %ld(micro seconds)", (long) excutionTime );
		Timer_delete(timer);

		system("pause");
	return 0;
}