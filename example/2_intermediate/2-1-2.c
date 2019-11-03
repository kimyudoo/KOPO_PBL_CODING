#include <stdio.h>

//기준 환율
const float USD = 1194.50, JPY = 1101.48, EUR = 1316.64,
                CNY = 168.46, GBP = 1489.37; 
float getExchangeRate(int mode);
void printExchangeReesult(float exchangeRate, int menuNumber, 
						int exchangeResult, int changeResult);
						
int main()
{
    float won = 0.0;    //입력받을 원화
    float exchangeRate = 0.0; // 환전할 외화의 환율
    float calcExchangeRate = 0.0; // 계산을 위해 환율을 저장할 변수
    float exchange = 0.0; // 소수점 처리를 위한 환전금액
    int exchangeResult = 0; // 소수점 처리를 끝낸 최종 환전 금액
    int changeResult = 0; // 거스름돈
    int calcChange = 0; // 거스름돈에서 1원 단위를 판별하기 위한 변수
    int menuNumber = 0; // 환전할 외화
    
    // 입력부
    printf("환전을 원하는 금액을 입력하세요(원화) : ");
    scanf("%f", &won);
	do {
	    printf("환전할 외화를 선택하세요 (1:USD, 2:JPY, 3:EUR, 4:CNY, 5:GBP) : ");
	    scanf("%d", &menuNumber);	
	}while(menuNumber < 1 || menuNumber > 5);
    
    // 처리부
    // 환율 지정
    exchangeRate = getExchangeRate(menuNumber);
        
    // 환율 계산
    calcExchangeRate = exchangeRate;
    if(menuNumber == 2)  // 엔화일 경우
    {
        calcExchangeRate /= 100;
    }
    exchange = won / calcExchangeRate;
    exchangeResult = exchange;
    changeResult = won - (exchangeResult * calcExchangeRate);
    
    // 거스름돈 1원단위 처리
    calcChange = changeResult % 10;
    changeResult -= calcChange;
    
    // 출력부 
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
	printf("기준 환율 : %.2f\n", exchangeRate);
    printf("환전 결과\n");
    switch(menuNumber) 
    {
    case 1:
        printf("달러 : %d달러\n", exchangeResult);
        break;
    case 2:
        printf("엔 : %d엔\n", exchangeResult);
        break;
    case 3:
        printf("유로 : %d유로\n", exchangeResult);
        break;
    case 4:
        printf("위안 : %d위안\n", exchangeResult);
        break;
    case 5:
        printf("파운드 : %d파운드\n", exchangeResult);
        break;
    }
    printf("거스름돈 : %d원\n", changeResult);
}
