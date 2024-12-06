#include <ctime>

const char* getTimeZone() {
    // C ��Ÿ�Ϸ� ���� �ð��� ������
    time_t currentTime = time(nullptr); // ���� �ð� (time_t Ÿ��)
    struct tm localTime;

    // time_t�� ���� �ð�(struct tm)���� ��ȯ
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour; // ���� �ð� (0 ~ 23)

    // �ð��븦 �з�
    if ((hour >= 22 && hour < 23) || (hour >= 2 && hour < 4)) {
        return "�ɾ� 1����";
    }
    else if (hour >= 23 || hour < 2) {
        return "�ɾ� 2����";
    }
    else {
        return "�ְ�";
    }
}