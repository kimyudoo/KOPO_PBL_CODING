#include <stdio.h>
#define MAX 10
void main()
{
   int num[MAX];
   int i,j,temp;
   int low=0, high=MAX-1, mid, flag=0; 
   int search;
   
   for(i=0; i<MAX; i++){
       printf("[%d] 정수 입력: ", i);
       scanf("%d", &num[i]);
   }
   //선택정렬
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
   //찾을 데이터 입력  
   printf("\n\n찾을 데이터 : ");
   scanf("%d", &search);
   //이진 검색 
    while(flag==0 && low<=high){
    	mid = (low+high)/2;   //mid값 계산 (소수점이하는 자동으로 절삭)

    	
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
	//출력  
	if(flag == 1){
		printf("탐색 데이터 : [%d] %d\n", mid, num[mid]);
	}
	else{
		printf("No\n");
	}  		
}
