#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct {
    char id[10];
    char name[30];
    float grade;
} data;

int main(){
    FILE *p;
    int i=0,n=0;
    FILE *s;
    p=fopen("thisinh.txt","w+");
    s=fopen("thisinh1.txt","w");
    if (p==NULL || s==NULL){
        printf("Can not open file\n");
        return 1;
    }
    data tem;
    data a[100];
    char str[100];
    while (1){
        printf("Nhap du lieu cho sinh vien : ");
        printf("Hay nhap mssv: ");
        scanf("%s",tem.id);
        if (strcmp(tem.id,"-1")==0)
        break;
        printf("Hay ten va diem : ");
        scanf("%s %f",tem.name,&tem.grade);
        fprintf(p,"%s %s %g\n",tem.id,tem.name,tem.grade);
    }
    fseek(p,0,SEEK_SET);
    while (!feof(p)){
        fgets(str,100,p);
        sscanf(str,"%s %s %f",a[i].id,a[i].name,&a[i].grade);
        printf("%s %s %g\n",a[i].id,a[i].name,a[i].grade);
        if (a[i].grade>=5)
        {
            fprintf(s,"%s %s %g\n",a[i].id,a[i].name,a[i].grade);
        }
        i++;
    }
    fclose(p);
    fclose(s);
    return 0;

    }