#include <stdio.h>
#define MAX 10
void main()
{
   int num[MAX];
   int i;
   int temp;
   int search;
   
   for(i=0; i<MAX; i++){
       printf("[%d] ���� �Է�: ", i);
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
   //ã�� ������ �Է�  
   printf("\n\nã�� ������ : ");
   scanf("%d", &search);
   
   //���� �˻� 
    for(i=0; i<MAX; i++){
    	if(num[i] == search){
    		printf("Ž�� ���� : [%d] : %d\n", i, num[i]);
    		break;
		} 
   }
}
