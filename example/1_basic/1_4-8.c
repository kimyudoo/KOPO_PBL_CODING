#include <stdio.h>
#define MAX 10
void main()
{
   int num[MAX];
   int i,j,temp;
   int low=0, high=MAX-1, mid, flag=0; 
   int search;
   
   for(i=0; i<MAX; i++){
       printf("[%d] ���� �Է�: ", i);
       scanf("%d", &num[i]);
   }
   //��������
 	for(i=0; i<MAX; i++){
        for(j=i+1; j<MAX; j++){
            if(num[i]>num[j]){
                temp = num[i];
                num[i] = num[j];
                num[j] = temp;
            }
        }
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
    while(flag==0 && low<=high){
    	mid = (low+high)/2;   //mid�� ��� (�Ҽ������ϴ� �ڵ����� ����)

    	
    	if(search == num[mid]){
    		flag = 1;
		}
		else if(search > num[mid]){
			low = mid + 1;
		}
		else{
			high = mid - 1;
		}
	}
	//���  
	if(flag == 1){
		printf("Ž�� ������ : [%d] %d\n", mid, num[mid]);
	}
	else{
		printf("No\n");
	}  		
}
