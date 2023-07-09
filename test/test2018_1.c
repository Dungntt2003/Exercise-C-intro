#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// data.h


typedef struct {
    int id;
    char name[255];
    int quantity;
    double price;
} dish;

typedef struct {
  int id;
  int order[8];
  double total;
} data_t;

//llist.h

typedef struct node_s {
  data_t data;
  struct node_s *next;
} node_t, *root_t;

//llstudent.h

typedef data_t student_t;

// data.c


//llist.c
// Traversing a list and show
// root_t llPrint(root_t root) {
// 	node_t* p;
//   for ( p = root; p != NULL; p = p->next) showData(p->data);
//   printf("\n");
//   return root;
// }

// Create a new Node
// return:
//  - on SUCCESS: return a pointer to new Node
//  - on FAIL   : return a NULL pointer
node_t* createNewNode(const data_t data) {
  node_t* newNode = (node_t*)malloc(sizeof(node_t));
  if (newNode == NULL) return NULL;

  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

root_t llInit() { return NULL; }

node_t* llSeek(root_t root, int index) {
  node_t* p;
  for (p = root; index > 0 && (p != NULL); index--) p = p->next;
  return p;
}

/* === Insert ============================================== */

root_t llInsertHead(root_t root, const data_t data) {
  node_t* pNewNode = createNewNode(data);
  pNewNode->next = root;
  return (root_t)pNewNode;
}

root_t llInsertTail(root_t root, const data_t data) {
  node_t* pNewNode = createNewNode(data);

  if (root == NULL) return (root_t)pNewNode;

  node_t* p = NULL;
  for (p = root; p->next != NULL; p = p->next)
    ;
  p->next = pNewNode;
  return root;
}

root_t llInsertAfter(root_t root, node_t* pAElem, const data_t data) {
  if (pAElem == NULL) return root;

  node_t* pNewNode = createNewNode(data);
  pNewNode->next = pAElem->next;
  pAElem->next = pNewNode;

  return root;
}

/* === Delete ============================================== */

root_t llDeleteHead(root_t root) {
  if (root == NULL) return NULL;

  node_t* p = root->next;
  free(root);
  return (root_t)p;
}

root_t llDeleteTail(root_t root) {
  if (root == NULL) return NULL;
  if (root->next == NULL) {
    free(root);
    return NULL;
  }

  node_t* p;
  // Find previous node of Tail
  for (p = root; p->next->next != NULL; p = p->next)
    ;

  free(p->next);
  p->next = NULL;
  return (root_t)root;
}

root_t llDeleteAfter(root_t root, node_t* pA) {
  if ((pA == NULL) || (pA->next == NULL)) return root;

  node_t* pToDelElem = pA->next;
  pA->next = pA->next->next;

  free(pToDelElem);
  return root;
}

root_t llDeleteAll(root_t root) {
  node_t* p = NULL;
  for (; root != NULL; root = p) {
    p = root->next;
    free(root);
  }
  return NULL;
}

/* === Tools ========================================= */
int llLength(root_t root) {
  int count;
  for (count = 0; root!=NULL; root = root->next) count++;
  return count;
}

root_t LLReverse(root_t root) {
  node_t *cur, *prev;

  for (cur = prev = NULL; root != NULL;) {
    cur = root;
    root = root->next;
    cur->next = prev;
    prev = cur;
  }
  return root;
}

int isEmpty(root_t root) { return root == NULL; }



void print_dslk(root_t root, dish a[],int n){
  node_t *p=NULL;
  int i=0;
  for (p=root;p!=NULL;  p=p->next){
    printf("Don hang so %d\n",i+1);
    printf("%-20s %-30s %-30s\n","Mon da chon","So luong","Thanh tien");
    for (int j=0;j<n;j++){
      printf("%-20s %-30d %-30lf",a[j].name,p->data.order[j],p->data.total);
    }
  }
}


int max(root_t root,dish a[],int n){
  node_t *p;
  int b[100];
  for (int i=0;i<n;i++) b[i]=0;
  for (p = root; p!=NULL; p = p->next){
    for (int j=0;j<n;j++){
        b[j]=b[j]+p->data.order[j];
    }
  }
  int max=0;
  for (int j=0;j<n;j++){
    if (b[j]>max){
      max=b[j];
    }
  }
  return max;
}

int main(){
    int key;
    FILE *p;
    dish a[100];
    int n;
    data_t tem;
    root_t lst=llInit();
    int k=0;
    char str[100];
    int i=0;
    while (1){
        printf("Menu\n");
        printf("1.Danh sach mon an hom nay\n");
        printf("2.Nhan order\n");
        printf("3.Thong tin tat ca order\n");
        printf("4.Mon an ua chuong nhat\n");
        printf("5.Thoat\n");
        printf("Chon : ");
        scanf("%d",&key);
        switch (key){
          case 1 :
            p=fopen("thucdontheongay.txt","r");
            if (p==NULL){
              printf("Can not open thucdontheongay\n");
              return 1;
            }
            printf("%-10s %-30s %-20s %-30s\n","ID","Ten mon","So luong ton","Gia tien");
            fgets(str,100,p);
            sscanf(str,"%d",&n);
            while (!feof(p)){
                fgets(str,100,p);
                sscanf(str,"%d %s %d %lf",&a[i].id,a[i].name,&a[i].quantity,&a[i].price);
                if (a[i].quantity>0)
                printf("%-10d %-30s %-20d %-30lf\n",a[i].id,a[i].name,a[i].quantity,a[i].price);
                i++;
            }
            fclose(p);
            break;
          case 2:
           if (n<8){
            for (int j=n;j<8;j++){
              tem.order[j]=-1;
            }
           }
           tem.total=0;
           printf("Hay nhap don dat hang cua khach\n");
           
           for (int j=0;j<n;j++){
            printf("Hay nhap dat hang cho mon %s : ",a[j].name);
            scanf("%d",&tem.order[j]);
            if (tem.order[j]>a[j].quantity)
            {
              printf("Xin loi nha hang khong con du dap ung\n");
              tem.order[j]=0;
            }
            else if (tem.order[j]==a[j].quantity) {
              a[j].quantity=0;
            }
            else a[j].quantity=a[j].quantity-tem.order[j];
            printf("so luong da dat la : %d\n",tem.order[j]);
            printf("So tien tuong ung la %lf\n",a[j].price);
            tem.total=tem.total+tem.order[j] * a[j].price;
            printf("Tien bay gio la : %lf\n",tem.total);
           }
            tem.id=k+1;
            k++;
            lst=llInsertTail(lst,tem);
            printf("Tong so tien can tra la : %lf\n",tem.total);
            p=fopen("thucdontheongay.txt","w");
            if (p==NULL){
              printf("Cant open thucdontheongay.txt\n");
              return 1;
            }
            fprintf(p, "%d\n",n);
            for (int j=0;j<n;j++)
            {
              fprintf(p,"%d %s %d %lf\n",a[j].id,a[j].name,a[j].quantity,a[j].price);
            }
            fclose(p);
            break;
          case 3:
            print_dslk(lst,a,n);
            break;
          case 4:
            printf("So luong duoc dat lon nhat la %d\n",max(lst,a,n));
            break;
          case 5 :
            return 1;
        }
    }
    llDeleteAll(lst);
    return 0;
}