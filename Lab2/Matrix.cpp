#include "Matrix.h"
#include <iomanip>

CMatrix::CMatrix()
{
	m_pMatrix = new FLOATDOUBLEVECTOR;
}

CMatrix::CMatrix(int const _nWidth, int const _nHeight)
{
	m_pMatrix = new FLOATDOUBLEVECTOR;
	m_pMatrix->resize(_nHeight);

	for (int i = 0; i < _nHeight; i++)
	{
		(*m_pMatrix)[i] = new FLOATVECTOR;
		(*m_pMatrix)[i]->resize(_nWidth);
		std::fill((*m_pMatrix)[i]->begin(), (*m_pMatrix)[i]->end(), 0.0f);
	}
}

CMatrix::CMatrix(CMatrix const &_mSrc)
{
	if (this != &_mSrc)
	{
		*this = _mSrc;
	}
}

CMatrix::CMatrix(CMatrix &&_mSrc)
{
	if (this != &_mSrc)
	{
		m_pMatrix = _mSrc.m_pMatrix;
		_mSrc.m_pMatrix = nullptr;
	}
}

CMatrix::~CMatrix()
{
	if (m_pMatrix)
	{
		delete m_pMatrix;
		m_pMatrix = nullptr;
	}
}


CMatrix const &CMatrix::operator+=(CMatrix const &_mSecond)
{
	if (_mSecond.m_pMatrix->size() != m_pMatrix->size() || (*_mSecond.m_pMatrix)[0]->size() != (*m_pMatrix)[0]->size())
		return *this;

	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] += (*(*_mSecond.m_pMatrix)[i])[j];
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator-=(CMatrix const &_mSecond)
{
	if (_mSecond.m_pMatrix->size() != m_pMatrix->size() || (*_mSecond.m_pMatrix)[0]->size() != (*m_pMatrix)[0]->size())
		return *this;

	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] -= (*(*_mSecond.m_pMatrix)[i])[j];
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator*=(CMatrix const &_mSecond)
{
	if ((*m_pMatrix)[0]->size() != _mSecond.m_pMatrix->size())
		return *this;

	CMatrix mResult(m_pMatrix->size(), (*_mSecond.m_pMatrix)[0]->size());

	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*_mSecond.m_pMatrix)[0]->size(); j++)
		{
			for (size_t r = 0; r < (*m_pMatrix)[0]->size(); r++)
			{
				mResult[i][j] += (*(*m_pMatrix)[i])[r] * (*(*_mSecond.m_pMatrix)[r])[j];
			}
		}
	}

	*this = mResult;

	return *this;
}

CMatrix const &CMatrix::operator=(CMatrix const &_mSrc)
{
	if (this != &_mSrc)
	{
		m_pMatrix = new FLOATDOUBLEVECTOR;
		m_pMatrix->resize(_mSrc.m_pMatrix->size());

		for (size_t i = 0; i < _mSrc.m_pMatrix->size(); i++)
		{
			(*m_pMatrix)[i] = new FLOATVECTOR;
			(*m_pMatrix)[i]->resize((*_mSrc.m_pMatrix)[0]->size());

			(*m_pMatrix)[i]->assign((*_mSrc.m_pMatrix)[i]->begin(), (*_mSrc.m_pMatrix)[i]->end());
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator=(CMatrix &&_mSrc)
{
	if (this != &_mSrc)
	{
		m_pMatrix = _mSrc.m_pMatrix;
		_mSrc.m_pMatrix = nullptr;
	}

	return *this;
}

CMatrix const &CMatrix::operator+=(float const _fNumber)
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] += _fNumber;
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator-=(float const _fNumber)
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] -= _fNumber;
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator*=(float const _fNumber)
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] *= _fNumber;
		}
	}

	return *this;
}

CMatrix const &CMatrix::operator=(float const _fNumber)
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		std::fill((*m_pMatrix)[i]->begin(), (*m_pMatrix)[i]->end(), _fNumber);
	}

	return *this;
}


CMatrix const CMatrix::operator-()
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] = -(*(*m_pMatrix)[i])[j];
		}
	}

	return *this;
}

CMatrix const CMatrix::operator+() const
{
	for (size_t i = 0; i < m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*m_pMatrix)[0]->size(); j++)
		{
			(*(*m_pMatrix)[i])[j] = (*(*m_pMatrix)[i])[j];
		}
	}

	return *this;
}

CMatrix::FLOATVECTOR &CMatrix::operator[](size_t const _nElement) const
{
	if (m_pMatrix->size() > _nElement)
		return (*(*m_pMatrix)[_nElement]);

	return *(new FLOATVECTOR());
}

CMatrix const operator+(CMatrix const &_mFirst, CMatrix const &_mSecond)
{
	CMatrix mResult(_mFirst);

	mResult += _mSecond;

	return mResult;
}

CMatrix const operator-(CMatrix const &_mFirst, CMatrix const &_mSecond)
{
	CMatrix mResult(_mFirst);

	mResult -= _mSecond;

	return mResult;
}

CMatrix const operator*(CMatrix const &_mFirst, CMatrix const &_mSecond)
{
	CMatrix mResult(_mFirst);

	mResult *= _mSecond;

	return mResult;
}

CMatrix const operator+(CMatrix const &_mFirst, float const _fNumber)
{
	CMatrix mResult(_mFirst);

	mResult += _fNumber;

	return mResult;
}

CMatrix const operator-(CMatrix const &_mFirst, float const _fNumber)
{
	CMatrix mResult(_mFirst);

	mResult -= _fNumber;

	return mResult;
}

CMatrix const operator*(CMatrix const &_mFirst, float const _fNumber)
{
	CMatrix mResult(_mFirst);

	mResult *= _fNumber;

	return mResult;
}


std::ostream &operator<<(std::ostream &_output, CMatrix const &_mSrc)
{
	//_output << std::setw(6);

	for (size_t i = 0; i < _mSrc.m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*_mSrc.m_pMatrix)[0]->size(); j++)
		{
			_output << std::setw(6) << (*(*_mSrc.m_pMatrix)[i])[j];
		}

		_output << std::endl;
	}

	return _output;
}


bool operator==(CMatrix const &_mFirst, CMatrix const &_mSecond)
{
	if (_mSecond.m_pMatrix->size() != _mFirst.m_pMatrix->size() || (*_mSecond.m_pMatrix)[0]->size() != (*_mFirst.m_pMatrix)[0]->size())
		return false;

	for (size_t i = 0; i < _mFirst.m_pMatrix->size(); i++)
	{
		for (size_t j = 0; j < (*_mFirst.m_pMatrix)[0]->size(); j++)
		{
			if ((*(*_mFirst.m_pMatrix)[i])[j] != (*(*_mSecond.m_pMatrix)[i])[j])
				return false;
		}
	}

	return true;
}

bool operator!=(CMatrix const &_mFirst, CMatrix const &_mSecond)
{
	return !(_mFirst == _mSecond);
}