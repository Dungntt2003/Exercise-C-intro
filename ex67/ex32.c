#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
    int id;
    char name[30];
    char des[100];
    int price;
    int quantity;

} data;



 int binarySearch(data A[],int X, int N) {
  int Low, Mid, High;
  Low = 0;
  High = N - 1;
  while (Low <= High) {
    Mid = (Low + High) / 2;
    if (A[Mid].id < X)
      Low = Mid + 1;
    else if (A[Mid].id > X)
      High = Mid - 1;
    else
      return Mid; /* Found */
  }
  return -1; /* NotFound is defined as -1 */
}

int main(){
    int key;
    data a[100];
    int i=0,n=0;
    FILE *p;
    data tem;
    char str[100];
    while (1){
        printf("Menu\n");
        printf("1.Nhap thong tin vao file\n");
        printf("2.Doc du lieu\n");
        printf("3.Tim binary search \n");
        printf("4.Thoat\n");
        printf("Hay chon : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                p=fopen("data.txt","w");
                if (p==NULL){
                    printf("Can open file\n");
                    return 1;
                }
                while (1){
                    printf("Nhap ma : ");
                    scanf("%d",&tem.id);
                    if (tem.id==-1)
                    {
                        break;
                    }
                    if (tem.id<100 || tem.id >500)
                    scanf("%d",&tem.id);
                    printf("Nhap ten san pham : ");
                    scanf("%s",tem.name);
                    printf("Nhap mo ta : ");
                    scanf("%s",tem.des);
                    printf("Nhap gia va so luong : ");
                    scanf("%d %d",&tem.price,&tem.quantity);
                    fprintf(p,"%d %s %s %d %d\n",tem.id,tem.name,tem.des,tem.price,tem.quantity);

                }
                fclose(p);
                break;
            case 2:
                p=fopen("data.txt","r");
                if (p==NULL){
                    printf("Can open file\n");
                    return 1;
                }
                while (!feof(p)){
                    fgets(str,100,p);
                    sscanf(str,"%d %s %s %d %d",&a[i].id,a[i].name,a[i].des,&a[i].price,&a[i].quantity);
                    i++;
                    n++;
                }
                for (int j=0; j<n-1 ;j++){
                    printf("%d %s %s %d %d\n",a[j].id,a[j].name,a[j].des,a[j].price,a[j].quantity);
                }
                fclose(p);
                break;
            case 3:
                printf("Hay nhap ma muon tim : ");
                scanf("%d",&tem.id);
                int k =binarySearch(a,tem.id,n-1);
                if (k==-1)
                printf("Can not found\n");
                else {
                    printf("%s %s %d %d\n",a[k].name,a[k].des,a[k].price,a[k].quantity);
                }
                break;
            case 4:
                return 1;

                
        }
    }
    return 0;
}