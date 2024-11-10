//��������
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#define _USE_MATH_DEFINES  
#define CRT_SECURE_NO_DEPRECATE

void init_array(int*** arr, int rows, int cols, int is_random);
void print_array(int** arr, int rows, int cols);
void sort_array(int** arr, int rows, int cols);
int count_negative_in_zero_rows(int** arr, int rows, int cols);
void find_saddle_points(int** arr, int rows, int cols);

void menu() {
    int choice;
    int** array = NULL;
    int rows, cols, is_random;

    while (1) {
        printf("\n1. ���������������� ������\n");
        printf("2. ������� ������ �� �����\n");
        printf("3. ����������� ������\n");
        printf("4. ��������� ���������\n");
        printf("5. ���������� ������������� ��������� � ������� � ������\n");
        printf("6. ����� �������� �����\n");
        printf("�������� ��������: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("������� ���������� �����: ");
            scanf_s("%d", &rows);
            printf("������� ���������� ��������: ");
            scanf_s("%d", &cols);

            printf("���������������� ���������� �������? (1 - ��, 0 - ���): ");
            scanf_s("%d", &is_random);

            // �������������� ������
            init_array(&array, rows, cols, is_random);
            break;

        case 2:
            if (array == NULL) {
                printf("������ �� ���������������! ������� �������� ������.\n");
            }
            else {
                print_array(array, rows, cols);
            }
            break;

        case 3:
            if (array == NULL) {
                printf("������ �� ���������������! ������� �������� ������.\n");
            }
            else {
                sort_array(array, rows, cols);
            }
            break;

        case 4:
            if (array != NULL) {
                for (int i = 0; i < rows; i++) {
                    free(array[i]);
                }
                free(array);
            }
            return;

        case 5:
            if (array == NULL) {
                printf("������ �� ���������������! ������� �������� ������.\n");
            }
            else {
                printf("���������� ������������� ��������� � ������� � ������: %d\n", count_negative_in_zero_rows(array, rows, cols));
            }
            break;

        case 6:
            if (array == NULL) {
                printf("������ �� ���������������! ������� �������� ������.\n");
            }
            else {
                find_saddle_points(array, rows, cols);
            }
            break;

        default:
            printf("������������ �����, ���������� �����.\n");
        }
    }
}

void init_array(int*** arr, int rows, int cols, int is_random) {
    // �������� ������ ��� ��������� ������
    *arr = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        (*arr)[i] = (int*)malloc(cols * sizeof(int));
    }

    // ������������� �������
    if (is_random) {
        srand(time(NULL));  // ������������� ���������� ��������� �����
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*arr)[i][j] = rand() % 21 - 10;  // ��������� ����� �� -10 �� 10
            }
        }
    }
    else {
        printf("������� �������� �������:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("������� [%d][%d]: ", i, j);
                scanf_s("%d", &(*arr)[i][j]);
            }
        }
    }
}

void print_array(int** arr, int rows, int cols) {
    printf("������:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void sort_array(int** arr, int rows, int cols) {
    // ���������� �������
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols - 1; j++) {
            for (int k = j + 1; k < cols; k++) {
                if (arr[i][j] > arr[i][k]) {
                    int temp = arr[i][j];
                    arr[i][j] = arr[i][k];
                    arr[i][k] = temp;
                }
            }
        }
    }
    printf("������ ������������.\n");
}

int count_negative_in_zero_rows(int** arr, int rows, int cols) {
    int count = 0;

    for (int i = 0; i < rows; i++) {
        int has_zero = 0;
        for (int j = 0; j < cols; j++) {
            if (arr[i][j] == 0) {
                has_zero = 1;
                break;
            }
        }

        if (has_zero) {
            for (int j = 0; j < cols; j++) {
                if (arr[i][j] < 0) {
                    count++;
                }
            }
        }
    }

    return count;
}

void find_saddle_points(int** arr, int rows, int cols) {
    printf("�������� �����:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // ����� ������������ �������� � ������
            int is_min_in_row = 1;
            for (int k = 0; k < cols; k++) {
                if (arr[i][k] < arr[i][j]) {
                    is_min_in_row = 0;
                    break;
                }
            }

            // ����� ������������ �������� � �������
            int is_min_in_col = 1;
            for (int k = 0; k < rows; k++) {
                if (arr[k][j] < arr[i][j]) {
                    is_min_in_col = 0;
                    break;
                }
            }

            if (is_min_in_row && is_min_in_col) {
                printf("�������� �����: A[%d][%d] = %d\n", i, j, arr[i][j]);
            }
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    menu();
    return 0;
}
