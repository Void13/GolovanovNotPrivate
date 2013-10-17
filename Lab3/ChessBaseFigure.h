#ifndef H__BASECHESSFIGURE
#define H__BASECHESSFIGURE

#define _XM_NO_INTRINSICS_

#include <DirectXMath.h>
#include <string>
#include <vector>

class CChessBaseFigure
{
public:
	enum FIGURE_COLOR 
	{ 
		FIGURE_BLACK = 0,
		FIGURE_WHITE,
		FIGURE_COLOR_COUNT
	};

	CChessBaseFigure(FIGURE_COLOR _Color, DirectX::XMINT2 &_vPos);
	virtual ~CChessBaseFigure();

	virtual void Draw() const = 0;
	virtual std::string const GetState() const = 0;
	virtual std::vector<DirectX::XMINT2> GetMoves() const = 0;
	virtual std::vector<DirectX::XMINT2> GetCaptures() const = 0;

	DirectX::XMINT2 const & GetPos() const;
	FIGURE_COLOR GetColor() const;

	virtual int GetMyMaxCount() const = 0;
	virtual int GetMyCount() const = 0;

	virtual CChessBaseFigure const *const GetNewInstance(DirectX::XMINT2& _vPos) const = 0;
protected:
	DirectX::XMINT2 m_vPos;
	FIGURE_COLOR m_eColor;
};

#endif