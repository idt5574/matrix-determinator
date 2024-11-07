#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>

double count_determinant(double**, int, int);
double** to_uptriang_matrix(double**, int, int);
double** copy_to_temp(double**, int, int);
//double** switch_strings(double**, int, int, int, int);
int find_coll(double**, int, int, double*);
int find_line(double**, int, int, double*);
double** remove_zeros(double** , int, int);
//double** sort_matrix(double**, int, int);
double* create_iden_ar(int, double);


int main(void)
{
    int n, k; // Размерность массива
    scanf("%d %d", &n, &k); // Ввод n и k
 
    double** ar = malloc(sizeof(double*) * n); // Инициализация двумерного динамического массива
    for(int i = 0; i < n; i++)
        ar[i] = malloc(sizeof(double) * k); 

    for(int i = 0; i < n; i++)
        for(int j = 0; j < k; j++)
            scanf("%lf", &ar[i][j]);

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < k; j++)
            printf("%.1f ", ar[i][j]);
        printf("\n");
    }
    
    double* ar = create_iden_ar(3, 0.0);
    // int x = count_determinant(ar, n, k);
    // printf("%d", x);
    return 0;
}

double** to_uptriang_matrix(double** ar, int h, int w)
{
    printf("D: func started\n");
    if(h != w) return 0; // Определяем, возможно ли посчитать определитель
    double** temp = copy_to_temp(ar, h, w);
    
    for(int i = 0; i < w; i++) // Первый цикл для перебора столбцов
    {
        printf("DEEP 1: IN\n");
        for(int j = i; j < h - 1; j++) // Второй цикл для перебора строк
        {
            printf("DEEP 2: (%d)IN\n", j);
            double r; // Коэффицент, на который мы будем домножать вычитаемое значение
            double x; // Вычитаемое значение (верхняя строчка типа)
            double y; // Ззначение которое нужно обнулить
            printf("inic 2\n");

            if(temp[j + 1][i] != 0.0) // Если ззначение которое нужно обнулить уже обнулено то мы НИчегго не делаем  азу перехмдио к след шагу!
            { 
                printf("DEEP 2 IF\n");
                x = temp[i][i];  
                y = temp[j + 1][i];
                r = y / x;
            }
            else 
            {
                printf("DEEP 2 BREAKOUT\n");
                break;
            }

            for(int k = 0; k < w; k++) // Вычитаем из каждого элемента строки верхнее значение домноженное на r
            {
                printf("DEEP 3: IN\n");
                temp[j + 1][k] = temp[j + 1][k] - (temp[i][k] * r);
                printf("\n");
                for(int i = 0; i < h; i++) // Выводим каждое изменение массива
                {
                    for(int j = 0; j < w; j++)
                        printf("%.1f ", temp[i][j]);
                    printf("\n");
                }
                printf("\n");
                printf("DEEP 3: OUT\n");
            }
            printf("DEEP 2: OUT\n");
        }
        printf("DEEP 1: OUT\n");
    }
    return temp;
}

double count_determinant(double** ar, int h, int w)
{
    if(h != w || find_line(ar, h, w, create_ar(3, 0.0)) != -1 || find_coll(ar, h, w, create_ar(3, 0.0, 0.0, 0.0)) != -1) return 0;
    
    double** temp = to_uptriang_matrix(ar, h, w);
    double res = 1;

    printf("\n");

    for(int i = 0; i < h; i++)
    {
        res *= temp[i][i];
        printf("%.1f %.1f\n", res, temp[i][i]);
    }

    printf("\n");

    free(temp);
    return res;
}

// double** switch_strings(double** ar, int h, int w, int a, int b) // Меняет местами строки с номерами a и b
// {
//     double** temp = copy_to_temp(ar, h, w);   
//     for(int i = 0; i < w; i++)
//     {
//         double temp_num = temp[a][i];
//         temp[a][i] = temp[b][i];
//         temp[b][i] = temp_num;
//     }
//     return temp;
// }

double** copy_to_temp(double** ar, int h, int w)
{
    double** temp = malloc(sizeof(double*) * h); // Инициализируем временный массив
    for(int i = 0; i < h; i++)
        temp[i] = malloc(sizeof(double) * w);
    
    for(int i = 0; i < h; i++) // Копируем во временный массив значения из изначального
        for(int j = 0; j < w; j++)
            temp[i][j] = ar[i][j];

    return temp;
}

int find_line(double** matrix, int h, int w, double* ar) // Поиск идентичной строки. Если существует, то возвращает номер строки, иначе -1
{
    for(int i = 0; i < h; i++)
    {
        int flag = 1;
        for(int j = 0; j < w; j++)
        {
            if(matrix[i][j] != ar[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag) return i;
    }

    free(ar);
    return -1;
}

int find_coll(double** matrix, int h, int w, double* ar) // Поиск идентичного столбца. Если существует, то возввращает номер столбца, иначе -1
{
    for(int i = 0; i < w; i++)
    {
        int flag = 1;
        for(int j = 0; j < h; j++)
        {
            if(matrix[j][i] != ar[j])
            {
                flag = 0;
                break;
            }
        }
        if(flag) return i;
    }

    free(ar);
    return -1;
}

double* create_iden_ar(int n, double a)
{

    double* ar = malloc(sizeof(double) * n);

    for(int i = 0; i < n; i++)
    {
        ar[i] = a;
    }

    return ar;
}

double** remove_zeros(double** ar, int w, int h)
{
    double** temp = copy_to_temp(ar, w, h);

    for(int i = 0; i < h; i++)
        for(int j = 0; j < w; j++)
        {
            if(temp[i][j] == 0.0)
            {
                printf("\neshkere\n");
                for(int k = 0; k < h; k++)
                {
                    if(temp[k][j] != 0.0)
                    {
                        printf("\nshkere2\n");
                        for(int p = 0; p < w; p++)
                        {
                            temp[i][p] += temp[k][p];
                        }
                    }
                }
                break;
            }
        }

    return temp;
}
