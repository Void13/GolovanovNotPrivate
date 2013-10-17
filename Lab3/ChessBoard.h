#ifndef H__CHESSBOARD
#define H__CHESSBOARD

#include <vector>
#include <unordered_map>
#include <Windows.h>
#include "ChessBaseFigure.h"

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

class CChessBoard
{
public:
	static CChessBoard *GetInstance();
	CChessBoard();
	~CChessBoard();

	void Clear();
	void AddFigure(CChessBaseFigure *const _pFigure);
	void DeleteFigure(CChessBaseFigure const *const _pFigure);
	void Draw() const;
	CChessBaseFigure const *const GetFigure(DirectX::XMINT2 &_vPos) const;

	std::string const GetState(CChessBaseFigure const *const _pFigure) const;
protected:
	bool IsItPossibleToPush(CChessBaseFigure const *const _pFigure) const;
	bool IsCellFree(CChessBaseFigure const *const _pFigure, CChessBaseFigure const *const _pFigureToForget) const;

	std::unordered_map<DWORD, CChessBaseFigure *> m_PosToFigure;
	std::vector<CChessBaseFigure *> m_Figures;
};

#endif