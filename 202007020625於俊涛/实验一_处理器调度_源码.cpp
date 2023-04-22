#include<stdio.h>
#include<stdlib.h> 
#include<time.h>
int num = 5;  /*�ٶ�������Ϊ5*/
struct PCB*head;  /*���������ͷָ��*/
struct PCB*tail;  /*���������βָ��*/
int global_time;  /*����ȫ��ʱ��*/
struct PCB*PCBinit(struct PCB *q);   /*��ʼ����������*/
struct PCB*init(struct PCB *p, int i);  /*��ʼ������*/

void sort(struct PCB *phead);  /*ð����������*/
void exchange(struct PCB *p, struct PCB *max); /*���������������̵�ָ��*/
void run(struct PCB *p);  /*ģ�����н���*/
void showinfor(struct PCB *head);  /*���������Ϣ*/
void check_runtime(struct PCB *p);/*�ж�����ʱ���Ƿ�Ϊ0*/

struct PCB  /*���̿��ƿ�ṹ��,������ʶ����������������ʱ�䡢״̬��ǰ��ָ��*/
{
       char name[10];  /*���̱�ʶ��*/
       int run_time;  /*��������ʱ��*/
       int prior_num;  /*����������*/
       char status;  /*����״̬��R-����,E-����*/
       struct PCB *pre;  /*ָ���һ���̵�ָ��*/
       struct PCB *next;  /*ָ���һ���̵�ָ��*/
};
//��ʼ������
struct PCB*init(struct PCB *p, int i){
       //��ʼ��������
       p->name[0] = 'P';
       p->name[1] = 'C';
       p->name[2] = 'B';
       p->name[3] = i+1+'0';
       //Ϊ����ָ������ʱ��
       printf("���� %s\n",p->name);
       printf("��ȷ���ý��̵�����ʱ�䣺");
       scanf("%d", &p->run_time);
       //Ϊ����ָ��������
       printf("��ȷ���ý��̵���������");
       scanf("%d",&p->prior_num);
       printf("\n");
              //��ʼ������״̬Ϊ����
       p->status = 'R';
       //��ʼ��ָ���һ���̵�ָ��Ϊ��
       p->next = NULL;
       //���ؽ���
       return p;
}
//��ʼ����������
struct PCB*PCBinit(struct PCB *q){
       int i;
       struct PCB *p = NULL;  /*pΪ�����ж���PCBָ��*/
       head = tail = NULL; /*��ʼ��ͷβָ��*/
       for(i = 0; i < num; i++){
              p = (struct PCB*)malloc(sizeof(struct PCB));  //����ռ䣬��pָ�����PCB
              init(p,i); //��ʼ������
              p->next = NULL;
              if(head == NULL){       //���ӽ���
                     tail = head = p;
                     p->pre = NULL;
              }else{
                     p->pre = tail;
                     tail->next = p;
                     tail = p;
              }
       }
       return p;
}
//ð����������
void sort(struct PCB *phead){
       struct PCB *a, *b;  //�������a,b
       int i;
       for(i=0;i<num;i++){  //��ѭ��ѭ������ȡ����ȫ�ֱ���num���൱��������
              a = head;  //��ʼ������aΪhead
              b = head->next;   //��ʼ������bΪhead->next
              while(b != NULL){  //b�ǿ�
                     if(a->prior_num <b->prior_num){  //�ȽϽ���a,b��������
                            exchange(a,b);  //����exchange��������a,b����ָ��
                            a = a->pre;  //ʵ��һ��ָ�뽻��Ҫ����a,b����λ��
                            b = b->next;  //��Ϊָ�뽻�����ݲ���
                     }
              a = a->next; //���һ����ѭ����
              b = b->next; //ָ��˳��
              }
       }
}
//���������������̵�ָ��
void exchange(struct PCB *p, struct PCB *max){
       if(p == max | max != p->next){  //�ж����������̲����ڣ��򷵻�
              return;
       }
       if(max == p->next){  //��������
          if(p->pre != NULL){  //����pָ��ǰһ���̵�ָ�벻Ϊ��
              p->pre->next = max;  //��p��ǰһ���̵ĺ�ָ��ָ��max
          }else{  //����p��ǰһ����ָ��Ϊ�ա���˵��pԭ��headָ��Ľ���
              head = max; //��ͷָ��ָ��max
          }
          if(max->next != NULL){  //max����һ����ָ�벻Ϊ��
              max->next->pre=p;  //��max����һ���̵�ǰָ��ָ��p
          }
       max->pre = p->pre;  //��max��ǰһָ��ָ��p��ǰһָ��
       p->next = max->next;  //��p�ĺ�һָ��ָ��max�ĺ�һָ��
       max->next = p;  //max�ĺ�һָ��ָ��p
       p->pre = max;  //p��ǰһָ��ָ��max
       }//ʵ��ð�������н��̽ṹ��ֻת��ָ�룬��ת������
}
//���������Ϣ
void showinfor(struct PCB *phead){
       struct PCB *p;
       for(p = phead; p != NULL; p =p->next){
              printf("���� %s\t ������ %d\t ����ʱ�� %d\t ״̬ %c\n",p->name,p->prior_num,p->run_time,p->status);
       }
}
//���к���
void run(struct PCB *p){
       //�����������״̬��ȫ��ʱ���1��������Ҫ��ʱ���1�����ȼ���1
    global_time++;  //ȫ��ʱ���1
    p->run_time--;  //����ʱ���1
    if(p->prior_num > 0)   // �����������0 
        p->prior_num--;   //��������1
       printf("�� %d ������:\n",global_time);
       printf("��ǰ����: %s\t ������ %d\t ����ʱ��:%d\n", p->name, p->prior_num, p->run_time);
       printf("\n");
}
//�ж�����ʱ���Ƿ�Ϊ0
void check_runtime(struct PCB *p){
       if(p->run_time <= 0){  //������ʱ��Ϊ0����������
                     p->status = 'E';  //�޸Ľ���״̬
                     printf("���� %s �ѽ���",p->name);
                     printf("\n");
                     printf("���̵�ǰ״̬Ϊ��\n");
                     showinfor(head);  //��ʾ������Ϣ
                     printf("\n");
                     printf("-----------------------------------------------------\n");
                     printf("�밴�س���������һ����");
                     printf("\n");
                     getchar();  //���ջس���
                     free(p); //�ͷ�p�ڴ�
                     head = p->next;  //��ͷָ��˳��
              }
}
int main(){
       struct PCB *p = NULL;  /*pΪ�����ж���PCBָ��*/
       //��ʼ����������
       PCBinit(p);
       //���������ݼ����н�����������
       sort(head);
       printf("���̵�ǰ״̬Ϊ��\n");
       showinfor(head);  //��ʾ������Ϣ
       printf("\n");
       //�������л���PCB��ִ��ѭ�����
       while(head != NULL){
              p = head;  //pָ���һ������
              run(p);   //���е���
              check_runtime(p); //�ж�����ʱ���Ƿ�Ϊ0
          }
}

