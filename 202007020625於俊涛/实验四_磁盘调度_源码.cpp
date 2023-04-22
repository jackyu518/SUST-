#include<iostream>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include <iomanip> //���ȿ��ƺ���λ�ڸÿ���
using namespace std;

int Max(int *cyclist, int n, int num){
	for(int i=0; i<n; i++)
		if(cyclist[i] > num)
			return 0;
	return 1;
}
int Min(int *cyclist, int n, int num){
	for(int i=0; i<n; i++)
		if(cyclist[i] < num)
			return 0;
	return 1;
}
//0��ԽС��1��Խ�� 
int SCAN(int *cyclist, int *cycorder, int n, int start, int dir){
	int sum, min, mid, index, tag[100] = {0};
	sum = 0;
	for(int j=0; j<n; j++){
		min = 9999;
		for(int i=0; i<n; i++){
			if(dir == 1 && cyclist[i] > start && tag[i] == 0){
				mid = cyclist[i] - start;
				if(mid < min){
					min = mid;
					index = i;
				}
			}
			else if(dir == 0 && cyclist[i] < start && tag[i] == 0){
				mid = abs(cyclist[i] - start);
				if(mid <min){
					min = mid;
					index = i;
				}
			}
		}
		if(dir && Max(cyclist, n, cyclist[index]))
			dir = 0;
		else if(Min(cyclist, n, cyclist[index]))
			dir = 1;
		sum += min;
		tag[index] = 1;
		cycorder[j] = cyclist[index];
		start = cyclist[index];
	}
	return sum;
}
int main(){
	int cyclist[100], cycorder[100], n, start, direction,m;
	float ave_num;
	cout<<"������ű۳�ʼ�ƶ�����1:�ŵ��ŵ����ķ���0:�ŵ��ŵݼ��ķ��򣩣�";
	cin>>direction;
	cout<<"�������ʼ�ŵ��ʹ�ִ�дŵ�����������";
	cin>>start>>n;
	srand((unsigned)time(NULL));
	for(int i=0; i<n; i++){
		m=rand() % 200 + 1;
		cyclist[i]=m;
	}
	cout<<"��ͷ�߹��ܵ���Ϊ��"<<SCAN(cyclist, cycorder, n, start, direction)<<endl;
	cout<<"SCAN�ߵ�˳��Ϊ��"<<endl;
	for(int i=0; i<n; i++){
		cout<<cycorder[i];
		if(i+1 != n)
			cout<<"->"; 
	}
	cout<<endl;
	ave_num=1.0*SCAN(cyclist, cycorder, n, start, direction)/n;
	cout<<fixed<<setprecision(2)<<"ƽ��Ѱ������Ϊ��"<<ave_num<<endl;
	return 0;
}

