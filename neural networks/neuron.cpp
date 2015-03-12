#include "stdafx.h"
#include "neuron.h"

Neuron::Neuron(int inputs,ActiveFunction* _func):inputCount(inputs),func(_func){
	threshold = 0.0;
	inputCount = std::max(1,inputCount);
	weight.resize(inputCount);
	randomize();
}

Neuron::~Neuron(){
	threshold = 0.0;
	func = NULL;
	inputCount = 0;
	output = 0;
}

double Neuron::compute(std::vector <double> input){
	sum = 0.0;
	for(int i=0;i<inputCount;++i){
		sum += input[i]*weight[i];
	}
	sum += threshold;
	return output = func->f(sum);
}

void Neuron::randomize(){
	for(int i=0;i<inputCount;++i){
		weight[i] = ran().NormalRandom(0.0,0.1,0.0,1.0);
		//printf("%lf ",weight[i]);
	}
	//printf("\n");
}

double Neuron::getOutput(){
	return output;
}

double Neuron::operator [](const int idx) const{
	return weight[idx];
}

void Neuron::addWeight(int idx,double val){
	weight[idx] += val;
}

void Neuron::addThreshold(double val){
	threshold += val;
}

int Neuron::getInputCount(){
	return inputCount;
}