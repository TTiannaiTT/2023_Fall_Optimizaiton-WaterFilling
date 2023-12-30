#include<bits/stdc++.h>
#include<random>
using namespace std;

//ά��
#define dimension 10
//����
#define precision 1e-6
//��עˮ��
#define totalwater 1.0

double alpha[dimension] = {0.39,0.09,0.53,0.73,0.73,0.1,0.85,0.6,0.15,0.1};
double x[dimension] = {};
//��ʵ���У�nuʼ��Ϊ1/nu��ʽ����Ϊ�����ʾ��nu[]������ʵ�ʴ洢1/nu
double nu[dimension] = {};

//����һ�������alpha��������ai��ΧΪ(0,1)
void random_alpha() {
	random_device num;
	uniform_real_distribution<double> Random(0, 1); //������ֲ����� 
	for (int i = 0; i < dimension; i++)  //���ɷ�ΧΪ0-1��������������� 
		alpha[i] = Random(num);
}

//����alpha����עˮ,����x^*�����ʽ��ʹ���յĺ��ھ���Ҫ���½ӽ�1
//�ӽ����㷨���ƶ��ֲ��ң�����α�����ڱ����.B����
void waterfilling() {
	double Init = 0.5;
	double Min = 0.0;
	double Max = totalwater + double(totalwater) / dimension;
	double result = 0;

	while (abs(result-totalwater)>precision){ //�ж�עˮ�����Ƿ����㾫��Ҫ��
		fill(nu, nu + dimension, Init);
		for (int i = 0; i < dimension; i++) {
			x[i] = max(nu[i] - alpha[i], 0.0);

		}
		result = 0;
		for (auto& i : x)
			result += i;

		if (result > totalwater) {//�����Ͻ�
			Max = Init;
			Init = (Init + Min) / 2;
		}
		else if (result < totalwater) {//�����½�
			Min = Init;
			Init = (Init + Max) / 2;
		}
			
	}
	

}

int main() {
	clock_t begin = clock();

	random_alpha();
	waterfilling();

	//������ε�alpha����
	for (int i = 0; i < dimension; i++) {
		cout << "alpha[" << i << ']' << " = " << alpha[i] << endl;
	}
	cout << endl;
	//���x^*���Ż����
	cout << "The optimal x* is : " << endl;
	for (int i = 0; i < dimension; i++) {
		cout << "x[" << i << ']' << " = " << x[i] << endl;
	}
	cout << endl;
	//������������ֵ
	double result = 0;
	for (int i = 0; i < dimension; i++) {
		result -= log(alpha[i] + x[i]);
	}
	cout << "The optimal result is : " <<result<< endl;

	cout << "The runtime is: "<<(clock() - begin)<<"ms"<<endl;
	return 0;

}