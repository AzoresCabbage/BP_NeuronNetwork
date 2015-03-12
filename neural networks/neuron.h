#pragma once

#include "stdafx.h"
#include "random.h"
#include "activefunction.h"

class Neuron{
private:
	int inputCount;//指向该神经元的边数
	std::vector <double> weight;//权重,weight[i]为从i指向该节点的边权重
	double output;//激励值，即经过sigmod函数映射后的结果
	double threshold;//偏置项
	ActiveFunction* func;//激励函数
public:
	double sum;
	Neuron(){}
	Neuron(int inputs,ActiveFunction* _func);
	~Neuron();

	double operator [](const int idx) const;
	double compute(std::vector <double> input);

	double getOutput();
	int getInputCount();
	void addWeight(int idx,double val);
	void addThreshold(double val);
	void randomize();
};