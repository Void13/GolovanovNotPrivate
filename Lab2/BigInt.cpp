#include "BigInt.h"

CBigInt::CBigInt()
{
	m_pNumber = new CHARDEQ;
	m_bIsNeg = false;

#ifdef DEBUG_CONSTR
	std::cout << "default constructor" << std::endl;
#endif
};

CBigInt::CBigInt(int const _nNumber)
{
	m_bIsNeg = _nNumber < 0;
	int nSrcNumber = _nNumber;
	m_pNumber = new CHARDEQ;
	while (nSrcNumber)
	{
		m_pNumber->push_back((char)(nSrcNumber % 10));
		nSrcNumber /= 10;
	}

	if (!_nNumber)
		m_pNumber->push_back(0);

	ClearZeroes(*this);

#ifdef DEBUG_CONSTR
	std::cout << "constructor from number" << std::endl;
#endif
};

CBigInt::CBigInt(std::string const _sNumber)
{
	m_bIsNeg = false;

	auto itStart = _sNumber.begin();

	if (_sNumber.size() > 1)
		m_bIsNeg = *itStart == '-' && *(itStart + 1) != '0';

	m_pNumber = new CHARDEQ;

	if (m_bIsNeg)
		itStart++;

	for (auto it = itStart, itEnd = _sNumber.end(); it != itEnd; it++)
	{
		m_pNumber->push_front(*it - '0');
	}

	ClearZeroes(*this);

#ifdef DEBUG_CONSTR
	std::cout << "constructor from string" << std::endl;
#endif
};

CBigInt::CBigInt(CBigInt const &_SourceNumber)
{
	if (this != &_SourceNumber)
	{
		m_bIsNeg = _SourceNumber.m_bIsNeg;
		m_pNumber = new CHARDEQ;

		m_pNumber->assign(_SourceNumber.m_pNumber->begin(), _SourceNumber.m_pNumber->end());

#ifdef DEBUG_CONSTR
		std::cout << "constructor from lvalue" << std::endl;
#endif
	}
};

CBigInt::CBigInt(CBigInt &&_SourceNumber)
{
	if (this != &_SourceNumber)
	{
		m_bIsNeg = _SourceNumber.m_bIsNeg;
		m_pNumber = _SourceNumber.m_pNumber;
		_SourceNumber.m_pNumber = nullptr;

#ifdef DEBUG_CONSTR
		std::cout << "constructor from rvalue" << std::endl;
#endif
	}
};

CBigInt::~CBigInt()
{
	if (m_pNumber != nullptr)
	{
		delete m_pNumber;
		m_pNumber = nullptr;

#ifdef DEBUG_CONSTR
		std::cout << "destructor with deleting" << std::endl;
#endif
	} 
#ifdef DEBUG_CONSTR
	else
		std::cout << "destructor" << std::endl;
#endif
};

void ClearZeroes(CBigInt &_Number)
{
	if (!_Number.m_pNumber->size())
		return;
	auto it = _Number.m_pNumber->end();
	it--;
	for (auto itEnd = _Number.m_pNumber->begin(); it != itEnd && !*it; it--) {};
	_Number.m_pNumber->erase(it + 1, _Number.m_pNumber->end());
}

CBigInt const operator+(CBigInt const &_First, CBigInt const &_Second)
{
	CBigInt result(_First);
	result += _Second;
	return result;
};

CBigInt const &CBigInt::operator+=(CBigInt const &_Second)
{
	if (_Second.m_bIsNeg && m_bIsNeg)
		m_bIsNeg = true;

	if (!m_bIsNeg && _Second.m_bIsNeg)
	{
		CBigInt TmpSecond = _Second;
		TmpSecond.m_bIsNeg = false;
		*this -= TmpSecond;
	}
	else if (m_bIsNeg && !_Second.m_bIsNeg)
	{
		m_bIsNeg = false;
		*this = _Second - *this;
	}
	else 
	{
		int nThisNumberSize = (int)m_pNumber->size();
		long long int nCarrier = 0;

		for (int i = 0; i < std::max((int)_Second.m_pNumber->size(), nThisNumberSize); i++)
		{
			if (!nCarrier)
			{
				if (i >= (int)_Second.m_pNumber->size())
					break;
				else if (i >= (int)m_pNumber->size())
				{
					m_pNumber->insert(m_pNumber->end(), _Second.m_pNumber->begin() + i, _Second.m_pNumber->end());
					break;
				}
			}

			int nX = i >= (int)_Second.m_pNumber->size() ? 0 : _Second.m_pNumber->at(i);
			int nY = i >= nThisNumberSize ? 0 : m_pNumber->at(i);

			long long int llR = nX + nY + nCarrier;

			if (i < nThisNumberSize)
				(*m_pNumber)[i] = (llR % 10);
			else
				m_pNumber->push_back(llR % 10);

			nCarrier = llR / 10;
		}

		if (nCarrier)
			m_pNumber->push_back((int)nCarrier);
	}

	return *this;
};

