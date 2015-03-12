#pragma once

#include "stdafx.h"
#include "neuron.h"
#include "activefunction.h"
class Layer{
//private:
public:
	int inputCount;//该层的输入数，即上一层的神经元数目
	int neuronsCount;//该层的除了偏置项外神经元数目
	std::vector <Neuron> neuron;//该层神经元
	std::vector <double> output;//该层神经元激励值，有neuronsCount+1个
	std::vector <double> sum;
public:
	Layer(){}
	Layer(int _inputCount,int _neuronCount,ActiveFunction* fun);
	~Layer();
	std::vector<double> compute(std::vector <double> input);
	void randomize();
	Neuron& operator[] (int idx);
	int getNeuronsCount();
};