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
    
    double x = count_determinant(ar, n, k);

    printf("%.1f", x);

    return 0;
}

double** to_uptriang_matrix(double** ar, int h, int w)
{
    double** temp = copy_to_temp(ar, h, w);
    
    for(int i = 0; i < w; i++) // Первый цикл для перебора столбцов
    {
        if(temp[i][i] == 0.0)
            temp = remove_zeros(temp, h, w);

        
        for(int j = i; j < h - 1; j++) // Второй цикл для перебора строк
        {
            double r; // Коэффицент, на который мы будем домножать вычитаемое значение
            double x; // Вычитаемое значение (верхняя строчка типа)
            double y; // Ззначение которое нужно обнулить

            if(temp[j + 1][i] != 0.0) // Если ззначение которое нужно обнулить уже обнулено то мы НИчегго не делаем  азу перехмдио к след шагу!
            { 
                x = temp[i][i];  
                y = temp[j + 1][i];
                r = y / x;
            }
            else 
            {
                break;
            }

            for(int k = 0; k < w; k++) // Вычитаем из каждого элемента строки верхнее значение домноженное на r
            {
                temp[j + 1][k] = temp[j + 1][k] - (temp[i][k] * r);
                printf("\n");
                for(int i = 0; i < h; i++) // Выводим каждое изменение массива
                {
                    for(int j = 0; j < w; j++)
                        printf("%.1f ", temp[i][j]);
                    printf("\n");
                }
            }
        }
    }
    return temp;
}

double count_determinant(double** ar, int h, int w)
{
    if(h != w || find_line(ar, h, w, create_iden_ar(w, 0.0)) != -1 || find_coll(ar, h, w, create_iden_ar(w, 0.0)) != -1) 
    {
        printf("NO!\n");
        return 0;
    }
    
    double** temp = to_uptriang_matrix(ar, h, w);

    for(int i = 0; i < h; i++) // Выводим каждое изменение массива
    {
        for(int j = 0; j < w; j++)
            printf("%.1f ", temp[i][j]);
        printf("\n");
    }

    double res = 1.0;

    printf("\n");

    for(int i = 0; i < h; i++)
        res = res * temp[i][i];

    printf("\n");

    if(find_line(temp, h, w, create_iden_ar(w, 0.0)) != -1 || find_coll(temp, h, w, create_iden_ar(w, 0.0)) != -1) 
    {
        printf("NO!\n");
        return 0;
    }
    

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
        ar[i] = a;

    return ar;
}

double** remove_zeros(double** ar, int w, int h)
{
    double** temp = copy_to_temp(ar, w, h);

    for(int i = 0; i < h; i++)
        for(int j = i; j < w; j++)
        {
            if(temp[i][j] == 0.0)
            {
                for(int k = i; k < h; k++)
                {
                    if(temp[k][j] != 0.0)
                    {
                        for(int p = 0; p < w; p++)
                            temp[i][p] += temp[k][p];
                        
                        break;
                    }
                }
                break;
            }
        }

    return temp;
}
