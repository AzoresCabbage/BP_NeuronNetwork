#pragma once
#include "stdafx.h"
#include "layer.h"
#include "activefunction.h"

class Network{
//private:
public:
	int inputCount;//输入层参数个数
	int layerCount;//不计输入层的层数
	ActiveFunction* fun;
	std::vector <Layer> layer;//层，没有输入层
	std::vector <double> output;//输出层值
public:
	Network(int _inputCount,int _layerCount,ActiveFunction* fun,int neuronCount[]);
	~Network();
	std::vector <double> compute(std::vector <double> input);
	void randomize();
	double getOutputByIdx(int idx);
	int getlayerCount();
	Layer& operator[](int idx);
};