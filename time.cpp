#include <ctime>

const char* getTimeZone(int* status) {
    // ���� �ð��� ������
    time_t currentTime = time(nullptr);
    struct tm localTime;

    // ���� �ð��� ���� �ð����� ��ȯ
    localtime_s(&localTime, &currentTime);

    int hour = localTime.tm_hour; // ���� �ð� (0 ~ 23)

    // �ð��븦 �з�
    if ((hour >= 22 && hour < 23) || (hour >= 2 && hour < 4)) {
        if (status) *status = 0; // ���¸� �����ͷ� ��ȯ
        return "�ɾ� 1����";
    }
    else if (hour >= 23 || hour < 2) {
        if (status) *status = 1; // ���¸� �����ͷ� ��ȯ
        return "�ɾ� 2����";
    }
    else {
        if (status) *status = 0; // ���¸� �����ͷ� ��ȯ
        return "�ְ�";
    }
}
