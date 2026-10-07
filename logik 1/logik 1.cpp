#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Объявление структуры student
struct student
{
    char famil[20];
    char name[20];
    char facult[20];
    int Nomzach;
};

// Задание 1: Разница между max и min
void task1(void)
{
    int a[10] = { 15, 3, -4, 8, 42, 0, -12, 19, 7, 25 };
    int n = 10;
    int i, min = a[0], max = a[0];

    for (i = 1; i < n; i++)
    {
        if (a[i] > max) max = a[i];
        if (a[i] < min) min = a[i];
    }

    printf("\n--- Задание 1 ---\nМассив: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\nMax: %d, Min: %d, Разница: %d\n", max, min, max - min);
}

// Задание 2: Случайные числа
void task2(void)
{
    int a[10];
    int n = 10, i;
    int min = 10, max = 50;

    srand((unsigned int)time(NULL));
    printf("\n--- Задание 2 ---\nСлучайный массив:\n");
    for (i = 0; i < n; i++)
    {
        a[i] = min + rand() % (max - min + 1);
        printf("%d ", a[i]);
    }
    printf("\n");
}

// Задание 3: Динамический массив
void task3(void)
{
    int* a;
    int n, i;

    printf("\n--- Задание 3 ---\nВведите размер массива: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Ошибка ввода размера.\n");
        return;
    }

    a = (int*)malloc(n * sizeof(int));
    if (a == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return;
    }

    printf("Введите %d элементов:\n", n);
    for (i = 0; i < n; i++) scanf("%d", &a[i]);

    printf("Массив: ");
    for (i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    free(a);
}

// Задание 4: Динамический квадратный двумерный массив [-15; 20]
// и сумма элементов строго ниже главной диагонали
void task4(void)
{
    int n, i, j;
    int** matrix;
    int min_val = -15, max_val = 20;
    int sum_below_diag = 0;

    printf("\n--- Задание 4 ---\n");
    printf("Введите размерность квадратной матрицы (N x N): ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Ошибка: неверный размер матрицы.\n");
        return;
    }

    // 1. Выделение памяти под массив указателей на строки
    matrix = (int**)malloc(n * sizeof(int*));
    if (matrix == NULL)
    {
        printf("Ошибка выделения памяти.\n");
        return;
    }

    // 2. Выделение памяти под каждую строку
    for (i = 0; i < n; i++)
    {
        matrix[i] = (int*)malloc(n * sizeof(int));
        if (matrix[i] == NULL)
        {
            printf("Ошибка выделения памяти под строку %d.\n", i);
            // Освобождаем уже выделенные строки
            for (j = 0; j < i; j++) free(matrix[j]);
            free(matrix);
            return;
        }
    }

    // Инициализация генератора случайных чисел
    srand((unsigned int)time(NULL));

    // 3. Заполнение матрицы случайными числами [-15; 20] и вывод на экран
    printf("\nСгенерированная матрица %dx%d:\n", n, n);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            matrix[i][j] = min_val + rand() % (max_val - min_val + 1);
            printf("%5d", matrix[i][j]);
        }
        printf("\n");
    }

    // 4. Подсчет суммы элементов строго ниже главной диагонали (условие i > j)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            sum_below_diag += matrix[i][j];
        }
    }

    printf("\nСумма элементов строго ниже главной диагонали: %d\n", sum_below_diag);

    // 5. Освобождение памяти
    for (i = 0; i < n; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
}

// Задание 5: Динамический ввод N записей и поиск по неполному совпадению
void task5(void)
{
    int n, i;
    struct student* stud;
    char search_part[20];
    int found_count = 0;

    printf("\n--- Задание 5: Структуры ---\n");
    printf("Введите количество студентов: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Ошибка: неверное количество записей.\n");
        return;
    }

    // Выделение динамической памяти под массив структур
    stud = (struct student*)malloc(n * sizeof(struct student));
    if (stud == NULL)
    {
        printf("Ошибка выделения памяти под структуры.\n");
        return;
    }

    // Ввод данных по образцу из методички
    for (i = 0; i < n; i++)
    {
        printf("Введите фамилию студента %d:\n", i + 1);
        scanf("%19s", stud[i].famil);
    }
    for (i = 0; i < n; i++)
    {
        printf("Введите имя студента %s:\n", stud[i].famil);
        scanf("%19s", stud[i].name);
    }
    for (i = 0; i < n; i++)
    {
        printf("Введите название факультета студента %s %s:\n", stud[i].famil, stud[i].name);
        scanf("%19s", stud[i].facult);
    }
    for (i = 0; i < n; i++)
    {
        printf("Введите номер зачётной книжки студента %s %s:\n", stud[i].famil, stud[i].name);
        scanf("%d", &stud[i].Nomzach);
    }

    // Вывод всех введённых записей
    printf("\n--- Список введенных студентов ---\n");
    for (i = 0; i < n; i++)
    {
        printf("Cтудент %s %s обучается на факультете %s, номер зачётной книжки %d \n",
            stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
    }

    // Поиск по неполному совпадению фамилии (подстроке)
    printf("\n--- Поиск по фрагменту фамилии ---\n");
    printf("Введите часть фамилии (или фамилию целиком): ");
    scanf("%19s", search_part);

    printf("\nРезультаты поиска:\n");
    for (i = 0; i < n; i++)
    {
        // strstr возвращает указатель на вхождение подстроки, либо NULL если подстрока не найдена
        if (strstr(stud[i].famil, search_part) != NULL)
        {
            printf("Найден: %s %s, Факультет: %s, Зачетка: %d\n",
                stud[i].famil, stud[i].name, stud[i].facult, stud[i].Nomzach);
            found_count++;
        }
    }

    if (found_count == 0)
    {
        printf("Студентов, содержащих \"%s\" в фамилии, не найдено.\n", search_part);
    }
    else
    {
        printf("Всего найдено записей: %d\n", found_count);
    }

    // Освобождение выделенной памяти
    free(stud);
}

int main(void)
{
    // Включаем поддержку русского языка в консоли Windows
    system("chcp 1251 > nul");

    int choice;
    do
    {
        printf("\n============================\n");
        printf("Выберите задание (1-5) или 0 для выхода: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice)
        {
        case 1: task1(); break;
        case 2: task2(); break;
        case 3: task3(); break;
        case 4: task4(); break;
        case 5: task5(); break;
        case 0: printf("Выход.\n"); break;
        default: printf("Неверный номер задания!\n");
        }
    } while (choice != 0);

    return 0;
}