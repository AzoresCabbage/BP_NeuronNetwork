#pragma once
#include "stdafx.h"

class SupervisedLearing{
public:
	virtual double run(std::vector <double> input,std::vector <double> output) = 0;
	virtual double runAll(std::vector < std::vector <double> > input,std::vector < std::vector <double> > output) = 0;
};