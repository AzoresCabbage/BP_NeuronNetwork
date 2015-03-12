#include "stdafx.h"
#include "BPLearning.h"
#include "sigmodfunction.h"

void BPLearning::clear(){
	int layerCount = network.layerCount;
	for(int i=0;i<layerCount;++i){
		Layer layer = network[i];
		int neuronCount = layer.neuronsCount;
		memset(neuronError[i],0,sizeof(double)*neuronCount);
		memset(thresholdUpdate[i],0,sizeof(double)*neuronCount);
		for(int j=0;j<neuronCount;++j){
			memset(weightUpdate[i][j],0,sizeof(double)*(layer.inputCount));
		}
	}
}

void BPLearning::see(){
	puts("This is see:");
	int layerCount = network.layerCount;
	for(int i=0;i<layerCount;++i){
		Layer layer = network[i];
		int neuronCount = layer.neuronsCount;
		for(int j=0;j<neuronCount;++j){
			for(int k=0;k<layer.inputCount;++k){
				printf("%lf ",weightUpdate[i][j][k]);
			}
		}
	}
	puts("");
}

BPLearning::BPLearning(Network _nw,double _learningRate,double _momentum):network(_nw),learningRate(_learningRate),momentum(_momentum){
	int layerCount = _nw.layerCount;
	/*neuronError.resize(layerCount);
	weightUpdate.resize(layerCount);
	thresholdUpdate.resize(layerCount);*/
	neuronError = new double*[layerCount];
	weightUpdate = new double**[layerCount];
	thresholdUpdate = new double*[layerCount];
	for(int i=0;i<layerCount;++i){
		Layer layer = network[i];
		int neuronCount = layer.neuronsCount;
		/*neuronError[i].resize(neuronCount);
		weightUpdate[i].resize(neuronCount);
		thresholdUpdate[i].resize(neuronCount);*/
		neuronError[i] = new double[neuronCount];
		weightUpdate[i] = new double*[neuronCount];
		thresholdUpdate[i] = new double[neuronCount];
		memset(neuronError[i],0,sizeof(double)*neuronCount);
		memset(thresholdUpdate[i],0,sizeof(double)*neuronCount);
		for(int j=0;j<neuronCount;++j){
			/*weightUpdate[i][j].resize(layer.inputCount);*/
			weightUpdate[i][j] = new double[layer.inputCount];
			memset(weightUpdate[i][j],0,sizeof(double)*(layer.inputCount));
			/*for(int k=0;k<layer.inputCount;++k){
				printf("%lf ",weightUpdate[i][j][k]);
			}*/
		}
	}
}

BPLearning::~BPLearning(){
	momentum = 0.0;
	int layerCount = network.layerCount;

	for(int i=0;i<layerCount;++i){
		Layer layer = network[i];
		int neuronCount = layer.neuronsCount;
		for(int j=0;j<neuronCount;++j){
			delete weightUpdate[i][j];
		}
		delete []weightUpdate[i];
		delete []neuronError[i];
		delete []thresholdUpdate[i];
	}
	delete []neuronError;
	delete []weightUpdate;
	delete []thresholdUpdate;
}

double BPLearning::run(std::vector <double> input,std::vector <double> output){
	//ÕýÏò¼ÆËã

	for(int i=0,n=(int)output.size();i<n;++i)
		output[i] = network.fun->f(output[i]);

	network.compute(input);
	
	double sumError = calcError(output);
	
	calcUpdate(input);

	update();

	return sumError;
}

double BPLearning::runAll(std::vector < std::vector <double> > input,std::vector < std::vector <double> > output){
	
	/*printf("before run weight:\n");
	for(int i=0,n=network.layerCount;i<n;++i){
		for(int j=0,m=network[i].neuronsCount;j<m;++j){
			for(int k=0,p=network[i][j].getInputCount();k<p;++k){
				printf("%lf ",network[i][j][k]);
			}
			printf(" || ");
		}
		printf("\n\n");
	}*/
	
	int inputSize = (int)input.size();
	double error = 0;
	for(int i=0;i<inputSize;++i){
		double tmp = run(input[i],output[i]);
		error += tmp;
		//printf("%lf ",tmp);
	}
	
	//printf("\n");
	/*printf("after weight:\n");
	for(int i=0,n=network.layerCount;i<n;++i){
		for(int j=0,m=network[i].neuronsCount;j<m;++j){
			for(int k=0,p=network[i][j].getInputCount();k<p;++k){
				printf("%lf ",network[i][j][k]);
			}
			printf(" || ");
		}
		printf("\n\n");
	}*/
	//clear();
	//puts("");
	return error;
}

