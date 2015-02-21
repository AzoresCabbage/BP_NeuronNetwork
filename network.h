#pragma once
#include "stdafx.h"
#include "layer.h"
#include "activefunction.h"

class Network{
//private:
public:
	int inputCount;//������������
	int layerCount;//���������Ĳ���
	ActiveFunction* fun;
	std::vector <Layer> layer;//�㣬û�������
	std::vector <double> output;//�����ֵ
public:
	Network(int _inputCount,int _layerCount,ActiveFunction* fun,int neuronCount[]);
	~Network();
	std::vector <double> compute(std::vector <double> input);
	void randomize();
	double getOutputByIdx(int idx);
	int getlayerCount();
	Layer& operator[](int idx);
};