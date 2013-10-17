#include <stdio.h>
#include <Windows.h>

#include "ChessFigures.h"
#include "ChessBoard.h"

int g_nCChessRookCount[CChessBaseFigure::FIGURE_COLOR_COUNT];
int g_nCChessKnightCount[CChessBaseFigure::FIGURE_COLOR_COUNT];
int g_nCChessBishopCount[CChessBaseFigure::FIGURE_COLOR_COUNT];
int g_nCChessQuennCount[CChessBaseFigure::FIGURE_COLOR_COUNT];
int g_nCChessKingCount[CChessBaseFigure::FIGURE_COLOR_COUNT];
int g_nCChessPawnCount[CChessBaseFigure::FIGURE_COLOR_COUNT];

void ClearFiguresData()
{
	g_nCChessRookCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessRookCount[CChessBaseFigure::FIGURE_BLACK] = 0;

	g_nCChessKnightCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessKnightCount[CChessBaseFigure::FIGURE_BLACK] = 0;

	g_nCChessBishopCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessBishopCount[CChessBaseFigure::FIGURE_BLACK] = 0;

	g_nCChessQuennCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessQuennCount[CChessBaseFigure::FIGURE_BLACK] = 0;

	g_nCChessKingCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessKingCount[CChessBaseFigure::FIGURE_BLACK] = 0;

	g_nCChessPawnCount[CChessBaseFigure::FIGURE_WHITE] = 0;
	g_nCChessPawnCount[CChessBaseFigure::FIGURE_BLACK] = 0;
}

void gotoxy(int x, int y) 
{
	static HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD pos = { x * 2, y };
	SetConsoleCursorPosition(output, pos);
}

