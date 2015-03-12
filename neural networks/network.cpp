#include "stdafx.h"
#include "network.h"

Network::Network(int _inputCount,int _layerCount,ActiveFunction* _fun,int neuronCount[]):inputCount(_inputCount),layerCount(_layerCount),fun(_fun){
	inputCount = std::max(1,inputCount);
	layerCount = std::max(1,layerCount);
	layer.resize(layerCount);

	for(int i=0;i<layerCount;++i){
		layer[i] = Layer(
			i==0?inputCount:neuronCount[i-1],
			neuronCount[i],
			_fun
			);
	}
}

Network::~Network(){
	inputCount = 0;
	layerCount = 0;
}

std::vector <double> Network::compute(std::vector <double> input){
	output = input;
	for(int i=0;i<layerCount;++i){
		output = layer[i].compute(output);
	}
	return output;
}

void Network::randomize(){
	for(int i=0;i<layerCount;++i){
		layer[i].randomize();
	}
}

double Network::getOutputByIdx(int idx){
	return output[idx];
}

Layer& Network::operator[](int idx){
	return layer[idx];
}

int Network::getlayerCount(){
	return layerCount;
}