// pixel-testbed.cpp : Builds a 2-3-4 binary search tree and uses 
// hardware concurrent threads (multicore) to distribute the loads.
// to measure the performance metrics.
// this is an experimental test bed.

#include "stdafx.h"
#include "di_testbed.h"

using namespace pixelda;

int main()
{
	di_testbed di;

	di.measure_tree_construction_performance();

    return 0;
}

