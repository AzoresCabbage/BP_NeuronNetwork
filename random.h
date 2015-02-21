#pragma once

#include "stdafx.h"

class Random{
    private:
        double PI;
    public:
        Random();

        //[Min,Max]�ھ���Ϊ1e-4�����С��
        double AverageRandom(double Min,double Max);

        //�����ܶȺ���
        double Normal(double x,double miu,double sigma);

        //������̬�ֲ��������
        //�������Ϊ�ֲ��ľ�ֵmiu����׼��sigma��Ҫ�������������������[Min,Max]
        //���ݷֲ�����f��ͼ�Σ��������ĳ��ֵd��Ȼ����Ҫ�����������õ�ĳ������ֵf(x)�����d>f(x)���ظ��ù��̡��ɴ˷����õ���xΪ����f�����С���Ϊ(x,f(x))����f�����ڲ�ͬx�㣬ȡ��d<=f(x)�ĸ��ʷ���f,��xҲ����f��
        double NormalRandom(double miu,double sigma,double Min,double Max);
};
Random& ran();