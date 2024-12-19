#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _countof(array) (sizeof(array) / sizeof(array[0]))

// ���� ����
int grade, status;
float distance;
char departure[50], arrival[50];

// ������ ���� �� �ε� ����� ���� ����ü ����
struct TaxiData {
    char start[50];
    char destination[50];
    double fare;
};

// �ܺ� �Լ� ����
extern void saveData(const TaxiData* data);
extern int loadData(TaxiData* data);
extern float Cost(int grade, int status, float distance);
extern const char* getTimeZone(int* status);

// �ý� ��� ���� �Լ�
void taxi_grade(void) {
    printf("�ý� ����� �����Ͻÿ�(��ȣ �Է�)\n1. �����ý�\n2. �����¿� �� ����ý�\n3. ����ý�\n4. ���������ý�\n");
    while (1) {
        scanf_s("%d", &grade);
        if (grade >= 1 && grade <= 4) {
            const char* grades[] = { "�����ý�", "�����¿� �� ����ý�", "����ý�", "���������ý�" };
            printf("%s�� �����ϼ̽��ϴ�.\n", grades[grade - 1]);
            break;
        }
        else {
            printf("�߸��� �Է��Դϴ�. �ٽ� �Է����ּ���.\n");
        }
    }
}

// �ð��� ���� Ȯ�� �Լ�
int timeline() {
    int timeStatus;
    const char* timeZone = getTimeZone(&timeStatus);
    printf("���� �ð���� '%s'�Դϴ�. (timeStatus: %d)\n", timeZone, timeStatus);
    return timeStatus;
}

// ������� ������ �Է� �Լ�
void place(void) {
    printf("������� �������� �Է��ϼ���: ");
    while (1) {
        if (scanf_s("%49s %49s", departure, (unsigned)_countof(departure), arrival, (unsigned)_countof(arrival)) == 2) {
            printf("�����: %s, ������: %s\n", departure, arrival);
            break;
        }
        else {
            printf("�Է��� �߸��Ǿ����ϴ�. �ٽ� �õ��ϼ���.\n");
            while (getchar() != '\n'); // �Է� ���� ����
        }
    }
}

// ���̹����� ��ũ ���� �Լ�
void openDistanceURL(const char* start, const char* destination) {
    char url[300];
    snprintf(url, sizeof(url),
        "https://map.naver.com/p/directions/-/-/-/car?c=15.00,0,0,0,dh",
        start, destination);
    printf("�������� ���� �Ÿ��� Ȯ���ϼ���: %s\n", url);
    char command[350];  // ����� ū ����
    snprintf(command, sizeof(command), "start %s", url);  // 'start' ��� ���
    system(command);  // system�� ���� ������ ����
}


// �ý� ��� ��� �� ��� �Լ�
float cost() {
   
    float cost = Cost(grade, status, (float)distance);

    return cost;
}

int main() {
    TaxiData data;

    // ���� ������ �ҷ����� ���� Ȯ��
    int choice;
    printf("������ ����� �����͸� �ҷ����ðڽ��ϱ�?\n1. ��\n2. �ƴϿ�\n");
    scanf_s("%d", &choice);

    if (choice == 1) {
        if (loadData(&data)) {
            printf("����� �����͸� �ҷ��Խ��ϴ�:\n");
            printf("�����: %s, ������: %s, ���: %.0f��\n", data.start, data.destination, data.fare);
        }
        else {
            printf("����� �����Ͱ� �����ϴ�. ���ο� �����͸� �Է��ϼ���.\n");
            taxi_grade();
            status = timeline();
            place();
            data.fare = cost();
        }
    }
    else if (choice == 2) {
        printf("���ο� �����͸� �Է��ϼ���.\n");
        taxi_grade();
        status = timeline();
        place();

        // �Ÿ� Ȯ�� �� �Է�
        openDistanceURL(departure, arrival);
        printf("���������� Ȯ���� �Ÿ��� km ������ �Է��ϼ���: ");
        scanf_s("%f", &distance);
        printf("����� '%s'�� ������ '%s'�� �Ÿ��� %.2f km�Դϴ�.\n", departure, arrival, distance);

        //��� ���
        data.fare = cost();
        float final_cost = Cost(grade, status, distance);
        printf("���� ����� %.0f���Դϴ�.\n", final_cost);
    }
    else {
        printf("�߸��� �Է��Դϴ�. ���α׷��� �����մϴ�.\n");
        while (getchar() != '\n'); // �Է� ���� ����
        return 0;
    }
    
    // ������ ����
    strcpy_s(data.start, sizeof(data.start), departure);
    strcpy_s(data.destination, sizeof(data.destination), arrival);
    saveData(&data);

    return 0;
}
