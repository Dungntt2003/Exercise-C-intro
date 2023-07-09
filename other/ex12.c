#include<stdio.h>
#include<string.h>


int main(){
    FILE *p;
    FILE *s;
    int n=0;
    int i=0;
    float a[100];
    char chuoi[100];
    p=fopen("float.txt","r");
    s=fopen("float1.txt","w");
    if (p==NULL || s==NULL){
        printf("Can not open file\n");
        return 1;
    }
    while (!feof(p)){
        fgets(chuoi,100,p);
        sscanf(chuoi,"%f",&a[i]);
        i++;
        n++;
    }
    for (int j=0;j<n;j++)
    {
        if (a[j]>=5)
        printf("%f\n",a[j]);
        fprintf(s,"%f\n",a[j]);
    }
    fclose(s);
    fclose(p);
    return 0;
}