#include <stdio.h>
#define _countof(array) (sizeof(array) / sizeof(array[0]))

int grade;
char departure[50], arrival[50];

void taxi_grade(void) {
    printf("�ý� ����� �����Ͻÿ�(��ȣ �Է�)\n1.�����ý�\n2.�����¿� �� ����ý�\n3.����ý�\n4.���������ý�\n");
    scanf_s("%d", &grade);  // & ������ �߰�
    switch (grade) {
    case 1:
        printf("�����ýø� �����ϼ̽��ϴ�.\n");
        break;
    case 2:
        printf("�����¿� �� ����ýø� �����ϼ̽��ϴ�.\n");
        break;
    case 3:
        printf("����ýø� �����ϼ̽��ϴ�.\n");
        break;
    case 4:
        printf("���������ýø� �����ϼ̽��ϴ�.\n");
        break;
    default:
        printf("�߸� �Է��ϼ̽��ϴ�.\n");
        taxi_grade();  // ��� ȣ�� �� ��ȣ �߰�
        break;
    }
}
// time���� �ð��� ���� �ҷ�����
extern const char* getTimeZone();

int timeline() {
    const char* timeZone = getTimeZone();
    printf("���� �ð���� '%s'�Դϴ�.\n", timeZone);
    return 0;
}

void place(void) {
        printf("������� �������� �Է��ϼ���: ");

        // scanf_s�� ����� �����ϰ� �Է�
        if (scanf_s("%49s %49s", departure, (unsigned)_countof(departure), arrival, (unsigned)_countof(arrival)) != 2) {
            printf("�Է��� �߸��Ǿ����ϴ�. �ٽ� �õ��ϼ���.\n");
            return;
        }

        printf("�����: %s, ������: %s\n", departure, arrival);
    }


int main()
{
    taxi_grade(); // �Լ� ȣ�� �� ��ȣ �߰�
    timeline();
    place();
    
    return 0;
}
