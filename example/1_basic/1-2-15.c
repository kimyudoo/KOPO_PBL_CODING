#include <stdio.h>
int main()
{    
    int inputData = 0;
    int resultData;
    FILE *fp;
    fp = fopen("input.txt", "r");
    resultData = fscanf(fp, "%d", &inputData);
    printf("결과 : %d\n", resultData);
    printf("입력값 : %d\n", inputData);
    fclose(fp);
    return 0;
}
