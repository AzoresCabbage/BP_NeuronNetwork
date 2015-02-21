#pragma once

#include "stdafx.h"

class Random{
    private:
        double PI;
    public:
        Random();

        //[Min,Max]内精度为1e-4的随机小数
        double AverageRandom(double Min,double Max);

        //概率密度函数
        double Normal(double x,double miu,double sigma);

        //产生正态分布随机数。
        //传入参数为分布的均值miu，标准差sigma，要产生序列所满足的区间[Min,Max]
        //根据分布函数f的图形，随机生成某个值d，然后在要求的区间随机得到某个函数值f(x)，如果d>f(x)则重复该过程。由此方法得到的x为符合f的序列。因为(x,f(x))满足f，则在不同x点，取得d<=f(x)的概率符合f,故x也满足f。
        double NormalRandom(double miu,double sigma,double Min,double Max);
};
Random& ran();