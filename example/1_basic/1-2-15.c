#include <stdio.h>
int main()
{    
    int inputData = 0;
    int resultData;
    FILE *fp;
    fp = fopen("input.txt", "r");
    resultData = fscanf(fp, "%d", &inputData);
    printf("��� : %d\n", resultData);
    printf("�Է°� : %d\n", inputData);
    fclose(fp);
    return 0;
}
