#include "stdafx.h"
#include "layer.h"

Layer::Layer(int _inputCount,int _neuronsCount,ActiveFunction* fun):inputCount(_inputCount),neuronsCount(_neuronsCount){
	inputCount = std::max(1,inputCount);
	neuronsCount = std::max(1,neuronsCount);

	neuron.resize(neuronsCount);
	output.resize(neuronsCount);
	sum.resize(neuronsCount);

	for(int i=0;i<neuronsCount;++i){
		neuron[i] = Neuron(inputCount,fun);
	}
}

Layer::~Layer(){
	inputCount = 0;
	neuronsCount = 0;
}

std::vector<double> Layer::compute(std::vector <double> input){
	//计算指向某个神经元的所有边权和
	for(int i=0;i<neuronsCount;++i){
		output[i] = neuron[i].compute(input);
		sum[i] = neuron[i].sum;
	}
	return output;
}

void Layer::randomize(){
	for(int i=0;i<neuronsCount;++i){
		neuron[i].randomize();
	}
}

Neuron& Layer::operator[] (int idx){
	return neuron[idx];
}

int Layer::getNeuronsCount(){
	return neuronsCount;
}