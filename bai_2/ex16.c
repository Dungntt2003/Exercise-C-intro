#include<stdio.h>
#include<string.h>

int main(){
    int a[100];
    int i=0,n=0;
    FILE *p;
    p=fopen("sothuc.txt","r");
    char str[100];
    fgets(str,100,p);
    sscanf(str,"%d",&n);
    while (!feof(p)){
        fgets(str,100,p);
        sscanf(str,"%d",&a[i]);
        i++;
    }
    for (int j=0;j<n;j++){
        if (a[j]>=5)
        printf("%d\t",a[j]);
    }
    fclose(p);
    return 0;
}