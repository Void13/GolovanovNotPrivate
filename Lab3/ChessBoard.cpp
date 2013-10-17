#include <vector>
#include <typeinfo>

#include "ChessBoard.h"
#include "ChessFigures.h"

CChessBoard *CChessBoard::GetInstance()
{
	static CChessBoard inst;
	return &inst;
}

CChessBoard::CChessBoard()
{
};

CChessBoard::~CChessBoard()
{
	Clear();
};

void CChessBoard::Clear()
{
	/*
	for (auto *&pFigure : m_Figures)
	{
		if (!pFigure)
			continue;

		//delete pFigure;
		pFigure = nullptr;
	}
	*/

	m_Figures.clear();

	m_PosToFigure.clear();
};

void CChessBoard::AddFigure(CChessBaseFigure *const _pFigure)
{
	if (IsItPossibleToPush(_pFigure))
	{
		m_Figures.push_back(_pFigure);
		m_PosToFigure.emplace(_pFigure->GetPos().y * BOARD_WIDTH + _pFigure->GetPos().x, _pFigure);
	}
};

void CChessBoard::DeleteFigure(CChessBaseFigure const *const _pFigure)
{
	auto it = std::find(m_Figures.begin(), m_Figures.end(), _pFigure);
	if (it != m_Figures.end())
	{
		m_Figures.erase(it);
	}

	auto itMap = m_PosToFigure.find(_pFigure->GetPos().y * BOARD_WIDTH + _pFigure->GetPos().x);
	if (itMap != m_PosToFigure.end())
	{
		m_PosToFigure.erase(itMap);
	}
};

void CChessBoard::Draw() const
{
	gotoxy(0, 0);

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			printf("* ");
		}

		printf("\n");
	}

	for (auto *pFigure : m_Figures)
	{
		pFigure->Draw();
	}
}

bool CChessBoard::IsItPossibleToPush(CChessBaseFigure const *const _pFigure) const
{
	/*
		1. проверку попадания фигуры на доску
		2. проверку установки фигуры на свободную клетку
		3. отслеживание количества экземпляров каждого вида фигур
	*/

	// 1
	if (_pFigure->GetPos().x >= BOARD_WIDTH || _pFigure->GetPos().x < 0 ||
		_pFigure->GetPos().y >= BOARD_HEIGHT || _pFigure->GetPos().y < 0)
		return false;

	// 2
	for (auto *pFigure : m_Figures)
	{
		if (_pFigure->GetPos().x == pFigure->GetPos().x && _pFigure->GetPos().y == pFigure->GetPos().y)
			return false;
	}

	/*
	// 3
#define CHECK_COUNT(TYPE) \
	{ \
		if (typeid(*_pFigure) == typeid(TYPE) && TYPE::GetMyCount(_pFigure->GetColor()) > TYPE::GetMyMaxCount()) \
			return false; \
	}

	CHECK_COUNT(CChessRook);
	CHECK_COUNT(CChessKnight);
	CHECK_COUNT(CChessBishop);
	CHECK_COUNT(CChessQuenn);
	CHECK_COUNT(CChessKing);
	CHECK_COUNT(CChessPawn);

#undef CHECK_COUNT
	*/

	if (_pFigure->GetMyCount() > _pFigure->GetMyMaxCount())
		return false;

	return true;
};

int round(float v) 
{ 
	return int(v + 0.5f * (1 + (((*reinterpret_cast<int *>(&v)) >> 31) << 1))); 
}

std::vector<std::pair<int, int>> GetPath(std::pair<int, int> f, std::pair<int, int> s)
{
	std::vector<std::pair<int, int>> Path;

	// если f.x - s.x > f.y - s.y, то идём по x
	if (abs(f.first - s.first) > abs(f.second - s.second))
	{
		float fYdX = ((float)s.second - f.second) / ((float)s.first - f.first);

		if (f.first > s.first)
		{
			for (int i = s.first; i <= f.first; i++)
			{
				Path.emplace_back(i, (int)round(fYdX * (i - f.first) + f.second));
			}
		}
		else
		{
			for (int i = f.first; i <= s.first; i++)
			{
				Path.emplace_back(i, (int)round(fYdX * (i - f.first) + f.second));
			}
		}
	}
	else
	{
		float fXdY = ((float)s.first - f.first) / ((float)s.second - f.second);

		if (f.second > s.second)
		{
			for (int i = s.second; i <= f.second; i++)
			{
				Path.emplace_back((int)round(fXdY * (i - f.second) + f.first), i);
			}
		}
		else
		{
			for (int i = f.second; i <= s.second; i++)
			{
				Path.emplace_back((int)round(fXdY * (i - f.second) + f.first), i);
			}
		}
	}

	return Path;
}

