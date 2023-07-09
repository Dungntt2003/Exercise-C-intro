#include <stdio.h>
#include <string.h>


typedef struct {
    char id[10];
    char name[30];
    float grade;
} data;

int main(){
    FILE *p,*s;
    data a[100];
    data tem;
    int i=0,n=0;
    char str[100];
    p=fopen("thisinh.txt","w+");
    s=fopen("thisinh1.txt","w+");
    if (p==NULL || s==NULL){
        printf("Can open file\n");
        return 1;
    }
    while (1){
        printf("Hay nhap mssv : ");
        scanf("%s",tem.id);
        if (strcmp(tem.id,"-1")==0)
        break;
        printf("Hay nhap ten sinh vien : ");
        scanf("%s",tem.name);
        printf("Hay nhap diem sinh vien : ");
        scanf("%f",&tem.grade);
        fprintf(p,"%s %s %g\n",tem.id,tem.name,tem.grade);
    }
    fseek(p,0,SEEK_SET);
    while (!feof(p)){
        fgets(str,100,p);
        sscanf(str,"%s %s %f",a[i].id,a[i].name,&a[i].grade);
        i++;
        n++;
    }
    for (int j=0;j<n-1;j++){
        if ( a[j].grade>5 ){
            fprintf(s,"%s %s %g\n",a[j].id,a[j].name,a[j].grade);
        }
    }
    fclose(p);
    fclose(s);
    return 0;

}