CBigInt const CBigInt::operator++(int)
{
	CBigInt tmp(*this);

	//operator++();

	++(*this);

	return tmp;
};

CBigInt const &CBigInt::operator++()
{
	if (m_bIsNeg)
	{
		m_bIsNeg = false;
		//operator--();
		--(*this);

		if (*m_pNumber->begin())
			m_bIsNeg = true;

		return *this;
	}

	long long int nCarrier = 1;
	int nThisNumberSize = (int)m_pNumber->size();

	for (int i = 0; i < nThisNumberSize && nCarrier; i++)
	{
		long long int llR = (*m_pNumber)[i] + nCarrier;

		(*m_pNumber)[i] = llR % 10;

		nCarrier = llR / 10;
	}

	if (nCarrier)
		m_pNumber->push_back((int)nCarrier);

	return *this;
};

CBigInt const CBigInt::operator-() const
{
	CBigInt result = *this;
	result.m_bIsNeg = !result.m_bIsNeg;
	return result;
};

CBigInt const operator-(CBigInt const &_First, CBigInt const &_Second)
{
	CBigInt result(_First);
	result -= _Second;
	return result;
};

CBigInt const &CBigInt::operator-=(CBigInt const &_Second)
{
	CBigInt result;

	auto _Subtract = [&result](CBigInt const &__First, CBigInt const &__Second)
	{
		int nCarrier = 0;

		for (int i = 0; i < (int)std::max(__First.m_pNumber->size(), __Second.m_pNumber->size()); i++)
		{
			int nX = i >= (int)__First.m_pNumber->size() ? 0 : __First.m_pNumber->at(i);
			int nY = i >= (int)__Second.m_pNumber->size() ? 0 : __Second.m_pNumber->at(i);

			if (nX >= nY + nCarrier)
			{
				result.m_pNumber->push_back(nX - nY - nCarrier);
				nCarrier = 0;
			}
			else
			{
				result.m_pNumber->push_back(10 + nX - nY - nCarrier);
				nCarrier = 1;
			}
		}

		ClearZeroes(result);
	};

	if (m_bIsNeg && _Second.m_bIsNeg)
	{
		CBigInt TmpSecond = _Second;
		TmpSecond.m_bIsNeg = false;
		_Subtract(TmpSecond, *this);
	}
	else if (!m_bIsNeg && _Second.m_bIsNeg)
	{
		CBigInt TmpSecond = _Second;
		TmpSecond.m_bIsNeg = false;
		*this += TmpSecond;
	}
	else if (m_bIsNeg && !_Second.m_bIsNeg)
	{
		CBigInt TmpSecond = _Second;
		TmpSecond.m_bIsNeg = true;
		*this += TmpSecond;
	}
	else 
	{
		if (*this > _Second)
		{
			_Subtract(*this, _Second);
			m_bIsNeg = false;
		}
		else 
		{
			_Subtract(_Second, *this);
			m_bIsNeg = true;
		}
	}

	*this = std::move(result);
	return *this;
};

CBigInt const CBigInt::operator--(int)
{
	CBigInt tmp(*this);

	//operator--();
	--(*this);

	return tmp;
};

CBigInt const &CBigInt::operator--()
{
	if (!m_bIsNeg && m_pNumber->size() == 1 && *m_pNumber->begin() == 0)
	{
		m_bIsNeg = true;
		*m_pNumber->begin() = 1;

		return *this;
	}

	if (m_bIsNeg)
	{
		m_bIsNeg = false;
		++(*this);
		//operator++();

		if (*m_pNumber->begin())
			m_bIsNeg = true;

		return *this;
	}

	int nCarrier = 1;

	for (int i = 0; i < (int)m_pNumber->size() && nCarrier; i++)
	{
		if (!(*m_pNumber)[i])
		{
			(*m_pNumber)[i] = 9;
			nCarrier = 1;
		}
		else
		{
			(*m_pNumber)[i]--;
			nCarrier = 0;
		}
	}

	ClearZeroes(*this);

	return *this;
};

