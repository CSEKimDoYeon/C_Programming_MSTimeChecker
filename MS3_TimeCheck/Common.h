#pragma once

#define MAX_ORDER 999

//typedef enum { FALSE, TRUE } Boolean;

typedef int Boolean;
#define TRUE 1
#define FALSE 0

typedef struct {
	int _order;
	int _board[MAX_ORDER][MAX_ORDER];
}MagicSquare;