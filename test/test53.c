#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// data.h


typedef struct {
  int ma;
  int price;
  int quantity;
  char name[30];
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


void fix(char *name){
  if (name != NULL && name[strlen(name)-1] == '\n'){
    name[strlen(name)-1] = '\0';
  }
}


void print(root_t root){
  node_t *p=NULL;
  for (p=root; p!=NULL; p=p->next){
    printf("%d %d %d %s\n",p->data.ma,p->data.price,p->data.quantity,p->data.name);
  }
}

// llistStudent.c

int main(){
  int key;
  root_t lst=llInit();
  data_t a[100];
  char str[100];
  FILE *p;
  int i=0,n=0;
  while (1){
    printf("Menu\n");
    printf("1.Nhap san pham\n");
    printf("2.Do tep\n");
    printf("3.Sap xep\n");
    printf("4.Tinh tong tien\n");
    printf("5.Dem nhom trung san pham\n");
    printf("6.Kiem tra san pham trung tinh\n");
    printf("7.Thoat\n");
    scanf("%d",&key);
    switch (key){
      case 1:
        p=fopen("data.txt","w");
        if (p==NULL){
          printf("Can not open file\n");
          return 1;
        }
        while (1){
          printf("Hay nhap ma, gia va so luong san pham : ");
          scanf("%d %d %d",&a[i].ma,&a[i].price,&a[i].quantity);
          printf("Hay nhap ten san pham : ");
          fflush(stdin);
          fgets(a[i].name,30,stdin);
          if (a[i].ma==0)
          break;
          for (int j=0;j<i;j++){
            if (a[j].ma==a[i].ma){
              scanf("%d",&a[i].ma);
            }
          }
          fprintf(p,"%d %d %d %s",a[i].ma,a[i].price,a[i].quantity,a[i].name);
          i++;n++;
        }
        fclose(p);
        break;
      case 2:
        i=0,n=0;
        p=fopen("data.txt","r");
        if (p==NULL){
          printf("Can not open file\n");
          return 1;
        }
        while (!feof(p)){
          fscanf(p,"%d %d %d",&a[i].ma,&a[i].price,&a[i].quantity);
          char c= fgetc(p);
          fgets(a[i].name,30,p);
          fix(a[i].name);
          lst = llInsertTail(lst,a[i]);
          i++,n++;
        }
        print(lst);
        fclose(p);
        break;
      case 3:
        for (int j=0;j<n;j++){
          printf("%d %d %d %s\n",a[j].ma,a[j].price,a[j].quantity,a[j].name);
        
        }
        break;
      case 7:
        return 1;
    }
  }
  return 0;
}
