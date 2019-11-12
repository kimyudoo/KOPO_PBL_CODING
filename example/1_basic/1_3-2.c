#include <stdio.h>

int main()
{
    int age;
    int fee; 
    
   printf("나이 입력 : ");
   scanf("%d",&age);
   
    if( age >= 65 )	{
        fee = 0;
	}
	
	printf("나이 : %d\n", age);
	printf("요금 : %d\n", fee);
}

