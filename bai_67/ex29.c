#include<stdio.h>
#include<string.h>

int main(){
    int count=0;
    int a[100];
    int key;
    int n;
    printf("Hay nhap vao so phan tu cua mang : ");
    scanf("%d",&n);
    for (int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    printf("Hay nhap so muon tim : ");
    scanf("%d",&key);
    for (int i=0;i<n;i++){
        if (a[i]==key){
            printf("%d\t",i);
            count++;
        }
    }
    if (count==0)
    printf("Can not found\n");
    return 0;
}