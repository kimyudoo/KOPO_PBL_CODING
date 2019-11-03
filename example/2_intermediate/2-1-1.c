#include <stdio.h>

//���� ȯ��
const float USD = 1194.50, JPY = 1101.48, EUR = 1316.64,
                CNY = 168.46, GBP = 1489.37; 
float getExchangeRate(int mode);
void printExchangeReesult(float exchangeRate, int menuNumber, 
						int exchangeResult, int changeResult);
						
int main()
{
    float won = 0.0;    //�Է¹��� ��ȭ
    float exchangeRate = 0.0; // ȯ���� ��ȭ�� ȯ��
    float calcExchangeRate = 0.0; // ����� ���� ȯ���� ������ ����
    float exchange = 0.0; // �Ҽ��� ó���� ���� ȯ���ݾ�
    int exchangeResult = 0; // �Ҽ��� ó���� ���� ���� ȯ�� �ݾ�
    int changeResult = 0; // �Ž�����
    int calcChange = 0; // �Ž��������� 1�� ������ �Ǻ��ϱ� ���� ����
    int menuNumber = 0; // ȯ���� ��ȭ
    
    // �Էº�
    printf("ȯ���� ���ϴ� �ݾ��� �Է��ϼ���(��ȭ) : ");
    scanf("%f", &won);
    printf("ȯ���� ��ȭ�� �����ϼ��� (1:USD, 2:JPY, 3:EUR, 4:CNY, 5:GBP) : ");
    scanf("%d", &menuNumber);	
    
    // ó����
    // ȯ�� ����
    exchangeRate = getExchangeRate(menuNumber);
        
    // ȯ�� ���
    calcExchangeRate = exchangeRate;
    if(menuNumber == 2)  // ��ȭ�� ���
    {
        calcExchangeRate /= 100;
    }
    exchange = won / calcExchangeRate;
    exchangeResult = exchange;
    changeResult = won - (exchangeResult * calcExchangeRate);
    
    // �Ž����� 1������ ó��
    calcChange = changeResult % 10;
    changeResult -= calcChange;
    
    // ��º� 
    printExchangeReesult(exchangeRate, menuNumber, exchangeResult, changeResult);    
    return 0;
}
float getExchangeRate(int mode)
{
	float exchangeRate = 0.0;
	switch(mode) 
    {
    case 1:
        exchangeRate = USD;
        break;
    case 2:
        exchangeRate = JPY;
        break;
    case 3:
        exchangeRate = EUR;
        break;
    case 4:
        exchangeRate = CNY;
        break;
    case 5:
        exchangeRate = GBP;
        break;
    }
    return exchangeRate;
}
void printExchangeReesult(float exchangeRate, int menuNumber, 
						int exchangeResult, int changeResult)
{
	printf("���� ȯ�� : %.2f\n", exchangeRate);
    printf("ȯ�� ���\n");
    switch(menuNumber) 
    {
    case 1:
        printf("�޷� : %d�޷�\n", exchangeResult);
        break;
    case 2:
        printf("�� : %d��\n", exchangeResult);
        break;
    case 3:
        printf("���� : %d����\n", exchangeResult);
        break;
    case 4:
        printf("���� : %d����\n", exchangeResult);
        break;
    case 5:
        printf("�Ŀ�� : %d�Ŀ��\n", exchangeResult);
        break;
    }
    printf("�Ž����� : %d��\n", changeResult);
}
