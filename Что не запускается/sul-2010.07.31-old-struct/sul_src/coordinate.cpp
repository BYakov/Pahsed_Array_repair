#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <string>
#include <istream>
#include <fstream>
#include <iomanip>

#ifndef _COORDINATE_H_
#include "coordinate.h"
#endif

using namespace std;

///////////////////////////////////////////////////////////////////////////////

coordinate::coordinate()
{
	dv = val = 0;
}

///////////////////////////////////////////////////////////////////////////////

coordinate::coordinate(double V, double dV)
{
	val = V;
	dv = dV;
}

///////////////////////////////////////////////////////////////////////////////

coordinate::~coordinate()
{
}

///////////////////////////////////////////////////////////////////////////////

double coordinate::inc()
{
	val += dv;
	return val;
}

///////////////////////////////////////////////////////////////////////////////

double coordinate::dec()
{
	val -= dv;
	return val;
}

///////////////////////////////////////////////////////////////////////////////
