#include <cstdio>//cstdioͷ�ļ�,������C++��ʹ�ú�C����stdio.hһ�����﷨���磺scanf()  printf()
#include <cmath>//������һϵ�к��������㳣������ѧ����ͱ任
#define SPACE 512
#include <iostream>
using namespace std;
//�ṹ�嶨�� 
typedef struct node
{
    char name;
    float start;
    float end;//��С
    int flag;//�Ƿ����ı�־
}node;
node OS[SPACE];
int count;//���ֳɵĿ���ͳ��
int applyfree;
float numb;
char c;

//�ȶ�������г�ʼ����ʹû�з��������Ϊ N
void init()
{
    count=1;
    OS[0].name ='N';
    OS[0].start =0;
    OS[0].end =SPACE;
    OS[0].flag =1;
}

//������Ĳ������
void insert(int m,float st,float en)
{
    int i;
    count++;
    for(i=count;i>m+1;i--)
    {
        OS[i]=OS[i-1];
    }
    OS[m].start =st;
    OS[m].end  =en;
}

//�ƶ����������������ɾ������
void move(int m)
{
    int i;
    for(i=m;i<count-1;i++)
    {
        OS[i]=OS[i+1];
    }
    count--;
}

//������ڿ鶼û�з��䣬��Ҫ�ϲ���һ��
void remove(int m,float st,float en)
{
    if(!OS[m-1].flag &&!OS[m+1].flag )
    {
        OS[m].name ='P';
        OS[m].flag =1;
    }
    if(OS[m-1].flag )
    {
        OS[m-1].end =OS[m-1].end +en;
        move(m);
    }
    if(OS[m+1].flag )
    {
        OS[m].end =OS[m].end +OS[m+1].end ;
        OS[m].name ='P';
        OS[m].flag =1;
        move(m+1);
    }
}


//��ӡ���
void show()
{
    int i;
    printf("----------------------------------------\n");
    printf("����  |  ��ʶ  |  ��ַ  |  ����  |  ״̬\n");
    printf("----------------------------------------\n");
    for(i=0;i<count;i++)
    {
        if(OS[i].flag )
            printf("  N     ");
        else
            printf("  %c    ",OS[i].name );

        printf("  %d        %1.0f       %1.0f    ",i,OS[i].start ,OS[i].end );
        if(OS[i].flag )
            printf("δ����\n");
        else
            printf("�ѷ���\n");
    }
}

//�Ӽ�����������
void putin()
{
    printf("����������(����1)�����ͷ�(����0)����ҵ���Ƽ���ռ�ռ䣺\n");
    rewind(stdin);
    scanf("%c",&c);
    scanf("%d",&applyfree);
    scanf("%f",&numb);
}


int apply()
{
    int i=0;
    int applyflag=0;
    int freeflag=0;
    if(applyfree)//���������Դ
    {
        while(!applyflag&&i<count)
        {
            if(OS[i].end >=numb&&OS[i].flag )
            {
                if(OS[i].end ==numb)
                {
                    OS[i].name =c;
                    OS[i].flag =0;
                }
                else
                {

                    insert(i+1,OS[i].start +numb,OS[i].end -numb);
                    OS[i+1].flag =1;
                    OS[i+1].name ='P';
                    OS[i].start =OS[i].start ;
                    OS[i].name =c;
                    OS[i].end =numb;
                    OS[i].flag =0;
                }
                applyflag=1;
            }
            i++;
        }
        if(applyflag)
        {
            printf("����ɹ���\n");
            return 1;
        }
        else
        {
            printf("����ʧ�ܣ�û���㹻��Ŀ��пռ䡣\n");
            return 0;
        }
    }

    else//����ͷ���Դ
    {
        while(!freeflag&&i<count)
        {
            if(OS[i].name ==c)
            {
                if(OS[i].end ==numb)
                {
                remove(i,OS[i].start ,OS[i].end );
                }
                else
                {
                    if(OS[i].end >numb)
                    {

                            insert(i+1,OS[i].start +numb,OS[i].end -numb);
                            OS[i+1].name ='P';
                            OS[i+1].flag =0;
                            OS[i].end =numb;
                            OS[i].flag =1;
                            if(OS[i-1].flag )
                            {
                                remove(i,OS[i].start ,OS[i].end );
                            }
                    }
                    else
                    {
                        printf("�ͷ�ʧ�ܣ���Ϊ��ʹ�õ�����С��Ҫ���ͷŵ�������\n");
                        return 0;
                    }
                }
                freeflag=1;
            }
            i++;
        }
        if(freeflag)
        {
            printf("�ͷųɹ���\n");
            return 1;
        }
        else
        {
            printf("�ͷ�ʧ�ܣ�δ�ҵ�ƥ��Ľ������ơ�\n");
            return 0;
        }
    }
}
//������ 
int main()
{
    init();
    show();
    while(1)
    {
        putin();
        apply();
        show();
    }
    return 0;
}

