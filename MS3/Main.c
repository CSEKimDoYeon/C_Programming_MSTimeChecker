
#include "AppController.h"
#include <stdio.h>

int main(void) {
	AppController* appController = AppController_new();
	appController = AppController_new(); // appController ��ü ����
	AppController_run(appController); // app ����
	AppController_delete(appController);// appController ��ü ����
	system("pause");
	return 0;
} // end of main()