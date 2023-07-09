#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    int a[100];
    int n;
    int count=0;
    int x;
    printf("Hay nhap tong so phan tu : ");
    scanf("%d",&n);
    for (int i=0; i<n; i++){
        scanf("%d",&a[i]);
    }
    printf("Hay nhap so can tim kiem : ");
    scanf("%d",&x);
    for (int i=0; i<n;i++){
        if (a[i]==x){
            printf("%d\t",i);
            count++;
        }
    }
    if (count==0)
    printf("Khong co so nao nhu vay\n");
    return 0;
}