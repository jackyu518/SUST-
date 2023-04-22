#include<stdio.h>
#define resource_Num 100
#define process_Num  100

int resourceNum;
int processNum;
int available[resource_Num];//ϵͳ���ã�ʣ�ࣩ��Դ
int maxRequest[process_Num][resource_Num];//���̵��������
int allocation[process_Num][resource_Num];//�����Ѿ�ռ�У����䣩��Դ
int need[process_Num][resource_Num];//���̻���Ҫ��Դ
bool Finish[process_Num];//�Ƿ�ȫ
int safeSeries[process_Num];//��ȫ���к�
int request[resource_Num];//����������Դ��
int num;//��Դ��������

//��ӡ���ϵͳ��Ϣ
void showInfo()
{
	printf("\n------------------------------------------------------------------------------------\n");  
	printf("��ǰϵͳ������Դʣ�ࣺ");
    for(int j = 0; j < resourceNum; j++)
	{
        printf("%d ",available[j]);
    }
    printf("\n\n��ǰϵͳ��Դ�����\n");
    printf(" PID\t Max\t\tAllocation\t Need\n");
    for(int i = 0; i < processNum; i++)
	{
        printf(" P%d\t",i);
        for(int j = 0; j < resourceNum; j++)
		{
            printf("%2d",maxRequest[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < resourceNum; j++)
		{
            printf("%2d",allocation[i][j]);
        }
        printf("\t\t");
        for(int j = 0; j < resourceNum; j++)
		{
            printf("%2d",need[i][j]);
        }
        printf("\n");
    }
}

//��ӡ��ȫ�����Ϣ
void SafeInfo(int *work, int i)
{
    int j;
    printf(" P%d\t",i);
    for(j = 0; j < resourceNum; j++)
	{
        printf("%2d",work[j]);
    }   
    printf("\t\t");
    for(j = 0; j < resourceNum; j++)
	{
        printf("%2d",allocation[i][j]);
    }
	printf("\t\t");
    for(j = 0; j < resourceNum; j++)
	{
        printf("%2d",need[i][j]);
    }
    printf("\t\t");
    for(j = 0; j < resourceNum; j++)
	{
        printf("%2d",allocation[i][j]+work[j]);
    }
    printf("\n");
}

//�ж�һ�����̵���Դ�Ƿ�ȫΪ��
bool isAllZero(int kang)
{
	num = 0;
	for(int i = 0; i < resourceNum; i++ )
	{
		if(need[kang][i] == 0)
		{
			num ++;
		}
	}
	if(num == resourceNum)
	{
		return true;
	}
	else
	{
		return false;
	}   
}

//��ȫ���
bool isSafe()
{
	//int resourceNumFinish = 0;
	int safeIndex = 0;
	int allFinish = 0;
    int work[resource_Num] = {0};
	int r = 0;
	int temp = 0;
	int pNum = 0;
	//Ԥ����Ϊ�˱���available[]
    for(int i = 0; i < resourceNum; i++)
	{		
        work[i] = available[i];	
    }
	//��δ��ɽ�����Ϊfalse
    for(int i = 0; i < processNum; i++)
	{
		bool result = isAllZero(i);
		if(result == true)
		{
			Finish[i] = true;
			allFinish++;
		}
		else
		{
			Finish[i] = false;
		}

    }
	//Ԥ���俪ʼ
    while(allFinish != processNum)
	{
		num = 0;	
        for(int i = 0; i < resourceNum; i++)
		{
			if(need[r][i] <= work[i] && Finish[r] == false)
			{
				num ++;
			}			
		}
		if(num == resourceNum)
		{		
			for(int i = 0; i < resourceNum; i++ )
			{
				work[i] = work[i] + allocation[r][i];
			}
			allFinish ++;
			SafeInfo(work,r);
			safeSeries[safeIndex] = r;
			safeIndex ++;
			Finish[r] = true;
		}
		r ++;//��ʽ�����ڴ˴�	
		if(r >= processNum)
		{
			r = r % processNum;
			if(temp == allFinish)
			{
				break;	
			}
			temp = allFinish;
		}		
		pNum = allFinish;
    }	
	//�ж�ϵͳ�Ƿ�ȫ
	for(int i = 0; i < processNum; i++)
	{
		if(Finish[i] == false)
		{
			printf("\n��ǰϵͳ����ȫ��\n\n");
			return false;	
		}
	}
	//��ӡ��ȫ����
	printf("\n��ǰϵͳ��ȫ��\n\n��ȫ����Ϊ��");
	for(int i = 0; i < processNum; i++)
	{	
		bool result = isAllZero(i);
		if(result == true)
		{		
			pNum --;
		}	
    }
	for(int i = 0; i < pNum; i++)
	{
		printf("%d ",safeSeries[i]);
	}
    return true;
}

//������
int main()
{
	int i,j;
	printf("���������������Դ��:\n");
	scanf("%d %d",&processNum,&resourceNum);
	printf("��������̿���(ʣ��)��Դ��:\n");
	for(i=0;i<resourceNum;i++){
		scanf("%d",&available[resource_Num]);
	}
	printf("��������̰�ȫ���к�:\n");
	for(i=0;i<processNum;i++){
		scanf("%d",&safeSeries[process_Num]);
	}
	printf("������������������(��[%d,%d]�ĸ�ʽ):\n",processNum,resourceNum);
	for(i=0;i<processNum;i++)
	for(j=0;j<resourceNum;j++){
		scanf("%d",&maxRequest[process_Num][resource_Num]);
	}
	printf("�����������ռ����Դ��(��[%d,%d]�ĸ�ʽ):\n",processNum,resourceNum);
	for(i=0;i<processNum;i++)
	for(j=0;j<resourceNum;j++){
		scanf("%d",&allocation[process_Num][resource_Num]);
	}
	printf("��������̻�����Դ��(��[%d,%d]�ĸ�ʽ):\n",processNum,resourceNum);
	for(i=0;i<processNum;i++)
	for(j=0;j<resourceNum;j++){
		scanf("%d",&need[process_Num][resource_Num]);
	}
    int curProcess = 0;
	int a = -1;
       showInfo(); 
	printf("\nϵͳ��ȫ�������\n");
	printf(" PID\t Work\t\tAllocation\t Need\t\tWork+Allocation\n");
	bool isStart = isSafe();
	//�û��������Ԥ��ϵͳ��Դ���������ܼ������н��̷��乤��
    while(isStart)
	{
		//�����û����룬�Է��û�������ڽ������������֣��Լ����������ַ��������ǲ�����ģ�
      	do
		{ 
			if(curProcess >= processNum || a == 0)
			{
				printf("\n�벻Ҫ���볬������������ֵ���������ַ���\n");
				while(getchar() != '\n'){};//��ջ�����	
				a = -1;
			}
			printf("\n------------------------------------------------------------------------------------\n");
			printf("\n����Ҫ����Ľ��̣�");
			a = scanf("%d",&curProcess);
			printf("\n");

		}while(curProcess >= processNum || a == 0);
		
		//�����û����룬�˴�ֻ�������֣��Է��û����������ַ��������ǲ�����ģ�
		for(int i = 0; i < resourceNum; i++)
		{
			do
			{
				if(a == 0)
				{
					printf("\n�벻Ҫ�������������������ַ������������룺\n");
					while(getchar() != '\n'){};//��ջ�����	
					a = -1;
				}
				printf("������Ҫ��������� P%d �ĵ� %d ����Դ��",curProcess,i+1);
				a = scanf("%d", &request[i]);
			}while( a == 0);
		}

		//�ж��û�����ķ����Ƿ�������������ʼ����Ԥ����
		num  = 0;
        for(i = 0; i < resourceNum; i++)
		{
            if(request[i] <= need[curProcess][i] && request[i] <= available[i])
			{
				num ++;
			}
            else
			{
				printf("\n�������󣡿���ԭ�����£�\n(1)������������Դ���ܴ��ڸý��̵�ĳЩ��Դ�������Ҫ��\n(2)ϵͳ��ʣ����Դ�Ѿ������ˣ�\n");
				break;
			}
        }
        if(num == resourceNum)
		{	
			num = 0;	
            for(int j = 0; j < resourceNum; j++)
			{
				//������Դ
                available[j] = available[j] - request[j];
                allocation[curProcess][j] = allocation[curProcess][j] + request[j];
                need[curProcess][j] = need[curProcess][j] - request[j];
				//��¼�����Ժ��Ƿ�ý�����ҪֵΪ0��
				if(need[curProcess][j] == 0)
				{
					num ++;
				}
            }
			//��������Ժ���ָý��̶�������Դ������Ϊ0�ˣ������ͷŸý���ռ����Դ����Ϊ��ɣ�
			if(num == resourceNum)
			{
				//�ͷ��������Դ
				for(int i = 0; i < resourceNum; i++ )
				{
					available[i] = available[i] + allocation[curProcess][i];
				}
				printf("\n\n���η������ P%d ���,�ý���ռ����Դȫ���ͷ���ϣ�\n",curProcess);
			}
			else
			{
				//��Դ������Բ���һ���������������
				printf("\n\n���η������ P%d δ��ɣ�\n",curProcess);
			}

			showInfo();
           	printf("\nϵͳ��ȫ�������\n");
			printf(" PID\t Work\t\tAllocation\t Need\t\tWork+Allocation\n");

			//Ԥ��������Ժ��жϸ�ϵͳ�Ƿ�ȫ������ȫ����ɼ������з��䣬������ȫ�����Ѿ��������Դ������
            if(!isSafe())
			{ 	        
				for(int j = 0; j < resourceNum; j++)
				{
					available[j] = available[j] + request[j];
					allocation[curProcess][j] = allocation[curProcess][j] - request[j];
					need[curProcess][j] = need[curProcess][j] +request[j];
				}
				printf("��Դ���㣬�ȴ���...\n\n����ʧ�ܣ�\n");				
            }
        }
    }
}

