#pragma once

#include "stdafx.h"
#include "random.h"
#include "activefunction.h"

class Neuron{
private:
	int inputCount;//ָ�����Ԫ�ı���
	std::vector <double> weight;//Ȩ��,weight[i]Ϊ��iָ��ýڵ�ı�Ȩ��
	double output;//����ֵ��������sigmod����ӳ���Ľ��
	double threshold;//ƫ����
	ActiveFunction* func;//��������
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