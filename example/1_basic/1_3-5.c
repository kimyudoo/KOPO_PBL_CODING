#include <stdio.h>

void main()
{
   int excel, powpoint, word;
    int sum;
    float avg;
    
    printf("엑셀, 파워포인트, 워드 : ");
    scanf("%d %d %d", &excel, &powpoint, &word);
    
    //합계 평균 계산
    sum = excel + powpoint + word;
    avg = (float)sum / 3;
    
    printf("합계 : %d\n", sum);
    printf("평균 : %.2f\n", avg);
    
    if((avg >= 60) && (excel > 40) && (powpoint > 40) && (word > 40)){
        printf("합격\n");
    }
    else{
        printf("불합격\n");
    }
}
