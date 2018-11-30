#pragma once

#define MAX_ORDER 99

typedef enum { FALSE, TRUE } Boolean;

typedef struct {
	int _order;
	int _board[MAX_ORDER][MAX_ORDER];
}MagicSquare;