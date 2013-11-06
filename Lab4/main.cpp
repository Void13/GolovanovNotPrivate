#include <stdio.h>
#include <conio.h>
#include <memory.h>

#include "BakeryFactory.h"
#include "BakeryProducts.h"

#ifdef _DEBUG
	#include <crtdbg.h>
	#define _CRTDBG_MAP_ALLOC
	#define new new( _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int main()
{
#ifdef _DEBUG
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	_CrtDumpMemoryLeaks();
#endif

	CFactory<IBakeryProduct> Factory;

	Factory.RegisterClass<CBread>("Bread");
	Factory.RegisterClass<CBun>("Bun");
	Factory.RegisterClass<CRoll>("Roll");
	Factory.RegisterClass<CPikelet>("Pikelet");

	IBakeryProduct const *const pBakeries[4] = 
	{
		Factory.CreateInstance("Bread"),
		Factory.CreateInstance("Bun"),
		Factory.CreateInstance("Pikelet"),
		Factory.CreateInstance("Roll")
	};

	for (int i = 0; i < 4; i++)
		pBakeries[i]->Cook();

	for (int i = 0; i < 4; i++)
		delete pBakeries[i];

	_getch();
	return 0;
}