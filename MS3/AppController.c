#include "Common.h"
#include "AppController.h"

#include <stdlib.h>
#include <stdio.h>

#define END_OF_RUN -1
#define EMPTY_CELL -1

typedef struct { // �������� ��ġ ������ ������ �ִ� ����ü.
	int _row;
	int _col;
} CellLocation;

void AppController_run(AppController* _this) { 
	// ������ ���α׷��� �����ϴ� AppController
	AppIO_out("<<< ������ Ǯ�̸� �����մϴ� >>>\n");
	MagicSquare* magicSquare = MagicSquare_new();
	int inputOrder = AppIO_in_order(); // ������ �Է� �޴´�
	while (inputOrder != END_OF_RUN) { // ������ -1 �̸� ����
		MagicSquare_setOrder(magicSquare, inputOrder);
		// magicSquare���� ������ �˷��ش�
		if (MagicSquare_orderIsValid(magicSquare)) {
			//������ ��ȿ���� �˻��Ѵ�
			MagicSquare_solve(magicSquare); // �������� Ǭ��
			AppController_showBoard(_this, magicSquare); 
			//������ ���� �����ִ� AppController�� �����Ѵ�.
		}
		inputOrder = AppIO_in_order(); // ������ �Է� �޴´�
	}
	AppIO_out("\n << < ������ Ǯ�̸� �����մϴ� >> >\n");
}

void AppController_showBoard(AppController* _this, MagicSquare* aMagicSquare) {
	//������ ���� �����ִ� �޼ҵ�.
	char messageBuffer[255];
	int order = MagicSquare_order(aMagicSquare); // ���� ����.
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
	} // ������ �迭 ���.
}

AppController* AppController_new(void) {
	// AppController ��ü�� �����Ѵ�
	AppController* _this ; // AppController ��ü ����
	_this = (AppController*)malloc(sizeof(AppController)); 
	// ����� �ν��Ͻ� ������ ���Ͽ�, �ʿ��� �ʱ�ȭ�� �����Ѵ�.
	return _this;
}

void AppController_delete(AppController* _this) {
	free(_this); // ���̻� �ʿ���� ���� �Ҵ� ��ü�� �Ҹ��Ų��.
}


/*--------------------------------------------------------------------------*/

MagicSquare* MagicSquare_new() {
	// MagicSquare ��ü�� �����Ѵ�.
	MagicSquare* _this; 
	_this = (MagicSquare*)malloc(sizeof(MagicSquare));
	// ����� �ν��Ͻ� ������ ���Ͽ�, �ʿ��� �ʱ�ȭ�� �����Ѵ�.
	return _this;
}
void MagicSquare_delete(MagicSquare* _this) {
	free(_this); // ���̻� �ʿ���� ���� �Ҵ� ��ü�� �Ҹ��Ų��.
}
void MagicSquare_setOrder(MagicSquare* _this, int anOrder) {
	_this->_order = anOrder; // �������� ������ �ʱ�ȭ���ش�.
}
int MagicSquare_order(MagicSquare* _this) {
	return _this->_order; // �������� ������ ����Ѵ�.
}

Boolean MagicSquare_orderIsValid(MagicSquare* _this) { 
	// �������� ������ ��ȿ���� �˻��ϴ� �޼ҵ�.
	if (_this->_order < 3) {
		AppIO_out("[����] ������ �ʹ� �۽��ϴ�. 3 ���� ũ�ų� ���ƾ� �մϴ�.\n");
		return FALSE;
	}
	else if (_this->_order > MAX_ORDER) {
		char messageBuffer[255];
		sprintf(messageBuffer, "[����] ������ �ʹ� Ů�ϴ�. %d ���� �۰ų� ���ƾ� �մϴ�.\n", MAX_ORDER);
		AppIO_out(messageBuffer);
		return FALSE;
	}
	else if ((_this->_order % 2) == 0) {
		AppIO_out("[����] ������ ¦���Դϴ�. Ȧ���̾�� �մϴ�.\n");
		return FALSE;
	}
	else {
		return TRUE;
	}
}
void MagicSquare_solve(MagicSquare* _this) {
	CellLocation currentLoc; // ���� ��ġ�� �����ϴ� ��ü ����.
	CellLocation nextLoc; // ���� ��ġ�� �����ϴ� ��ü ����.

	int row, col; // ��� ���� index
	int cellValue = 1; // �ʱⰪ 1
	int lastCellValue = _this->_order * _this->_order; // ����� �ִ밪�� ����^2 �̴�.

	for (row = 0; row < _this->_order; row++) { // ��� ����� Value�� EMPTY_CELL �� �ʱ�ȭ�Ѵ�.
		for (col = 0; col < _this->_order; col++) {
			_this->_board[row][col] = EMPTY_CELL;
		}
	}

	currentLoc._row = 0; // ���� 0 ���� ����.
	currentLoc._col = _this->_order / 2; // ���� anOrder / 2 ��, �߾Ӻ��� �����Ѵ�.
	_this->_board[currentLoc._row][currentLoc._col] = cellValue; // ������ ������ġ�� cellValue�� ä���.

	cellValue = 2; // 1�� ä������ cellValue�� 2�� �ʱ�ȭ�Ѵ�.

	for (cellValue = 2; cellValue <= lastCellValue; cellValue++) {
		// cellValue��2����(anOrder * anOrder) ����1�������ϸ�����������ݺ�
		// <������ġ>�κ���<������ġ>������Ѵ�;
		nextLoc._row = currentLoc._row - 1;
		if (nextLoc._row < 0)
			nextLoc._row = _this->_order - 1;
		nextLoc._col = currentLoc._col + 1;
		if (nextLoc._col >= _this->_order)
			nextLoc._col = 0;



		if (_this->_board[nextLoc._row][nextLoc._col] != EMPTY_CELL) {
			// <������ġ>��<������ġ>�ǹٷ����پƷ�ĭ��ġ�μ����Ѵ�;
			// <������ġ>�����ο�<������ġ>���Ѵ�;
			// �����ǻ��ο�<������ġ>��cellValue ���ִ´�;
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
	{ // ��ġ�� ����
		return _this->_board[aRow][aCol];
	}
	else { // ��ġ�� ���� ������ �����
		return -1;
	}
}

