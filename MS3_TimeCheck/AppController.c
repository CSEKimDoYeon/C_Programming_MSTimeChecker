#include "Common.h"
#include "AppController.h"
#include "Timer.h"

#include <stdlib.h>
#include <stdio.h>

#define END_OF_RUN -1
#define EMPTY_CELL -1

typedef struct {
	int _row;
	int _col;
} CellLocation;

void AppController_run(AppController* _this) {
	MagicSquare* magicSquare;
	int order, count;
	Timer* timer; // Timer 객체 선언.
	long executionTime; // 실행시간을 저장하는 변수.
	timer = Timer_new(); // Timer 객체 생성.
	AppIO_out("<<< 마방진 풀이의 성능 측정을 시작합니다 >>>\n");
	AppIO_out("하나의 차수에 대해 100 회 반복 실행한 시간을 측정합니다.\n");
	for (order = 9; order <= MAX_ORDER; order += 10) {
		Timer_start(timer); // 최소 차수 9부터 최대 차수까지 Timer 실행.
		for (count = 0; count < 10; count++) {
			// 시간을 측정할 코드.
			magicSquare = MagicSquare_new(); // 마방진 생성
			MagicSquare_setOrder(magicSquare, order); // 마방진 차수 설정.
			MagicSquare_solve(magicSquare); // 마방진 풀이 실행.
			MagicSquare_delete(magicSquare); // 마방진 삭제.
		}
		Timer_stop(timer); // 모든 작업이 끝나면 Timer 중지.
		executionTime = Timer_duration(timer); 
		//타이머 작동 시작부터 중지까지 시간 계산 후 저장.
		AppIO_out_executionTime(order, executionTime);
		// 측정 결과 출력.
	}
	Timer_delete(timer);
	AppIO_out("<<< 성능 측정을 마칩니다 >>>\n");
}

void AppController_showBoard(AppController* _this, MagicSquare* aMagicSquare) {
	char messageBuffer[255];
	int order = MagicSquare_order(aMagicSquare);
	sprintf(messageBuffer, "Magic Square Board: Order %2d\n", order);
	AppIO_out(messageBuffer);
	AppIO_out(" ");
	for (int col = 0; col < order; col++) {
		sprintf(messageBuffer, " [%2d] ", col);
		AppIO_out(messageBuffer);
	}
	AppIO_out("\n");
	for (int row = 0; row < order; row++) {
		sprintf(messageBuffer, "[%2d]", row);
		AppIO_out(messageBuffer);
		for (int col = 0; col < order; col++) {
			sprintf(messageBuffer, "%5d ", MagicSquare_cell(aMagicSquare, row, col));
			AppIO_out(messageBuffer);
		}
		AppIO_out("\n");
	}
}

AppController* AppController_new(void) {
	// AppController 객체를 생성한다
	AppController* _this;
	_this = (AppController*)malloc(sizeof(AppController));
	return _this;
}

void AppController_delete(AppController* _this) {
	free(_this);
}


/*--------------------------------------------------------------------------*/

MagicSquare* MagicSquare_new() {
	MagicSquare* _this;
	_this = (MagicSquare*)malloc(sizeof(MagicSquare));
	return _this;
}
void MagicSquare_delete(MagicSquare* _this) {
	free(_this);
}
void MagicSquare_setOrder(MagicSquare* _this, int anOrder) {
	_this->_order = anOrder;
}
int MagicSquare_order(MagicSquare* _this) {
	return _this->_order;
}

Boolean MagicSquare_orderIsValid(MagicSquare* _this) {
	if (_this->_order < 3) {
		AppIO_out("[오류] 차수가 너무 작습니다. 3 보다 크거나 같아야 합니다.\n");
		return FALSE;
	}
	else if (_this->_order > MAX_ORDER) {
		char messageBuffer[255];
		sprintf(messageBuffer, "[오류] 차수가 너무 큽니다. %d 보다 작거나 같아야 합니다.\n", MAX_ORDER);
		AppIO_out(messageBuffer);
		return FALSE;
	}
	else if ((_this->_order % 2) == 0) {
		AppIO_out("[오류] 차수가 짝수입니다. 홀수이어야 합니다.\n");
		return FALSE;
	}
	else {
		return TRUE;
	}
}

void MagicSquare_solve(MagicSquare* _this) {
	CellLocation currentLoc; // 현재 위치를 저장하는 객체 선언.
	CellLocation nextLoc; // 다음 위치를 저장하는 객체 선언.

	int row, col; // 행과 열의 index
	int cellValue = 1; // 초기값 1
	int lastCellValue = _this->_order * _this->_order; // 행렬의 최대값은 차수^2 이다.

	for (row = 0; row < _this->_order; row++) { // 모든 행렬의 Value를 EMPTY_CELL 로 초기화한다.
		for (col = 0; col < _this->_order; col++) {
			_this->_board[row][col] = EMPTY_CELL;
		}
	}

	currentLoc._row = 0; // 행은 0 부터 시작.
	currentLoc._col = _this->_order / 2; // 열은 anOrder / 2 즉, 중앙부터 시작한다.
	_this->_board[currentLoc._row][currentLoc._col] = cellValue; // 보드의 현재위치에 cellValue를 채운다.

	cellValue = 2; // 1을 채웠으니 cellValue를 2로 초기화한다.

	for (cellValue = 2; cellValue <= lastCellValue; cellValue++) {
		// cellValue가2부터(anOrder * anOrder) 까지1씩증가하며다음내용을반복
		// <현재위치>로부터<다음위치>를계산한다;
		nextLoc._row = currentLoc._row - 1;
		if (nextLoc._row < 0)
			nextLoc._row = _this->_order - 1;
		nextLoc._col = currentLoc._col + 1;
		if (nextLoc._col >= _this->_order)
			nextLoc._col = 0;



		if (_this->_board[nextLoc._row][nextLoc._col] != EMPTY_CELL) {
			// <다음위치>를<현재위치>의바로한줄아래칸위치로수정한다;
			// <다음위치>를새로운<현재위치>로한다;
			// 보드의새로운<현재위치>에cellValue 를넣는다;
			nextLoc._row = currentLoc._row + 1;
			nextLoc._col = currentLoc._col;
		}
		currentLoc = nextLoc;
		_this->_board[currentLoc._row][currentLoc._col] = cellValue;
	}
}
int MagicSquare_cell(MagicSquare* _this, int aRow, int aCol) {
	if ((0 <= aRow && aRow < _this->_order) &&
		(0 <= aCol && aCol < _this->_order))
	{ // 위치가 정상
		return _this->_board[aRow][aCol];
	}
	else { // 위치가 정상 범위를 벗어났음
		return -1;
	}
}

