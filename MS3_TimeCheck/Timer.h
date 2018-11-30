#include <Windows.h> // 속도 측정을 위한 Header

typedef struct {
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _startCounter;
	LARGE_INTEGER _stopCounter;
} Timer;

Timer* Timer_new();
//타이머 생성
void Timer_delete(Timer* _this);
// 타이머 소멸
void Timer_start(Timer* _this);
// 타이머 작동 시작
void Timer_stop(Timer* _this);
// 타이머 작동 중지
double Timer_duration(Timer* _this);
// 타이머 작동 시작부터 중지까지의 시간(단위: micro second)