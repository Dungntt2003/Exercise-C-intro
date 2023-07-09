#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char id[10];
    char name[30];
    float grade;
} data;

void sort(data a[], int n)
{
    data tem;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n - 1; j)
        {
            if (a[i].grade > a[j].grade)
            {
                tem = a[i];
                a[i] = a[j];
                a[j] = tem;
            }
        }
    }
    for (int i = 0; i < n - 1; i++)
    {
        printf("%s %s %g\n", a[i].id, a[i].name, a[i].grade);
    }
}

int binarySearch(data a[], char X[], int N)
{
    int Low, Mid, High;
    Low = 0;
    High = N - 1;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (strcmp(a[Mid].id, X) < 0)
            Low = Mid + 1;
        else if (strcmp(a[Mid].id, X) > 0)
            High = Mid - 1;
        else
            return Mid; /* Found */
    }
    return -1; /* NotFound is defined as -1 */
}

int main()
{
    int key;
    data tem;
    data a[100];
    char str[100];
    char id[10];
    FILE *s;
    FILE *p;
    int i = 0, n = 0;
    while (1)
    {
        printf("Menu\n");
        printf("1.Nhap thong tin sinh vien vao file\n");
        printf("2.Doc du lieu\n");
        printf("3.Sap xep theo thu tu tang dan\n");
        printf("4.Nhap vao 1 mssv va tim kiem\n");
        printf("5.Thoat\n");
        printf("Chon 1-5 : ");
        scanf("%d", &key);
        switch (key)
        {
        case 1:
            p = fopen("data.txt", "w");
            if (p == NULL)
            {
                printf("Error\n");
                return 1;
            }
            while (1)
            {
                printf("Please enter the information for thr students\n");
                printf("Please enter the ID : ");
                scanf("%s", tem.id);
                if (strcmp(tem.id, "###") == 0)
                {
                    break;
                }
                printf("Please enter the name : ");
                scanf("%s", tem.name);
                printf("Please enter the grade : ");
                do
                    scanf("%f", &tem.grade);
                while (tem.grade < 0 || tem.grade > 10);
                fprintf(p, "%s %s %g\n", tem.id, tem.name, tem.grade);
            }
            fclose(p);
            break;
        case 2:
            s = fopen("data.txt", "r");
            if (s == NULL)
            {
                printf("Error\n");
                return 1;
            }
            while (!feof(s))
            {
                fgets(str, 100, s);
                sscanf(str, "%s %s %f", a[i].id, a[i].name, &a[i].grade);
                i++;
                n++;
            }
            for (int j = 0; j < n - 1; j++)
            {
                printf("%s %s %g\n", a[j].id, a[j].name, a[j].grade);
            }
            fclose(s);
            break;
        case 3:
                for (int i = 0; i < n - 1; i++)
                {
                    for (int j = i + 1; j < n - 1; j++)
                    {
                        if (a[i].grade > a[j].grade)
                        {
                            tem = a[i];
                            a[i] = a[j];
                            a[j] = tem;
                        }
                    }
                }
                for (int i = 0; i < n - 1; i++)
                {
                    printf("%s %s %g\n", a[i].id, a[i].name, a[i].grade);
                }
            
            break;
        case 4:
            printf("Please enter the id you want search : ");
            scanf("%s", id);
            int k = binarySearch(a, id, n - 1);
            if (k == -1)
            {
                printf("Not Found in this database\n");
            }
            else
                printf("%s %s %g\n", a[k].id, a[k].name, a[k].grade);
            break;
        case 5:
            return 1;
        }
    }
    return 0;
}