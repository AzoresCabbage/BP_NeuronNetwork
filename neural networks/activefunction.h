#pragma once

#include "stdafx.h"

class ActiveFunction{
public:
	virtual double f(double x) const = 0;
	virtual double derivative(double x) const = 0;
	virtual double derivative2(double y) const = 0;
};