#include "stdafx.h"
#include "random.h"

using namespace std;


Random& ran(){
	static Random Ran;
	return Ran;
}

Random::Random(){
	PI = acos(-1.0);
	srand((unsigned int)time(NULL));
}

double Random::AverageRandom(double Min,double Max){
	int MinInteger = (int)(Min*10000);
	int MaxInteger = (int)(Max*10000);
	int randInteger = rand()*rand();
	int diffInteger = MaxInteger - MinInteger;
	int resultInteger = randInteger % diffInteger + MinInteger;
	return resultInteger/10000.0;
}

double Random::Normal(double x,double miu,double sigma) {
	return 1.0/sqrt(2*PI*sigma) * exp(-1*(x-miu)*(x-miu)/(2*sigma*sigma));
}

double Random::NormalRandom(double miu,double sigma,double Min,double Max){
	double x,y,d;
	do{
		x = AverageRandom(Min,Max);
		y = Normal(x, miu, sigma);
		d = AverageRandom(0, Normal(miu,miu,sigma));
	}while( d > y );
	return x;
}
