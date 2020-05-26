#include <iostream>
#include "Date.h"


int main()
{
	Date a1(03, 05, 2020);
	Date a4 = a1 + 2000 ;
	a4.PrintInfoDate();
}