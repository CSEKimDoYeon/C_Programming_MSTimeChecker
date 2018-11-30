#include <Windows.h> // �ӵ� ������ ���� Header

typedef struct {
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _startCounter;
	LARGE_INTEGER _stopCounter;
} Timer;

Timer* Timer_new();
//Ÿ�̸� ����
void Timer_delete(Timer* _this);
// Ÿ�̸� �Ҹ�
void Timer_start(Timer* _this);
// Ÿ�̸� �۵� ����
void Timer_stop(Timer* _this);
// Ÿ�̸� �۵� ����
double Timer_duration(Timer* _this);
// Ÿ�̸� �۵� ���ۺ��� ���������� �ð�(����: micro second)