// функция сообщает, что фигура под ударом находится или нет
bool CChessBoard::IsCellFree(CChessBaseFigure const *const _pFigure, CChessBaseFigure const *const _pFigureToForget) const
{
	// поиск фигуры, которая может добраться до исходной
	for (auto *pFigure : m_Figures)
	{
		if (pFigure == _pFigure || pFigure->GetColor() == _pFigure->GetColor())
			continue;

		bool bIsCaptured = false;

		// получаем все ходы для захвата вражеских фигур
		auto &Captures = pFigure->GetCaptures();
		for (auto &Capture : Captures)
		{
			// клетки совпадают
			if (Capture.x == _pFigure->GetPos().x && Capture.y == _pFigure->GetPos().y)
			{
				bIsCaptured = true;
				break;
			}
		}

		if (!bIsCaptured)
			continue;

		// если это конь, то надо завершить
		if (typeid(*pFigure) == typeid(CChessKnight))
			return false;

		// теперь надо проверить, а может ли фигура pFigure дойти до _pFigure ?
		
		// возьмём все точки пути
		auto Path = GetPath(std::make_pair(pFigure->GetPos().x, pFigure->GetPos().y), std::make_pair(_pFigure->GetPos().x, _pFigure->GetPos().y));

		bool bIsFindedBlockingFigure = false;

		// на пути встретилась фигура какая-то
		for (auto &Cell : Path)
		{
			auto *pBlockFigure = CChessBoard::GetFigure(DirectX::XMINT2(Cell.first, Cell.second));
			if (pBlockFigure && pBlockFigure != pFigure && pBlockFigure != _pFigure && pBlockFigure != _pFigureToForget)
			{
				bIsFindedBlockingFigure = true;
				break;
			}
		}

		if (!bIsFindedBlockingFigure)
			return false;
	}

	return true;
};

std::string const CChessBoard::GetState(CChessBaseFigure const *const _pFigure) const
{
	// прибывает с функции вектор, гружёный позициями ходов
	// принимаем заказ
	std::vector<DirectX::XMINT2> &Moves = _pFigure->GetMoves();

	std::vector<DWORD> ToDelete;

	DWORD iMove = 0;

	// если в клетке хода кто-то стоит уже - нафиг этот ход
	for (auto &vMove : Moves)
	{
		auto *pFigureOnCell = GetFigure(vMove);
		if (pFigureOnCell)
		{
			ToDelete.push_back(iMove);
		}

		if (typeid(*_pFigure) == typeid(CChessKnight))
			continue;

		// берём путь от фигуры до хода
		auto Path = GetPath(std::make_pair(vMove.x, vMove.y), std::make_pair(_pFigure->GetPos().x, _pFigure->GetPos().y));

		bool bIsFindedBlockingFigure = false;

		// ищем, встречается-ли на пути какая-то фигура
		for (auto &Cell : Path)
		{
			auto *pBlockFigure = CChessBoard::GetFigure(DirectX::XMINT2(Cell.first, Cell.second));
			if (pBlockFigure && pBlockFigure != _pFigure)
			{
				bIsFindedBlockingFigure = true;
				break;
			}
		}

		if (bIsFindedBlockingFigure && !pFigureOnCell)
		{
			ToDelete.push_back(iMove);
		}

		iMove++;
	}

	for (auto it = ToDelete.rbegin(); it != ToDelete.rend(); it++)
	{
		Moves.erase(Moves.begin() + *it);
	}

	// пат: когда в текущей клетке всё норм,	а возможные ходы все не свободные
	// мат: когда в текущей клетке мат,			а возможные ходы все не свободные
	// шах: когда в текущая клетка мат,			а возможные ходы все свободные

	// текущая клетка под матом
	// возможные ходы все под матом
	// возможные ходы все свободные

	bool bMovesAnyIsFree = false;
	bool bMovesAllIsNotFree = false;
	bool bCurrentCellIsNotFree = false;

	int nCounterOfFreeCells = 0;
	int nCounterOfNotFreeCells = 0;

	// проверка возможных ходов:
	for (auto &vMove : Moves)
	{
		CChessBaseFigure const *const piFigure = _pFigure->GetNewInstance(vMove);

		// новый сосед: piFigure
		// нужно проверить его на возможную угрозу со стороны остальных фигур противоположного цвета
		if (IsCellFree(piFigure, _pFigure))
			nCounterOfFreeCells++;
		else
			nCounterOfNotFreeCells++;

		delete piFigure;
	}

	if (nCounterOfFreeCells > 0)
		bMovesAnyIsFree = true;

	if (nCounterOfNotFreeCells == Moves.size())
		bMovesAllIsNotFree = true;

	bCurrentCellIsNotFree = !IsCellFree(_pFigure, nullptr);

	if (!bCurrentCellIsNotFree && bMovesAllIsNotFree)
		return "Stalemate";

	if (bCurrentCellIsNotFree && bMovesAllIsNotFree)
		return "Checkmate";

	if (bCurrentCellIsNotFree && bMovesAnyIsFree)
		return "Check";

	return "Free";
};

CChessBaseFigure const *const CChessBoard::GetFigure(DirectX::XMINT2 &_vPos) const
{
	auto itMap = m_PosToFigure.find(_vPos.y * BOARD_WIDTH + _vPos.x);

	if (itMap == m_PosToFigure.end())
		return nullptr;

	return (*itMap).second;
};