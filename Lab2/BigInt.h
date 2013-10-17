#ifndef _H__BIGINT
#define _H__BIGINT

#include <memory.h>
#include <iostream>
#include <deque>
#include <string>

//#define DEBUG_CONSTR 1

class CBigInt
{
private:
	typedef std::deque<char> CHARDEQ;
public:
	CBigInt();
	CBigInt(int const _nNumber);
	CBigInt(std::string const _sNumber);
	CBigInt(CBigInt const &_SourceNumber);
	CBigInt(CBigInt &&_SourceNumber);
	~CBigInt();

	friend void ClearZeroes(CBigInt &_Number);

	CBigInt const &operator+=(CBigInt const &_Second);
	CBigInt const &operator-=(CBigInt const &_Second);
	CBigInt const &operator*=(CBigInt const &_Second);
	CBigInt const &operator=(CBigInt const &_Number);
	CBigInt const &operator=(CBigInt &&_Number);
	CBigInt const &operator--();
	CBigInt const &operator++();

	CBigInt const operator++(int);
	CBigInt const operator--(int);
	CBigInt const operator-() const;
	CBigInt const operator+() const;

	friend CBigInt const operator+(CBigInt const &_First, CBigInt const &_Second);
	friend CBigInt const operator-(CBigInt const &_First, CBigInt const &_Second);
	friend CBigInt const operator*(CBigInt const &_First, CBigInt const &_Second);

	friend std::ostream &operator<<(std::ostream &_output, CBigInt const &_Number);

	friend bool operator==(CBigInt const &_First, CBigInt const &_Second);
	friend bool operator!=(CBigInt const &_First, CBigInt const &_Second);
	friend bool operator<(CBigInt const &_First, CBigInt const &_Second);
	friend bool operator>(CBigInt const &_First, CBigInt const &_Second);
	friend bool operator<=(CBigInt const &_First, CBigInt const &_Second);
	friend bool operator>=(CBigInt const &_First, CBigInt const &_Second);
private:
	CHARDEQ *m_pNumber;
	bool m_bIsNeg;
};

#endif