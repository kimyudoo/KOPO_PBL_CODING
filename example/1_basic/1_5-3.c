#include<stdio.h>
#include<stdlib.h>      // 난수 관련 함수가 들어있는 헤더파일
#include<time.h>       // 시간 관련 헤더파일
#include<windows.h>   //Sleep함수 사용하기 위해.
#define MAX 6       // 최대 값

int win_price(int num);  //당첨금액 구하는 함수 

void main(void)
{
    int lotto[MAX];  //생성번호
    int com_lotto[MAX]; //컴퓨터 로또 번호 
    int i, j;
    int temp;
    srand(time(NULL)); //rand함수 초기화
    int count=0; //입력 개수 받을 변수 
    int win_num=0; //당첨개수
	int price=0; //당첨금액 
    
    printf("=================로또 복권 생성기=================\n");
    printf("== 직접 번호를 선택하고 싶은 개수를 입력하세요 ==\n\n");
    printf("입력 개수 : ");
    scanf("%d",&count);
    for(j=0; j<count; j++){
    	printf("%d : ", j+1);
    	scanf("%d",&lotto[j]);
	}
	
	printf("\n---------------------------------------------------\n"); 
	printf("선택번호 : ");
	
    for(i=count; i<MAX; i++){
        lotto[i] = (rand() % 45)+1;
        for(j=0; j<i; j++){
        	if(lotto[i]==lotto[j]){
        		i--;
        		break;
			}
		}
    }
    //컴퓨터 당첨 번호 생성 
    for(i=0; i<MAX; i++){
        com_lotto[i] = (rand() % 45)+1;
        for(j=0; j<i; j++){
        	if(com_lotto[i]==com_lotto[j]){
        		i--;
        		break;
			}
		}
    }
    //오름차순 정렬 (선택정렬)
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
    
     //당첨개수 
    for(i=0; i<MAX; i++){
    	for(j=0; j<MAX; j++){
    		if(lotto[i]==com_lotto[j])
    		{
    			win_num++;
			}
		}
	}
	
	//당첨금 
    price = win_price(win_num);
    //출력
    
    for(i=0; i<MAX; i++){
        Sleep(300);
       printf("%d\t", lotto[i]);
    }
    printf("\n---------------------------------------------------\n"); 
    //컴퓨터당첨 번호 출력
    printf("당첨번호 : ");
	for(i=0; i<MAX; i++){
       printf("%d\t", com_lotto[i]);
    } 
    printf("\n---------------------------------------------------\n"); 
    printf("\n당첨 개수 : %d\n", win_num);
    printf("\n당첨 금액 : %d\n", price);
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

