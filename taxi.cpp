#include <stdio.h>
#define _countof(array) (sizeof(array) / sizeof(array[0]))

char departure[50], arrival[50];

void place(void) {
    printf("출발지와 도착지를 입력하세요: ");

    // scanf_s를 사용해 안전하게 입력
    if (scanf_s("%49s %49s", departure, (unsigned)_countof(departure), arrival, (unsigned)_countof(arrival)) != 2) {
        printf("입력이 잘못되었습니다. 다시 시도하세요.\n");
        return;
    }

    printf("출발지: %s, 도착지: %s\n", departure, arrival);
}

int grade;

void taxi_grade(void) {
    printf("택시 등급을 선택하시오(번호 입력)\n1.중형택시\n2.대형승용 및 모범택시\n3.고급택시\n4.대형승합택시\n");
    scanf_s("%d", &grade);  // & 연산자 추가
    switch (grade) {
    case 1:
        printf("중형택시\n");
        break;
    case 2:
        printf("대형승용 및 모범택시\n");
        break;
    case 3:
        printf("고급택시\n");
        break;
    case 4:
        printf("대형승합택시\n");
        break;
    default:
        printf("잘못 입력하셨습니다.\n");
        taxi_grade();  // 재귀 호출 시 괄호 추가
        break;
    }
}

int main() {
    place();
    taxi_grade();  // 함수 호출 시 괄호 추가
    return 0;
}
