#pragma once
#include "stdafx.h"
#include "supervisedlearning.h"
#include "network.h"

class BPLearning:public SupervisedLearing{
private:
	Network network;
	double learningRate;
	double momentum;

	double ** neuronError;
	double ** thresholdUpdate;
	double ***weightUpdate;

	double calcError(std::vector <double>);
	void calcUpdate(std::vector <double>);
	void update();
	void clear();
	void see();
public:
	BPLearning(Network _nw,double _learningRate,double _momentum);
	~BPLearning();
	virtual double run(std::vector <double> input,std::vector <double> output);
	virtual double runAll(std::vector < std::vector <double> > input,std::vector < std::vector <double> > output);
	std::vector <double> calc(std::vector <double> input);
};