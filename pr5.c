#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

double count_determinant(double**, int, int);
double** to_uptriang_matrix(double**, int, int);
double** copy_to_temp(double**, int, int);
double** switch_strings(double**, int, int, int, int);
int find_coll(double**, int, int, double, double, double);
int find_line(double**, int, int, double, double, double);
double** sort_matrix(double**, int, int); 

int main(void)
{
    srand(time(NULL)); // Инициализируем seed рандома
    int n, k; // Размерность массива
    scanf("%d %d", &n, &k); // Ввод n и k
 
    double** ar = malloc(sizeof(double*) * n); // Инициализация двумерного динамического массива
    for(int i = 0; i < n; i++)
        ar[i] = malloc(sizeof(double) * k); 

    for(int i = 0; i < n; i++) // Задаём рандомные значения каждой ячейке массива
    {
        for(int j = 0; j < k; j++)
        {
            scanf("%lf", &ar[i][j]);
            //ar[i][j] = rand() % 10;
        }
    }
    
    for(int i = 0; i < n; i++) // Вывод изначального массива
    {
        for(int j = 0; j < k; j++)
            printf("%.1f ", ar[i][j]);
        printf("\n");
    }

    int x = find_coll(ar, n, k, 0, 0, 0);
    int y = find_line(ar, n, k, 0, 0, 0);

    printf("%d %d", x, y);

    printf("\n");

    // ar = sort_matrix(ar, n, k);
    
    // for(int i = 0; i < n; i++) // Вывод полученного массива
    // {
    //     for(int j = 0; j < k; j++)
    //         printf("%.1f ", ar[i][j]);
    //     printf("\n");
    // }

    //double determinant = count_determinant(ar, n, k);
    //printf("%.1f", determinant);

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

double** switch_strings(double** ar, int h, int w, int a, int b) // Меняет местами строки с номерами a и b
{
    double** temp = copy_to_temp(ar, h, w);
    
    for(int i = 0; i < w; i++)
    {
        double temp_num = temp[a][i];
        temp[a][i] = temp[b][i];
        temp[b][i] = temp_num;
    }

    return temp;
}

double** sort_matrix(double** ar, int h, int w)
{
    double** temp = copy_to_temp(ar, h, w);

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
            printf("%.1f ", temp[i][j]);
        printf("\n");
    }
    
    for(int i = 0; i < h - 1; i++)
    {
        printf("DEEP IN 1\n");
        for(int j = 0; j < w - 1; j++)
        {
            printf("DEEP IN 2\n");
            if(temp[i][j] == 0.0)
            {
                for(int k = i + 1; k < h - 1; k++)
                {
                    printf("DEEP IN 3\n");
                    if(temp[k][j] != 0.0)
                    {
                        temp = switch_strings(temp, h, w, i, k);
                        k = i + 1;
                        printf("DEEP BREAKOUT 3\n");
                        break;
                    }
                    printf("DEEP OUT 3\n");
                }
            }
            printf("DEEP OUT 2\n");
        }
        printf("DEEP OUT 1\n");
    }
}

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

int find_line(double** ar, int h, int w, double a, double b, double c) // Поиск идентичной строки. Если существует, то возвращает номер строки, иначе -1
{
    for(int i = 0; i < h; i++)
    {
        if(ar[i][0] == a && ar[i][1] == b && ar[i][2] == c)
        {
            return i;
        }
    }

    return -1;
}

int find_coll(double** ar, int h, int w, double a, double b, double c) // Поиск идентичного столбца. Если существует, то возввращает номер столбца, иначе -1
{
    for(int i = 0; i < h; i++)
    {
        if(ar[0][i] == a && ar[1][i] == b && ar[2][i] == c)
        {
            return i;
        }
    }

    return -1;
}


