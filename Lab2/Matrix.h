#ifndef _H__MATRIX
#define _H__MATRIX

#include <iostream>
#include <vector>

class CMatrix
{
private:
	typedef std::vector<float> FLOATVECTOR;
	typedef std::vector<std::vector<float> *> FLOATDOUBLEVECTOR;
public:
	CMatrix();
	CMatrix(int const _nWidth, int const _nHeight);
	CMatrix(CMatrix const &_mSrc);
	CMatrix(CMatrix &&_mSrc);
	~CMatrix();

	CMatrix const &operator+=(CMatrix const &_mSecond);
	CMatrix const &operator-=(CMatrix const &_mSecond);
	CMatrix const &operator*=(CMatrix const &_mSecond);
	CMatrix const &operator=(CMatrix const &_mSrc);
	CMatrix const &operator=(CMatrix &&_mSrc);
	CMatrix const &operator=(float const _fNumber);
	CMatrix const &operator+=(float const _fNumber);
	CMatrix const &operator-=(float const _fNumber);
	CMatrix const &operator*=(float const _fNumber);

	CMatrix const operator-();
	CMatrix const operator+() const;

	//float operator[](size_t const _nElement) const;
	FLOATVECTOR &operator[](size_t const _nElement) const;

	friend CMatrix const operator+(CMatrix const &_mFirst, CMatrix const &_mSecond);
	friend CMatrix const operator-(CMatrix const &_mFirst, CMatrix const &_mSecond);
	friend CMatrix const operator*(CMatrix const &_mFirst, CMatrix const &_mSecond);
	friend CMatrix const operator+(CMatrix const &_mFirst, float const _fNumber);
	friend CMatrix const operator-(CMatrix const &_mFirst, float const _fNumber);
	friend CMatrix const operator*(CMatrix const &_mFirst, float const _fNumber);

	friend std::ostream &operator<<(std::ostream &_output, CMatrix const &_mSrc);

	friend bool operator==(CMatrix const &_mFirst, CMatrix const &_mSecond);
	friend bool operator!=(CMatrix const &_mFirst, CMatrix const &_mSecond);
private:
	FLOATDOUBLEVECTOR *m_pMatrix;
};

#endif