#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
    int number;
    char name[255];
    int quantity;
    double price;

} dishes;


typedef struct {
    int ID;
    int order[8];
    long total;
} data_t;

typedef struct node_s {
  data_t data;
  struct node_s *next;
} node_t, *root_t;

//llstudent.h

typedef data_t student_t;

// data.c




//llist.c
// Traversing a list and show

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


int main(){
    int key;
    data_t tem;
    data_t b[100];
    dishes a[100];
    FILE *p;
    int n;
    int k=0;
    int i=0;
    char str[200];
    root_t lst =llInit();
    while (1){
        printf("Menu\n");
        printf("1.Danh sach mon an hom nay\n");
        printf("2.Nhan order\n");
        printf("3.Thong tin tat ca cac order\n");
        printf("4.Mon an ua chuong nhat\n");
        printf("5.Thoat\n");
        printf("Choose : ");
        scanf("%d", &key);
        switch (key){
            case 1:
                p=fopen("thucdontheongay.txt","r");
                if (p==NULL){
                    printf("Can't open thucdontheongay\n");
                    return 1;
                } 
                fgets(str,200,p);
                sscanf(str,"%d",&n);
                while (!feof(p)){
                    fgets(str,200,p);
                    sscanf(str,"%d %s %d %lf",&a[i].number,a[i].name,&a[i].quantity,&a[i].price);
                    i++;
                }
                printf("%-10s %-40s %-30s %-10s\n","ID","Ten mon","So luong ton","Gia tien");
                for (int j=0;j<n;j++){
                    printf("%-10d %-40s %-30d %-10lf\n",a[j].number,a[j].name,a[j].quantity,a[j].price);
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
                printf("Hay nhap order cho mon\n");
                for (int j=0;j<n;j++){
                    printf("Mon %s\n",a[j].name);
                    if (a[j].quantity>0)
                        {
                            scanf("%d",&tem.order[j]);
                            a[j].quantity=a[j].quantity- tem.order[j];
                        }
                    else {
                        printf("Xin loi, nha hang khong du suat an cho quy khach");
                        tem.order[j]=0;
                    }
                    tem.total = tem.order[j]*a[j].price;
                }
                printf("Tong so tien phai tra la : %ld\n",tem.total);
                tem.ID=k;
                b[k]=tem;
                k++;
                lst= llInsertHead(lst,b[k]);
                p=fopen("thucdonmoingay.txt","w");
                if (p==NULL)
                {
                    printf("Can not open\n");
                    return 1;
                }
                fprintf(p,"%d\n",n);
                for (int j=0;j<n;j++){
                    fprintf(p,"%d %s %d %lf\n",a[j].number,a[j].name,a[i].quantity,a[j].price);
                }
                fclose(p);
                break;
            
            case 5:
                return 1;
        }
    }
    return 0;
}

