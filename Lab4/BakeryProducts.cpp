#include "BakeryProducts.h"

IBakeryProduct::IBakeryProduct() :
	m_fWeight(1.0f)
{
};

IBakeryProduct::IBakeryProduct(float const _fWeight) :
	m_fWeight(_fWeight)
{
};

IBakeryProduct::~IBakeryProduct() 
{
};



CBread::CBread() :
	IBakeryProduct()
{
};

CBread::CBread(float const _fWeight, std::string const &_sFilling) :
	IBakeryProduct(_fWeight),
	m_sFilling(_sFilling)
{
};

void CBread::Cook() const
{
	printf("Bread has cooked\n");
};


CBun::CBun() :
	IBakeryProduct()
{
};

CBun::CBun(float const _fWeight) :
	IBakeryProduct(_fWeight)
{
};

void CBun::Cook() const
{
	printf("Bun has cooked\n");
};



CRoll::CRoll() :
	IBakeryProduct()
{
};

CRoll::CRoll(float const _fWeight) :
	IBakeryProduct(_fWeight)
{
};

void CRoll::Cook() const
{
	printf("Roll has cooked\n");
};



CPikelet::CPikelet() :
	IBakeryProduct()
{
};

CPikelet::CPikelet(float const _fWeight, int const _nCherries) :
	IBakeryProduct(_fWeight),
	m_nCherries(_nCherries)
{
};

void CPikelet::Cook() const
{
	printf("Pikelet has cooked\n");
};