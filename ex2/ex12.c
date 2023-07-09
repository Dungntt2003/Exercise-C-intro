#include <stdio.h>


int main(){
    FILE *p,*s;
    p=fopen("float1.txt","w+");
    s=fopen("float2.txt","w");
    int a[100];
    int i,n;
    int m;
    char str[100];
    if (p==NULL || s==NULL) {
        printf("Cannot open\n");
        return 1;
    }
    printf("Hay nhap vao so phan tu cua mang \n");
    scanf("%d",&n);
    fprintf(p,"%d\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
        fprintf(p,"%d\n",a[i]);
    }
    fseek(p,0,SEEK_SET);
    fgets(str,100,p);
    sscanf(str,"%d",&n);
    while (!feof(p)){
        fgets(str,100,p);
        sscanf(str,"%d",&m);
        if (m>=5)
        fprintf(s,"%d\n",m);
    }
    fclose(p);
    fclose(s);
    return 0;
}