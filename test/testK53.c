#include<stdio.h>
#include<stdlib.h>
#include<string.h>


typedef struct {
    int ma;
    char name[30];
    int price;
    int quantity;
} data_t;

//llist.h

typedef struct node_s {
  data_t data;
  struct node_s *next;
} node_t, *root_t;

//llstudent.h

typedef data_t student_t;

// data.c


void showData(data_t data) { 
  printf("%-10d %-10d %-10d %-30s\n",data.ma,data.price,data.quantity,data.name);
}


//llist.c
// Traversing a list and show
root_t llPrint(root_t root) {
	node_t* p;
  for ( p = root; p != NULL; p = p->next) showData(p->data);
  printf("\n");
  return root;
}

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
    FILE *p;
    data_t a[100];
    int i=0;
    while (1){
        printf("Menu\n");
        printf("1.Nhap san pham \n");
        printf("2.Doc tep\n");
        printf("3.Sap xep\n");
        printf("4.Tinh tong tien\n");
        printf("5.Dem nhom san pham trung gia\n");
        printf("6.Kiem tra san pham trung ten\n");
        printf("7.Thoat\n");
        scanf("%d",&key);
        switch (key){
            case 1:
                p=fopen("sanpham.txt","w");
                if (p==NULL){
                    printf("Can not open sanpham.txt\n");
                    return 1;
                }
                while (1){
                    printf("Hay nhap ma san pham : ");
                    scanf("%d",&a[i].ma);
                    if (a[i].ma==0)
                    break;
                    for (int j=0;j<i;j++){
                        if (a[j].ma>a[i].ma)
                        scanf("%d",&a[i].ma);
                    }
                    printf("Hay nhap ten sp : ");
                    fflush(stdin);
                    fgets(a[i].name,40,stdin);
                    printf("Hay nhap gia : ");
                    do scanf("%d",&a[i].price);
                    while (a[i].price <=0);
                    printf("Hay nhap so luong : ");
                    do scanf("%d",&a[i].quantity);
                    while (a[i].quantity <0);
                    fprintf(p,"%d %d %d %s\n",a[i].ma,a[i].price,a[i].quantity,a[i].name);
                    i++;
                }
                fclose(p);
                break;
            case 7: 
                return 1;
        }
    }
    return 0;
}