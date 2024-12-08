#include <stdio.h>
#define _countof(array) (sizeof(array) / sizeof(array[0]))

int grade, status, distance;
char departure[50], arrival[50];

void taxi_grade(void) {
    printf("택시 등급을 선택하시오(번호 입력)\n1.중형택시\n2.대형승용 및 모범택시\n3.고급택시\n4.대형승합택시\n");
    scanf_s("%d", &grade);  // & 연산자 추가
    switch (grade) {
    case 1:
        printf("중형택시를 선택하셨습니다.\n");
        break;
    case 2:
        printf("대형승용 및 모범택시를 선택하셨습니다.\n");
        break;
    case 3:
        printf("고급택시를 선택하셨습니다.\n");
        break;
    case 4:
        printf("대형승합택시를 선택하셨습니다.\n");
        break;
    default:
        printf("잘못 입력하셨습니다.\n");
        taxi_grade();  // 재귀 호출 시 괄호 추가
        break;
    }
}
// time에서 시간대 정보 불러오기
extern const char* getTimeZone(int* status);

int timeline() {
    int timeStatus;
    const char* timeZone = getTimeZone(&timeStatus);
    printf("현재 시간대는 '%s'입니다. (timeStatus: %d)\n", timeZone, timeStatus);
    return timeStatus;
}

void place(void) {
    printf("출발지와 도착지를 입력하세요: ");

    // scanf_s를 사용해 안전하게 입력
    if (scanf_s("%49s %49s", departure, (unsigned)_countof(departure), arrival, (unsigned)_countof(arrival)) != 2) {
        printf("입력이 잘못되었습니다. 다시 시도하세요.\n");
        return;
    }

    printf("출발지: %s, 도착지: %s\n", departure, arrival);
}

extern float Cost(int grade, int status, float distance);

int cost() {
    int taxi_cost;
    float cost = Cost(grade, status, distance);
    printf("최종 요금은 %.0f원입니다.\n", cost);
    return 0;
}

int main()
{
    taxi_grade(); // 함수 호출 시 괄호 추가
    timeline();
    place();
    cost();

    return 0;
}
