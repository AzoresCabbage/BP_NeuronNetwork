#pragma once

#include "stdafx.h"
#include "neuron.h"
#include "activefunction.h"
class Layer{
//private:
public:
	int inputCount;//�ò��������������һ�����Ԫ��Ŀ
	int neuronsCount;//�ò�ĳ���ƫ��������Ԫ��Ŀ
	std::vector <Neuron> neuron;//�ò���Ԫ
	std::vector <double> output;//�ò���Ԫ����ֵ����neuronsCount+1��
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