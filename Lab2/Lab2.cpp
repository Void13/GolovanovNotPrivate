#include <stdio.h>
#include <conio.h>
#include <iostream>

#define TASK1

#ifndef TASK1
#include "Matrix.h"

int main() 
{
	CMatrix a;
	CMatrix b(2, 2);
	CMatrix c(3, 3);

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++) 
			b[i][j] = (float)i + j;

	a = 2;

	b *= 2;
	b = a = b + b; 

	if (a != b) 
		std::cout << "Something wrong\n";
	else 
		std::cout << "As expected\n";

	b += c;    

	std::cout << a << std::endl;
	std::cout << c << std::endl;
	std::cout << b << std::endl;

	//_getch();
	return 0;
}
#endif

#ifdef TASK1
#include "BigInt.h"

int main()
{
	CBigInt a;
	CBigInt b("-1206");
	CBigInt c(1207);

	a = c;
	if (a == c) 
		std::cout << "\nAs expected\n";
	else 
		std::cout << "\nSomething wrong\n";

	if (b >= c) 
		std::cout << "\nSomething wrong...\n";
	else 
		std::cout << "\nAs expected\n";

	std::cout << b++ << std::endl;
	std::cout << c - 1 << std::endl;
	std::cout << (b += 7) << std::endl;

	_getch();
	return 0;
}
#endif