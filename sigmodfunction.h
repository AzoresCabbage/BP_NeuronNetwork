#pragma once

#include "stdafx.h"
#include "activefunction.h"

class SigmodFunction:public ActiveFunction{
private:
	double alpha;//coef of exp
public:
	SigmodFunction(double _alpha);
	virtual double f(double x) const;
	virtual double derivative(double x) const;
	virtual double derivative2(double y) const;
};