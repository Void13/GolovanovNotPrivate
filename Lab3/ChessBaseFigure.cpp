#include "ChessBaseFigure.h"
#include "ChessBoard.h"

CChessBaseFigure::CChessBaseFigure(FIGURE_COLOR _Color, DirectX::XMINT2 &_vPos)
	: m_eColor(_Color), m_vPos(_vPos)
{
};

CChessBaseFigure::~CChessBaseFigure()
{
};

DirectX::XMINT2 const & CChessBaseFigure::GetPos() const
{
	return m_vPos;
};

CChessBaseFigure::FIGURE_COLOR CChessBaseFigure::GetColor() const
{
	return m_eColor;
};