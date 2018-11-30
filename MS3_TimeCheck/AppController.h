#pragma once
#include "Common.h"

//typedef struct _AppController AppController;

typedef struct {
	int a;
}AppController;

AppController* AppController_new(void);
void AppController_delete(AppController* _this);
void AppController_run(AppController* __this);
void AppController_showBoard(AppController* _this, MagicSquare* aMagicSquare);

MagicSquare* MagicSquare_new();
void MagicSquare_delete(MagicSquare* _this);

void MagicSquare_setOrder(MagicSquare* _this, int anOrder);
int MagicSquare_order(MagicSquare* _this);
Boolean MagicSquare_orderIsValid(MagicSquare* _this);
void MagicSquare_solve(MagicSquare* _this);
int MagicSquare_cell(MagicSquare* _this, int aRow, int aCol);