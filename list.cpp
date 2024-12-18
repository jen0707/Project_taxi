#include <stdio.h>
#include <string.h>

struct TaxiData {
    char start[50];       // �����
    char destination[50]; // ������
    double fare;          // ���
};

// �����͸� ���Ͽ� �����ϴ� �Լ�
void saveData(const TaxiData* data) {
    FILE* file = NULL;
    if (fopen_s(&file, "taxi_data.txt", "w") == 0) { // fopen_s requires a pointer to FILE*
        fprintf(file, "%s\n%s\n%.2f\n", data->start, data->destination, data->fare);
        fclose(file);
        printf("�����Ͱ� ����Ǿ����ϴ�.\n");
    }
    else {
        printf("������ �� �� �����ϴ�!\n");
    }
}

// ���Ͽ��� �����͸� �д� �Լ�
int loadData(TaxiData* data) {
    FILE* file = NULL;
    if (fopen_s(&file, "taxi_data.txt", "r") == 0) {
        if (fgets(data->start, sizeof(data->start), file) != NULL) {
            data->start[strcspn(data->start, "\n")] = '\0'; // ���� ���� ����
        }

        if (fgets(data->destination, sizeof(data->destination), file) != NULL) {
            data->destination[strcspn(data->destination, "\n")] = '\0'; // ���� ���� ����
        }

        if (fscanf_s(file, "%lf", &data->fare) == 1) {
            fclose(file);
            return 1; // ����
        }
        fclose(file);
    }
    else {
        printf("������ �� �� �����ϴ�!\n");
    }
    return 0; // ����
}
