#include<stdio.h>
#include<stdlib.h>
int main(){
    FILE *p,*s;
    int n;
    int a[100];
    int i=0;
    char str[100];
    char filename[100],name[200];
    printf("Nhap file doc : ");
    scanf("%s",filename);
    printf("Nhap file ghi : ");
    scanf("%s",name);
    p=fopen(filename,"r");
    s=fopen(name,"w");
    if (p==NULL || s==NULL){
        printf("Can not open\n");
        return 0;
    }
    fgets(str,100,p);
    sscanf(str, "%d", &n);
    while (!feof(p)){
        fgets(str,100,p);
        sscanf(str, "%d", &a[i]);
        i++;
    }
    for (int j=0;j<n;j++)
    {
        if (a[j]>5)
        fprintf(s,"%d\t",a[j]);

    }
    return 0;
}