double BPLearning::calcError(std::vector <double> ans){
	Layer layer,layerNxt;
	/*std::vector <double> errors,errorsNxt;*/
	double* errors,*errorsNxt;
	double error = 0.0,e,sum;
	double output;
	int layerCount = network.layerCount;
	ActiveFunction *fun = network.fun;

	layer = network[layerCount-1];
	errors = neuronError[layerCount-1];
	for(int i=0,n=layer.neuronsCount;i<n;++i){
		output = layer[i].getOutput();
		e = ans[i] - output;
		errors[i] = e*fun->derivative2(output);

		//printf("%lf ",neuronError[layerCount-1][i]);

		error += (e*e);
	}

	//puts("");

	for(int j=layerCount-2;j>=0;--j){
		layer = network[j];
		layerNxt = network[j+1];
		errors = neuronError[j];
		errorsNxt = neuronError[j+1];
		for(int i=0,n=layer.neuronsCount;i<n;++i){
			sum = 0.0;
			for(int k=0,m=layerNxt.neuronsCount;k<m;++k){
				sum += errorsNxt[k]*layerNxt[k][i];
			}
			errors[i] = sum*fun->derivative2(layer[i].getOutput());
			//printf("%lf ",neuronError[j][i]);
		}
		//puts("");
	}
	return error/2.0;
}

void BPLearning::calcUpdate(std::vector <double> input){
	
	Neuron neuron;
	Layer layer,layerPre;
	/*std::vector < std::vector <double> > layerWeightUpdate;
	std::vector <double> layerThresholdUpdate;
	std::vector <double> errors;
	std::vector <double> neuronWeightUpdate;*/
	double ** layerWeightUpdate;
	double * layerThresholdUpdate;
	double * errors;
	double * neuronWeightUpdate;

	double error;

	layer = network[0];
	errors = neuronError[0];
	layerWeightUpdate = weightUpdate[0];
	layerThresholdUpdate = thresholdUpdate[0];

	for(int i=0,n=layer.neuronsCount;i<n;++i){
		neuron = layer[i];
		error = errors[i];
		neuronWeightUpdate = layerWeightUpdate[i];
		for(int j=0,m=neuron.getInputCount();j<m;++j){
			neuronWeightUpdate[j] = learningRate*(
				momentum*neuronWeightUpdate[j]
			+(1.0 - momentum)*error*input[j]
				);
		}
		layerThresholdUpdate[i] = learningRate*(
			momentum*layerThresholdUpdate[i]
		+(1.0 - momentum)*error
			);
	}

	for(int k=1,l=network.layerCount;k<l;++k){
		layerPre = network[k-1];
		layer = network[k];
		errors = neuronError[k];
		layerWeightUpdate = weightUpdate[k];
		layerThresholdUpdate = thresholdUpdate[k];
		for(int i=0,n=layer.neuronsCount;i<n;++i){
			neuron = layer[i];
			error = errors[i];
			neuronWeightUpdate = layerWeightUpdate[i];
			for(int j=0,m=neuron.getInputCount();j<m;++j){
				neuronWeightUpdate[j] = 
					learningRate*(
					momentum*neuronWeightUpdate[j]
				+(1.0 - momentum)*error*layerPre[j].getOutput()
					);
			}
			layerThresholdUpdate[i] = learningRate*(
				momentum*layerThresholdUpdate[i]
			+(1.0 - momentum)*error
				);
		}
	}
}

void BPLearning::update(){
	
	/*std::vector < std::vector <double> > layerWeightUpdate;
	std::vector <double> layerThresholdUpdate;
	std::vector <double> neuronWeightUpdate;*/
	
	double ** layerWeightUpdate;
	double * layerThresholdUpdate;
	double * neuronWeightUpdate;

	//see();

	for(int i=0,n=network.layerCount;i<n;++i){
		Layer& layer = network[i];
		//std::cout<<(&layer)<<std::endl;
		//std::cout<<(&network[i])<<std::endl;

		layerWeightUpdate = weightUpdate[i];
		layerThresholdUpdate = thresholdUpdate[i];
		for(int j=0,m=layer.neuronsCount;j<m;++j){
			Neuron& neuron = layer[j];
			neuronWeightUpdate = layerWeightUpdate[j];
			for(int k=0,s=neuron.getInputCount();k<s;++k){
				neuron.addWeight(k , neuronWeightUpdate[k]);
			}
			neuron.addThreshold(layerThresholdUpdate[j]);
		}
	}
}

std::vector <double> BPLearning::calc(std::vector <double> input){
	network.compute(input);
	return network[network.layerCount-1].sum;
}