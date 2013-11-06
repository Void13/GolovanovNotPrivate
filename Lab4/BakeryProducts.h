#ifndef _H__BAKERYPROD
#define _H__BAKERYPROD

#include <stdio.h>
#include <string>

class IBakeryProduct
{
public:
	IBakeryProduct();
	IBakeryProduct(float const _fWeight);
	virtual ~IBakeryProduct();

	virtual void Cook() const = 0;

	float m_fWeight;
};

class CBread : public IBakeryProduct
{
public:
	CBread();
	CBread(float const _fWeight, std::string const &_sFilling);
	void Cook() const;

	std::string m_sFilling;
};

class CBun : public IBakeryProduct
{
public:
	CBun();
	CBun(float const _fWeight);

	void Cook() const;
};

class CRoll : public IBakeryProduct
{
public:
	CRoll();
	CRoll(float const _fWeight);

	void Cook() const;
};

class CPikelet : public IBakeryProduct
{
public:
	CPikelet();
	CPikelet(float const _fWeight, int const _nCherries);

	void Cook() const;

	int m_nCherries;
};

#endif