CBigInt const &CBigInt::operator*=(CBigInt const &_Second)
{
	CBigInt result;

	result.m_bIsNeg = m_bIsNeg ^  _Second.m_bIsNeg;

	for (int i = 0; i < (int)_Second.m_pNumber->size(); i++)
	{
		int nCarrier = 0;
		CBigInt k;

		for (int j = 0; j < i; j++)
			k.m_pNumber->push_back(0);

		for (int j = 0; j < (int)m_pNumber->size(); j++)
		{
			int nX = m_pNumber->at(j);
			int nY = _Second.m_pNumber->at(i);

			int llR = nX * nY + nCarrier;
			k.m_pNumber->push_back(llR % 10);
			nCarrier = llR / 10;
		}

		if (nCarrier)
			k.m_pNumber->push_back((int)nCarrier);

		result += k;
	}

	*this = std::move(result);
	return *this;
};

CBigInt const operator*(CBigInt const &_First, CBigInt const &_Second)
{
	CBigInt result(_First);
	result *= _Second;
	return result;
};

CBigInt const &CBigInt::operator=(CBigInt const &_Number)
{
	if (this != &_Number)
	{
		m_bIsNeg = _Number.m_bIsNeg;
		m_pNumber->assign(_Number.m_pNumber->begin(), _Number.m_pNumber->end());
	}

	return *this;
};

CBigInt const &CBigInt::operator=(CBigInt &&_Number)
{
	if (this != &_Number)
	{
		m_bIsNeg = _Number.m_bIsNeg;
		m_pNumber = _Number.m_pNumber;
		_Number.m_pNumber = nullptr;
	}

	return *this;
};

std::ostream &operator<<(std::ostream &_output, CBigInt const &_Number)
{
	std::string result;
	for (CBigInt::CHARDEQ::reverse_iterator it = _Number.m_pNumber->rbegin(), itEnd = _Number.m_pNumber->rend(); it != itEnd; it++)
	{
		result.push_back(*it + '0');
	}

	if (_Number.m_bIsNeg)
		_output << '-';
	_output << result;

	return _output;
};

bool operator==(CBigInt const &_First, CBigInt const &_Second)
{
	if (_First.m_bIsNeg != _Second.m_bIsNeg)
		return false;

	if (_First.m_pNumber->size() != _Second.m_pNumber->size())
		return false;

	for (int i = 0; i < (int)_First.m_pNumber->size(); i++)
	{
		if ((*_First.m_pNumber)[i] != (*_Second.m_pNumber)[i])
			return false;
	}

	return true;
};

bool operator!=(CBigInt const &_First, CBigInt const &_Second)
{
	return !(_First == _Second);
};

bool operator<(CBigInt const &_First, CBigInt const &_Second)
{
	if (!_First.m_bIsNeg && _Second.m_bIsNeg)
		return false;
	if (_First.m_bIsNeg && !_Second.m_bIsNeg)
		return true;

	auto _CompareSmaller = [](CBigInt const &__First, CBigInt const &__Second) -> bool
	{
		for (int i = std::max(__First.m_pNumber->size(), __Second.m_pNumber->size()) - 1; i >= 0; i--)
		{
			int nX = (i >= (int)__First.m_pNumber->size()) ? 0 : (*__First.m_pNumber)[i];
			int nY = (i >= (int)__Second.m_pNumber->size()) ? 0 : (*__Second.m_pNumber)[i];

			if (nX != nY)
				return nX < nY;
		}

		return false;
	};

	if (_First.m_bIsNeg && _Second.m_bIsNeg)
	{
		return _CompareSmaller(_Second, _First);
	}

	return _CompareSmaller(_First, _Second);
};

bool operator>(CBigInt const &_First, CBigInt const &_Second)
{
	if (!_First.m_bIsNeg && _Second.m_bIsNeg)
		return false;
	if (_First.m_bIsNeg && !_Second.m_bIsNeg)
		return true;

	auto _CompareSmaller = [](CBigInt const &__First, CBigInt const &__Second) -> bool
	{
		for (int i = std::max(__First.m_pNumber->size(), __Second.m_pNumber->size()) - 1; i >= 0; i--)
		{
			int nX = (i >= (int)__First.m_pNumber->size()) ? 0 : (*__First.m_pNumber)[i];
			int nY = (i >= (int)__Second.m_pNumber->size()) ? 0 : (*__Second.m_pNumber)[i];

			if (nX != nY)
				return nX > nY;
		}

		return false;
	};

	if (_First.m_bIsNeg && _Second.m_bIsNeg)
	{
		return _CompareSmaller(_Second, _First);
	}

	return _CompareSmaller(_First, _Second);
};

bool operator<=(CBigInt const &_First, CBigInt const &_Second)
{
	return !(_First > _Second);
};

bool operator>=(CBigInt const &_First, CBigInt const &_Second)
{
	return !(_First < _Second);
};