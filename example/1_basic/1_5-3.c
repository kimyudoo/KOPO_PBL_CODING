#include<stdio.h>
#include<stdlib.h>      // ���� ���� �Լ��� ����ִ� �������
#include<time.h>       // �ð� ���� �������
#include<windows.h>   //Sleep�Լ� ����ϱ� ����.
#define MAX 6       // �ִ� ��

int win_price(int num);  //��÷�ݾ� ���ϴ� �Լ� 

void main(void)
{
    int lotto[MAX];  //������ȣ
    int com_lotto[MAX]; //��ǻ�� �ζ� ��ȣ 
    int i, j;
    int temp;
    srand(time(NULL)); //rand�Լ� �ʱ�ȭ
    int count=0; //�Է� ���� ���� ���� 
    int win_num=0; //��÷����
	int price=0; //��÷�ݾ� 
    
    printf("=================�ζ� ���� ������=================\n");
    printf("== ���� ��ȣ�� �����ϰ� ���� ������ �Է��ϼ��� ==\n\n");
    printf("�Է� ���� : ");
    scanf("%d",&count);
    for(j=0; j<count; j++){
    	printf("%d : ", j+1);
    	scanf("%d",&lotto[j]);
	}
	
	printf("\n---------------------------------------------------\n"); 
	printf("���ù�ȣ : ");
	
    for(i=count; i<MAX; i++){
        lotto[i] = (rand() % 45)+1;
        for(j=0; j<i; j++){
        	if(lotto[i]==lotto[j]){
        		i--;
        		break;
			}
		}
    }
    //��ǻ�� ��÷ ��ȣ ���� 
    for(i=0; i<MAX; i++){
        com_lotto[i] = (rand() % 45)+1;
        for(j=0; j<i; j++){
        	if(com_lotto[i]==com_lotto[j]){
        		i--;
        		break;
			}
		}
    }
    //�������� ���� (��������)
     for(i=0; i<MAX; i++){
         for(j=i+1; j<MAX; j++){
             if(lotto[i] > lotto[j]){
                 temp = lotto[i];
                 lotto[i] = lotto[j];
                 lotto[j] = temp;
             }
             if(com_lotto[i] > com_lotto[j]){
                 temp = com_lotto[i];
                 com_lotto[i] = com_lotto[j];
                 com_lotto[j] = temp;
             }
         }
    }
    
     //��÷���� 
    for(i=0; i<MAX; i++){
    	for(j=0; j<MAX; j++){
    		if(lotto[i]==com_lotto[j])
    		{
    			win_num++;
			}
		}
	}
	
	//��÷�� 
    price = win_price(win_num);
    //���
    
    for(i=0; i<MAX; i++){
        Sleep(300);
       printf("%d\t", lotto[i]);
    }
    printf("\n---------------------------------------------------\n"); 
    //��ǻ�ʹ�÷ ��ȣ ���
    printf("��÷��ȣ : ");
	for(i=0; i<MAX; i++){
       printf("%d\t", com_lotto[i]);
    } 
    printf("\n---------------------------------------------------\n"); 
    printf("\n��÷ ���� : %d\n", win_num);
    printf("\n��÷ �ݾ� : %d\n", price);
    printf("\n\n\n\n\n");
}


int win_price(int num){
	switch(num){
		case 6:
			return 1000000000;
			break;
		case 5:
			return 100000000;
			break;
		case 4:
			return 50000000;
			break;
		case 3:
			return 10000000;
			break;	
		case 2:
			return 10000;
			break;
		case 1:
			return 1000;
			break;
		default :
			return 0;
			break;
	} 
}

