#include<bits/stdc++.h>
#include<random>
using namespace std;

//维度
#define dimension 10
//精度
#define precision 1e-6
//总注水量
#define totalwater 1.0

double alpha[dimension] = {0.39,0.09,0.53,0.73,0.73,0.1,0.85,0.6,0.15,0.1};
double x[dimension] = {};
//本实验中，nu始终为1/nu形式，故为方便表示，nu[]数组中实际存储1/nu
double nu[dimension] = {};

//生成一组随机的alpha参数，且ai范围为(0,1)
void random_alpha() {
	random_device num;
	uniform_real_distribution<double> Random(0, 1); //随机数分布对象 
	for (int i = 0; i < dimension; i++)  //生成范围为0-1的随机浮点数序列 
		alpha[i] = Random(num);
}

//根据alpha进行注水,根据x^*解的形式，使最终的和在精度要求下接近1
//接近的算法类似二分查找，具体伪代码在报告Ⅳ.B节中
void waterfilling() {
	double Init = 0.5;
	double Min = 0.0;
	double Max = totalwater + double(totalwater) / dimension;
	double result = 0;

	while (abs(result-totalwater)>precision){ //判断注水后结果是否满足精度要求
		fill(nu, nu + dimension, Init);
		for (int i = 0; i < dimension; i++) {
			x[i] = max(nu[i] - alpha[i], 0.0);

		}
		result = 0;
		for (auto& i : x)
			result += i;

		if (result > totalwater) {//更新上界
			Max = Init;
			Init = (Init + Min) / 2;
		}
		else if (result < totalwater) {//更新下界
			Min = Init;
			Init = (Init + Max) / 2;
		}
			
	}
	

}

int main() {
	clock_t begin = clock();

	random_alpha();
	waterfilling();

	//输出本次的alpha参数
	for (int i = 0; i < dimension; i++) {
		cout << "alpha[" << i << ']' << " = " << alpha[i] << endl;
	}
	cout << endl;
	//输出x^*的优化结果
	cout << "The optimal x* is : " << endl;
	for (int i = 0; i < dimension; i++) {
		cout << "x[" << i << ']' << " = " << x[i] << endl;
	}
	cout << endl;
	//输出计算的最优值
	double result = 0;
	for (int i = 0; i < dimension; i++) {
		result -= log(alpha[i] + x[i]);
	}
	cout << "The optimal result is : " <<result<< endl;

	cout << "The runtime is: "<<(clock() - begin)<<"ms"<<endl;
	return 0;

}