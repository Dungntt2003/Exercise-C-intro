#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    int item;
    char name[50];
    char mota[100];
    int price;
    int quantity;

} data;

int binarySearch(data a[], int ma, int N)
{
    int Low, Mid, High;
    Low = 0;
    High = N - 1;
    while (Low <= High)
    {
        Mid = (Low + High) / 2;
        if (a[Mid].item <ma)
            Low = Mid + 1;
        else if (a[Mid].item > ma)
            High = Mid - 1;
        else
            return Mid; /* Found */
    }
    return -1; /* NotFound is defined as -1 */
}

int main()
{
    int key;
    char str[200];
    data a[100];
    data tem;
    int n=0;
    int i=0;
    int ma;
    FILE *p;
    FILE *s;
    while (1)
    {
        printf("Menu\n");
        printf("1.Write data to the file\n");
        printf("2.Read data from the file\n");
        printf("3.Find item with the matching\n");
        printf("4.Exit\n");
        printf("Enter 1-4 : ");
        scanf("%d", &key);
        switch (key)
        {
        case 1:
            p=fopen("data.txt", "w");
            if (p==NULL){
                printf("Cannot open file\n");
                break;
            }
            while (1)
            {
                printf("Enter the information for the item\n");
                printf("Enter the item : ");
                do scanf("%d",&tem.item);
                while (tem.item<100 || tem.item>500);
                printf("Enter the name : ");
                scanf("%s",tem.name);
                if (strcmp(tem.name,"###")==0)
                break;
                printf("Enter the mota : ");
                scanf("%s",tem.mota);
                printf("Enter the price : ");
                scanf("%d",&tem.price);
                printf("Enter the quantity : ");
                scanf("%d",&tem.quantity);
                fprintf(p,"%d %s %s %d %d\n",tem.item,tem.name,tem.mota,tem.price,tem.quantity);
            }
            fclose(p);
            break;

        case 2:
            s=fopen("data.txt", "r");
            if (s==NULL){
                printf("Cannot open file\n");
                return 1;
            }
            while (!feof(s)){
                fgets(str, 200, s);
                sscanf(str, "%d %s %s %d %d", &a[i].item, a[i].name,a[i].mota, &a[i].price, &a[i].quantity);
                i++;
                n++;
            }
            for (int j=0;j<n-1;j++){
                printf("%d %s %s %d %d\n",a[j].item,a[j].name,a[j].mota,a[j].price,a[j].quantity);
            }
            break;
        case 3:
            printf("Enter the ma you want to search : ");
            scanf("%d",&ma);
            int k=binarySearch(a,ma,n-1);
            if (k==-1)
            {
                printf("Not found\n");

            }
            else {
                printf("%d %s %s %d %d\n",a[k].item,a[k].name,a[k].mota,a[k].price,a[k].quantity);
            }
            break;
        case 4:
        return 1;
        }
    }
    return 0;
}