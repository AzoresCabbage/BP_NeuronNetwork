#include "stdafx.h"
#include "sigmodfunction.h"

SigmodFunction::SigmodFunction(double _alpha):alpha(_alpha){}

//input:sigmod函数自变量x
//output:sigmod函数因变量y
double SigmodFunction::f(double x) const{
	return ( 1 / ( 1 + exp( -alpha * x ) ) );
}

//input:sigmod函数自变量x
//output:sigmod函数在x处的导数
double SigmodFunction::derivative(double x) const{
	double y = f( x );
	return ( alpha * y * ( 1 - y ) );
}

//input:sigmod函数因变量y
//output:sigmod函数当f(x) = y时的导数
double SigmodFunction::derivative2(double y) const{
	return alpha*y*(1-y);
}