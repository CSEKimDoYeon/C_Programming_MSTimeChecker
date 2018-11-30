#include <Windows.h> // 속도 측정을 위한 Header

typedef struct { // 타이머의 정보들을 가지고 있는 구조체.
	LARGE_INTEGER _frequency;
	LARGE_INTEGER _startCounter;
	LARGE_INTEGER _stopCounter;
} Timer;
Timer * Timer_new(void) {
	// Timer 객체 생성 (malloc 하여 메모리 할당.)
	Timer* _this = (Timer*)malloc(sizeof(Timer));
	QueryPerformanceFrequency(&(_this->_frequency)); // 주파수( 1초당 증가되는 카운트 수)를 구한다.
	return _this;
}
void Timer_delete(Timer* _this) {
	free(_this); // 동적 할당 된 Timer 객체 삭제
}
void Timer_start(Timer* _this) {
	QueryPerformanceCounter(&(_this->_startCounter)); // 실행 전 카운트를 구한다.
}
void Timer_stop(Timer* _this) {
	QueryPerformanceCounter(&(_this->_stopCounter)); // 실행 후 카운트를 구한다.
}
double Timer_duration(Timer* _this) {
	double elapsed = (double)(_this->_stopCounter.QuadPart - _this->_startCounter.QuadPart);
	return (elapsed * 1000000.0 / ((double)_this->_frequency.QuadPart));
	// 실행 시간을 마이크로 초 (micro second) 로 변환한다.
}