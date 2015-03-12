#include "stdafx.h"
#include "sigmodfunction.h"

SigmodFunction::SigmodFunction(double _alpha):alpha(_alpha){}

//input:sigmod�����Ա���x
//output:sigmod���������y
double SigmodFunction::f(double x) const{
	return ( 1 / ( 1 + exp( -alpha * x ) ) );
}

//input:sigmod�����Ա���x
//output:sigmod������x���ĵ���
double SigmodFunction::derivative(double x) const{
	double y = f( x );
	return ( alpha * y * ( 1 - y ) );
}

//input:sigmod���������y
//output:sigmod������f(x) = yʱ�ĵ���
double SigmodFunction::derivative2(double y) const{
	return alpha*y*(1-y);
}