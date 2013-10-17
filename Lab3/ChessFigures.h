#ifndef H__CHESSFIGURES
#define H__CHESSFIGURES

#include "ChessBaseFigure.h"

#define INIT_CLASS_CHESS_FIGURE(f) \
	class f : public CChessBaseFigure \
	{ \
	public: \
		f(FIGURE_COLOR _Color, DirectX::XMINT2& _vPos, bool _bNeedsToPush = true); \
		~f(); \
		 \
		void Draw() const; \
		std::string const GetState() const; \
		std::vector<DirectX::XMINT2> GetMoves() const; \
		std::vector<DirectX::XMINT2> GetCaptures() const; \
		 \
		CChessBaseFigure const *const GetNewInstance(DirectX::XMINT2& _vPos) const; \
		 \
		int GetMyMaxCount() const; \
		int GetMyCount() const; \
	}; \

INIT_CLASS_CHESS_FIGURE(CChessRook);
INIT_CLASS_CHESS_FIGURE(CChessKnight);
INIT_CLASS_CHESS_FIGURE(CChessBishop);
INIT_CLASS_CHESS_FIGURE(CChessQuenn);
INIT_CLASS_CHESS_FIGURE(CChessKing);
INIT_CLASS_CHESS_FIGURE(CChessPawn);

void ClearFiguresData();
void gotoxy(int x, int y);

#endif