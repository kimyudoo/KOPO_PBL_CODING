#include <stdio.h>
#define MAX 10
void main()
{
   int num[MAX];
   int i;
   int temp;
   int search;
   
   for(i=0; i<MAX; i++){
       printf("[%d] 정수 입력: ", i);
       scanf("%d", &num[i]);
   }
 printf("\n----------------------------------------------------------------------------\n");
    for(i=0; i<MAX; i++){
       printf("[%d]\t", i);
   }
   printf("\n");
    for(i=0; i<MAX; i++){
       printf(" %d\t", num[i]);
   }
   //찾을 데이터 입력  
   printf("\n\n찾을 데이터 : ");
   scanf("%d", &search);
   
   //순차 검색 
    for(i=0; i<MAX; i++){
    	if(num[i] == search){
    		printf("탐색 성공 : [%d] : %d\n", i, num[i]);
    		break;
		} 
   }
}
