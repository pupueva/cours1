//курсовая
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
        printf("\n1. Инициализировать массив\n");
        printf("2. Вывести массив на экран\n");
        printf("3. Сортировать массив\n");
        printf("4. Завершить программу\n");
        printf("5. Количество отрицательных элементов в строках с нулями\n");
        printf("6. Найти седловые точки\n");
        printf("Выберите действие: ");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            printf("Введите количество строк: ");
            scanf_s("%d", &rows);
            printf("Введите количество столбцов: ");
            scanf_s("%d", &cols);

            printf("Инициализировать случайными числами? (1 - да, 0 - нет): ");
            scanf_s("%d", &is_random);

            // Инициализируем массив
            init_array(&array, rows, cols, is_random);
            break;

        case 2:
            if (array == NULL) {
                printf("Массив не инициализирован! Сначала создайте массив.\n");
            }
            else {
                print_array(array, rows, cols);
            }
            break;

        case 3:
            if (array == NULL) {
                printf("Массив не инициализирован! Сначала создайте массив.\n");
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
                printf("Массив не инициализирован! Сначала создайте массив.\n");
            }
            else {
                printf("Количество отрицательных элементов в строках с нулями: %d\n", count_negative_in_zero_rows(array, rows, cols));
            }
            break;

        case 6:
            if (array == NULL) {
                printf("Массив не инициализирован! Сначала создайте массив.\n");
            }
            else {
                find_saddle_points(array, rows, cols);
            }
            break;

        default:
            printf("Некорректный выбор, попробуйте снова.\n");
        }
    }
}

void init_array(int*** arr, int rows, int cols, int is_random) {
    // Выделяем память под двумерный массив
    *arr = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        (*arr)[i] = (int*)malloc(cols * sizeof(int));
    }

    // Инициализация массива
    if (is_random) {
        srand(time(NULL));  // Инициализация генератора случайных чисел
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                (*arr)[i][j] = rand() % 21 - 10;  // Случайные числа от -10 до 10
            }
        }
    }
    else {
        printf("Введите элементы массива:\n");
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                printf("Элемент [%d][%d]: ", i, j);
                scanf_s("%d", &(*arr)[i][j]);
            }
        }
    }
}

void print_array(int** arr, int rows, int cols) {
    printf("Массив:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

void sort_array(int** arr, int rows, int cols) {
    // Сортировка массива
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
    printf("Массив отсортирован.\n");
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
    printf("Седловые точки:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Поиск минимального элемента в строке
            int is_min_in_row = 1;
            for (int k = 0; k < cols; k++) {
                if (arr[i][k] < arr[i][j]) {
                    is_min_in_row = 0;
                    break;
                }
            }

            // Поиск минимального элемента в столбце
            int is_min_in_col = 1;
            for (int k = 0; k < rows; k++) {
                if (arr[k][j] < arr[i][j]) {
                    is_min_in_col = 0;
                    break;
                }
            }

            if (is_min_in_row && is_min_in_col) {
                printf("Седловая точка: A[%d][%d] = %d\n", i, j, arr[i][j]);
            }
        }
    }
}

int main() {
    setlocale(LC_CTYPE, "RUS");
    menu();
    return 0;
}
