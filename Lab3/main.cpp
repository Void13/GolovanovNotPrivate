#include <stdio.h>
#include <conio.h>
#include <memory.h>
#include <algorithm>

#ifdef _DEBUG
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>
#endif

#include "ChessBoard.h"
#include "ChessFigures.h"

int main()
{
	#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtDumpMemoryLeaks();
	#endif

        
	CChessKing King(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(7, 4));
	CChessKnight Knight(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(2, 1));

	CChessKing King2(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(0, 0));
	CChessKnight Knight2(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(2, 1));
	CChessKnight Knight3(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(99, 19));

	CChessBaseFigure *pFigures[32];
	pFigures[0] = &King;
	pFigures[1] = &Knight;

	CChessKing WKing(CChessBaseFigure::FIGURE_WHITE, DirectX::XMINT2(0, 3));
        
        
	/*
	// check
	CChessKing BKing(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(4, 7));
	CChessRook BRook(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(2, 6));

	CChessKing WKing(CChessBaseFigure::FIGURE_WHITE, DirectX::XMINT2(2, 2));
	*/

	/*
	// checkmate
	CChessKing BKing(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(3, 2));
	CChessRook BRook(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(6, 0));

	CChessKing WKing(CChessBaseFigure::FIGURE_WHITE, DirectX::XMINT2(3, 0));
	*/

	/*
	// stalemate
	CChessKing BKing(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(2, 3));
	CChessQuenn BQuenn(CChessBaseFigure::FIGURE_BLACK, DirectX::XMINT2(2, 1));

	CChessKing WKing(CChessBaseFigure::FIGURE_WHITE, DirectX::XMINT2(0, 2));
	*/

	CChessBoard::GetInstance()->Draw();

	printf(CChessBoard::GetInstance()->GetState(&WKing).c_str());

	CChessBoard::GetInstance()->Clear();
	ClearFiguresData();

	_getch();
	return 0;
}