#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    char id[20];
    char name[20];
    float grade;
} data;




 int binarySearch(data A[], char id[], int N) {
  int Low, Mid, High;
  Low = 0;
  High = N - 1;
  while (Low <= High) {
    Mid = (Low + High) / 2;
    if (strcmp(A[Mid].id,id)<0)
      Low = Mid + 1;
    else if (strcmp(A[Mid].id,id)>0)
      High = Mid - 1;
    else
      return Mid; /* Found */
  }
  return -1; /* NotFound is defined as -1 */
}

int main(){
    int key;
    data tem;
    char str[100];
    data a[100];
    int i=0,n=0;
    FILE *p,*f;
    while (1){
        printf("Menu\n");
        printf("1.Nhap thong tin ra file\n");
        printf("2.Doc du lieu file ra 1 mang\n");
        printf("3.Sap xep mang tang dan\n");
        printf("4.Dung binary search\n");
        printf("5.Thoat\n");
        printf("Hay chon : ");
        scanf("%d",&key);
        switch (key) {  
            case 1:
                p=fopen("sv.txt","w");
                if (p==NULL){
                    printf("File not found\n");
                    return 1;
                }
                while (1){
                    printf("Hay nhap mssv : ");
                    scanf("%s",tem.id);
                    printf("Hay nhap ten sinh vien : ");
                    scanf("%s",tem.name);
                    if (strcmp(tem.name,"###")==0)
                    break;
                    printf("Hay nhap diem : ");
                    do scanf("%f",&tem.grade);
                    while (tem.grade<0 || tem.grade>10);
                    fprintf(p,"%s %s %g\n",tem.id,tem.name,tem.grade);

                }
                fclose(p);
                break;
            case 2:
                f=fopen("sv.txt","r");
                if (f==NULL){
                    printf("File not found\n");
                    return 1;
                }
                while (!feof(f)){
                    fgets(str,100,f);
                    sscanf(str,"%s %s %f",a[i].id,a[i].name,&a[i].grade);
                    i++;
                    n++;
                 }
                 for (int j=0;j<n-1;j++){

                    printf("%s %s %f\n",a[j].id,a[j].name,a[j].grade);
                 }
                 fclose(f);
                 break;
            case 3:
                for (int j=0;j<n-1;j++){
                    for (int k=j+1;k<n-1;k++){
                        if (strcmp(a[j].id,a[k].id)>0)
                        {
                            tem=a[j];
                            a[j]=a[k];
                            a[k]=tem;
                        }
                    }
                }
                for (int j=0;j<n-1;j++)
                printf("%s %s %g\n",a[j].id,a[j].name,a[j].grade);
                break;
            case 4:
                printf("Hay nhap vao id mon tim : ");
                scanf("%s",tem.id);
                if (binarySearch(a,tem.id,n-1)==-1)
                {
                    printf("Khong thay\n");
                }
                else 
                {
                    int k =binarySearch(a,tem.id,n-1);
                    printf("%s %s %g\n",a[k].id,a[k].name,a[k].grade);
                }
                break;
            case 5:
                return 1;
        }
    }
}