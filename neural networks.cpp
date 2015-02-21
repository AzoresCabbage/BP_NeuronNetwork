// neural networks.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "network.h"
#include "BPLearning.h"
#include "sigmodfunction.h"
#include "activefunction.h"
#include <fstream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[]){

#define CASENUM 4

	vector < vector<double> > input,output;
	for(int i=1;i<=CASENUM;++i){

		char num[10];
		sprintf_s(num,"%d",i);
		int len = strlen(num);
		num[len++] = '.';
		num[len++] = 'i';
		num[len++] = 'n';
		num[len++] = '\0';
		ifstream fin(num);
		double tmp;
		vector <double> cur;
		while(fin>>tmp){
			cur.push_back(tmp);
		}
		fin.close();

		input.push_back(cur);
		cur.clear();

		sprintf_s(num,"%d",i);
		len = strlen(num);
		num[len++] = '.';
		num[len++] = 'o';
		num[len++] = 'u';
		num[len++] = 't';
		num[len++] = '\0';

		fin.open(num);
		while(fin>>tmp){
			cur.push_back(tmp);
		}
		fin.close();

		output.push_back(cur);
		cur.clear();
	}
	int neurons[3] = {4,4,4};

	BPLearning NN(
		Network(4,3,new SigmodFunction(2),neurons),
		1,0.0
		);
	//NN.run(input[0],output[0]);
	for(int i=0;i<2000;++i)
		//NN.runAll(input,output);
		printf("case %d's error is %lf\n",i,NN.runAll(input,output));;
	vector <double> data;
	data.push_back(0);
	data.push_back(1);
	data.push_back(0);
	data.push_back(0);
	vector <double> res = NN.calc(data);
	for(int i=0;i<(int)res.size();++i)
		cout<<res[i]<<endl;
	return 0;
}

