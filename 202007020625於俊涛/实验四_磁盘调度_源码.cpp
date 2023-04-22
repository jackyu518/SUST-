#include<iostream>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include <iomanip> //精度控制函数位于该库中
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
//0外越小，1内越大 
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
	cout<<"请输入磁臂初始移动方向（1:磁道号递增的方向，0:磁道号递减的方向）：";
	cin>>direction;
	cout<<"请输入初始磁道和待执行磁道序列数量：";
	cin>>start>>n;
	srand((unsigned)time(NULL));
	for(int i=0; i<n; i++){
		m=rand() % 200 + 1;
		cyclist[i]=m;
	}
	cout<<"磁头走过总道数为："<<SCAN(cyclist, cycorder, n, start, direction)<<endl;
	cout<<"SCAN走道顺序为："<<endl;
	for(int i=0; i<n; i++){
		cout<<cycorder[i];
		if(i+1 != n)
			cout<<"->"; 
	}
	cout<<endl;
	ave_num=1.0*SCAN(cyclist, cycorder, n, start, direction)/n;
	cout<<fixed<<setprecision(2)<<"平均寻道长度为："<<ave_num<<endl;
	return 0;
}