#define GET_CONSTRUCTOR(a) \
	a::a(FIGURE_COLOR _Color, DirectX::XMINT2& _vPos, bool _bNeedsToPush) \
		: CChessBaseFigure(_Color, _vPos) \
	{ \
		if (_bNeedsToPush) \
		{ \
			(g_n ## a ## Count)[_Color]++; \
			CChessBoard::GetInstance()->AddFigure(this); \
		} \
	};

#define GET_DESTRUCTOR(a) \
	a::~a() \
	{ \
		(g_n ## a ## Count)[m_eColor]--; \
		CChessBoard::GetInstance()->DeleteFigure(this); \
	};

#define GET_MAXCOUNT(a) \
	int a::GetMyCount() const \
	{ \
		return (g_n ## a ## Count)[m_eColor]; \
	};

#define GET_GETSTATE(a) \
	std::string const a::GetState() const \
	{ \
		return CChessBoard::GetInstance()->GetState(this); \
	};

#define GET_NEWINSTANCE(a) \
	CChessBaseFigure const *const a::GetNewInstance(DirectX::XMINT2& _vPos) const \
	{ \
		return new a(m_eColor, _vPos, false); \
	};


// ---------------------------------------------------------------------------------
// -------------------------------- ROOK  -----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessRook);
GET_DESTRUCTOR(CChessRook);
GET_MAXCOUNT(CChessRook);
GET_GETSTATE(CChessRook);
GET_NEWINSTANCE(CChessRook);

void CChessRook::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("R");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessRook::GetMoves() const
{
	std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	for (int i = 0; i < BOARD_WIDTH; i++)
		MyMoves.push_back(DirectX::XMINT2(i, m_vPos.y));

	for (int i = 0; i < BOARD_HEIGHT; i++)
		MyMoves.push_back(DirectX::XMINT2(m_vPos.x, i));

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessRook::GetCaptures() const
{
	return GetMoves();
};

int CChessRook::GetMyMaxCount() const
{
	return 2;
};

// ---------------------------------------------------------------------------------
// -------------------------------- KNIGHT ----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessKnight);
GET_DESTRUCTOR(CChessKnight);
GET_MAXCOUNT(CChessKnight);
GET_GETSTATE(CChessKnight);
GET_NEWINSTANCE(CChessKnight);

void CChessKnight::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("k");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessKnight::GetMoves() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	DirectX::XMINT2 Moves[] = 
	{
		DirectX::XMINT2(1, 2),
		DirectX::XMINT2(2, 1),
		DirectX::XMINT2(-1, -2),
		DirectX::XMINT2(-1, 2),
		DirectX::XMINT2(1, -2),
		DirectX::XMINT2(-2, -1),
		DirectX::XMINT2(-2, 1),
		DirectX::XMINT2(2, -1)
	};

	for (int i = 0; i < _ARRAYSIZE(Moves); i++)
	{
		if (Moves[i].x + m_vPos.x < 0 || Moves[i].x + m_vPos.x >= BOARD_WIDTH ||
			Moves[i].y + m_vPos.y < 0 || Moves[i].y + m_vPos.y >= BOARD_HEIGHT)
			continue;

		MyMoves.push_back(DirectX::XMINT2(Moves[i].x + m_vPos.x, Moves[i].y + m_vPos.y));
	}

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessKnight::GetCaptures() const
{
	return GetMoves();
};

int CChessKnight::GetMyMaxCount() const
{
	return 2;
};

// ---------------------------------------------------------------------------------
// -------------------------------- BISHOP -----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessBishop);
GET_DESTRUCTOR(CChessBishop);
GET_MAXCOUNT(CChessBishop);
GET_GETSTATE(CChessBishop);
GET_NEWINSTANCE(CChessBishop);

void CChessBishop::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("B");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessBishop::GetMoves() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	DirectX::XMVECTOR xvEnd = DirectX::XMLoadSInt2(&DirectX::XMINT2(BOARD_WIDTH, BOARD_HEIGHT));

	DirectX::XMVECTORF32 xvStep1 = { 1.0f, 1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep2 = { -1.0f, -1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep3 = { 1.0f, -1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep4 = { -1.0f, 1.0f, 0.0f, 0.0f };
	
#define CREATE_FOR(s) \
	for (DirectX::XMVECTOR xviPos = DirectX::XMLoadSInt2(&m_vPos);; \
		xviPos = DirectX::XMVectorAdd(xviPos, s)) \
	{ \
		DirectX::XMVECTOR xvResult = DirectX::XMVectorLess(xviPos, xvEnd); \
		if (!xvResult.vector4_u32[0] || !xvResult.vector4_u32[1]) \
			break; \
		\
		xvResult = DirectX::XMVectorGreaterOrEqual(xviPos, DirectX::g_XMZero); \
		if (!xvResult.vector4_u32[0] || !xvResult.vector4_u32[1]) \
			break; \
		\
		DirectX::XMINT2 viPos; \
		DirectX::XMStoreSInt2(&viPos, xviPos); \
		MyMoves.push_back(viPos); \
	}

	CREATE_FOR(xvStep1);
	CREATE_FOR(xvStep2);
	CREATE_FOR(xvStep3);
	CREATE_FOR(xvStep4);

#undef CREATE_FOR

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessBishop::GetCaptures() const
{
	return GetMoves();
};

int CChessBishop::GetMyMaxCount() const
{
	return 2;
};

// ---------------------------------------------------------------------------------
// -------------------------------- QUENN -----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessQuenn);
GET_DESTRUCTOR(CChessQuenn);
GET_MAXCOUNT(CChessQuenn);
GET_GETSTATE(CChessQuenn);
GET_NEWINSTANCE(CChessQuenn);

void CChessQuenn::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("Q");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessQuenn::GetMoves() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	DirectX::XMVECTOR xvEnd = DirectX::XMLoadSInt2(&DirectX::XMINT2(BOARD_WIDTH, BOARD_HEIGHT));

	DirectX::XMVECTORF32 xvStep1 = { 1.0f, 1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep2 = { -1.0f, -1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep3 = { 1.0f, -1.0f, 0.0f, 0.0f };
	DirectX::XMVECTORF32 xvStep4 = { -1.0f, 1.0f, 0.0f, 0.0f };

#define CREATE_FOR(s) \
	for (DirectX::XMVECTOR xviPos = DirectX::XMLoadSInt2(&m_vPos);; \
		xviPos = DirectX::XMVectorAdd(xviPos, s)) \
	{ \
		DirectX::XMVECTOR xvResult = DirectX::XMVectorLess(xviPos, xvEnd); \
		if (!xvResult.vector4_u32[0] || !xvResult.vector4_u32[1]) \
			break; \
		\
		xvResult = DirectX::XMVectorGreaterOrEqual(xviPos, DirectX::g_XMZero); \
		if (!xvResult.vector4_u32[0] || !xvResult.vector4_u32[1]) \
			break; \
		\
		DirectX::XMINT2 viPos; \
		DirectX::XMStoreSInt2(&viPos, xviPos); \
		MyMoves.push_back(viPos); \
	}

	CREATE_FOR(xvStep1);
	CREATE_FOR(xvStep2);
	CREATE_FOR(xvStep3);
	CREATE_FOR(xvStep4);

#undef CREATE_FOR

	for (int i = 0; i < BOARD_WIDTH; i++)
		MyMoves.push_back(DirectX::XMINT2(i, m_vPos.y));

	for (int i = 0; i < BOARD_HEIGHT; i++)
		MyMoves.push_back(DirectX::XMINT2(m_vPos.x, i));

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessQuenn::GetCaptures() const
{
	return GetMoves();
};

int CChessQuenn::GetMyMaxCount() const
{
	return 1;
};

// ---------------------------------------------------------------------------------
// -------------------------------- KING  -----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessKing);
GET_DESTRUCTOR(CChessKing);
GET_MAXCOUNT(CChessKing);
GET_GETSTATE(CChessKing);
GET_NEWINSTANCE(CChessKing);

void CChessKing::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("K");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessKing::GetMoves() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	DirectX::XMINT2 Moves[] = 
	{
		DirectX::XMINT2(0, 1),
		DirectX::XMINT2(-1, 1),
		DirectX::XMINT2(-1, 0),
		DirectX::XMINT2(-1, -1),
		DirectX::XMINT2(0, -1),
		DirectX::XMINT2(1, -1),
		DirectX::XMINT2(1, 0),
		DirectX::XMINT2(1, 1)
	};

	for (int i = 0; i < _ARRAYSIZE(Moves); i++)
	{
		if (Moves[i].x + m_vPos.x < 0 || Moves[i].x + m_vPos.x >= BOARD_WIDTH ||
			Moves[i].y + m_vPos.y < 0 || Moves[i].y + m_vPos.y >= BOARD_HEIGHT)
			continue;

		MyMoves.push_back(DirectX::XMINT2(Moves[i].x + m_vPos.x, Moves[i].y + m_vPos.y));
	}

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessKing::GetCaptures() const
{
	return GetMoves();
};

int CChessKing::GetMyMaxCount() const
{
	return 1;
};

// ---------------------------------------------------------------------------------
// -------------------------------- PAWN  -----------------------------------------
// ---------------------------------------------------------------------------------

GET_CONSTRUCTOR(CChessPawn);
GET_DESTRUCTOR(CChessPawn);
GET_MAXCOUNT(CChessPawn);
GET_GETSTATE(CChessPawn);
GET_NEWINSTANCE(CChessPawn);

void CChessPawn::Draw() const
{
	gotoxy(m_vPos.x, m_vPos.y);

	printf("P");

	gotoxy(0, 8);
};

std::vector<DirectX::XMINT2> CChessPawn::GetMoves() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	if (m_eColor == FIGURE_BLACK)
	{
		if (m_vPos.y < BOARD_HEIGHT - 1)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y + 1));

		if (m_vPos.y == 1)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y + 2));
	}

	if (m_eColor == FIGURE_WHITE)
	{
		if (m_vPos.y > 0)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y - 1));

		if (m_vPos.y == 6)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y - 2));
	}

	return MyMoves;
};

std::vector<DirectX::XMINT2> CChessPawn::GetCaptures() const
{
	static std::vector<DirectX::XMINT2> MyMoves;
	MyMoves.clear();

	if (m_eColor == FIGURE_BLACK && m_vPos.y < 7)
	{
		if (m_vPos.x + 1 < BOARD_WIDTH)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y + 1));
		if (m_vPos.x - 1 > 0)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y - 1));
	}

	if (m_eColor == FIGURE_WHITE && m_vPos.y > 0)
	{
		if (m_vPos.x + 1 < BOARD_WIDTH)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y + 1));
		if (m_vPos.x - 1 > 0)
			MyMoves.push_back(DirectX::XMINT2(m_vPos.x, m_vPos.y - 1));
	}

	return MyMoves;
};

int CChessPawn::GetMyMaxCount() const
{
	return 8;
};