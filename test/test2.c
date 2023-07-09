#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// data.h


typedef struct {
  char name[50];
  float grade;
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
  printf("%s - %g\n",data.name, data.grade);
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


void travel(root_t root, float x) {
    node_t *p=NULL;
    for (p=root;p!=NULL;p=p->next){
        if (p->data.grade>=x){
            printf("%s %f\n",p->data.name,p->data.grade);
        }
    }
}


root_t llInsertSinhVien(root_t root, const student_t sv) {
  if (root == NULL) return llInsertHead(root, sv);

  if (sv.grade > root->data.grade) {
    return llInsertHead(root, sv);
  } else if (root->next == NULL)
    return llInsertTail(root, sv);
	node_t* p;
  for (p = root; p->next != NULL; p = p->next) {
    if (sv.grade > p->next->data.grade) {
      root = llInsertAfter(root, p, sv);
      return root;
    }
  }

  return llInsertTail(root, sv);
}

void fix(char *name){
    if (name[strlen(name)-1]='\n')
        name[strlen(name)-1]='\0';
}

void print(root_t root){
    node_t *p;
    for (p=root;p!=NULL;p=p->next){
        printf("%s %f\n",p->data.name,p->data.grade);
    }
}



root_t case4 (root_t tree, root_t lst, root_t root){
    node_t *p;
    for (p=root;p!=NULL;p=p->next){
        if (p->data.grade>=8.5)
        tree= llInsertTail(tree,p->data);
    }
    for (p=lst;p!=NULL;p=p->next){
        if (p->data.grade>=8.5)
        tree= llInsertTail(tree,p->data);
    }
    return tree;
}


int main(){
    root_t root = llInit();
    node_t *l=NULL;
    root_t lst = llInit();
    root_t tree=  llInit();
    root_t sort = llInit();
    int key;
    data_t data;
    float grade;
    data_t a[100];
    int i=0,n=0;
    int k=0,m=0;
    char str[100];
    node_t *excellent = NULL;
    FILE *p,*f;
    while (1){
        printf("Menu\n");
        printf("1.Doc file\n");
        printf("2.Tim kiem\n");
        printf("3.Danh sach xuat sac\n");
        printf("4.Ghi file\n");
        printf("5.Gop danh sach\n");
        printf("6.Thoat\n");
        printf("Hay nhap : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                p=fopen("6d.txt","r");
                if (p==NULL){
                    printf("Can not open\n");
                    return 1;
                }
                while (!feof(p)){
                    fgets(data.name,100,p);
                    fflush(stdin);
                    fix(data.name);
                    fgets(str,100,p);
                    fflush(stdin);
                    sscanf(str,"%f",&data.grade);
                    a[i]=data;
                    i++;
                    n++;

                }
                for (int j=0;j<n-1;j++){
                    root= llInsertTail(root,a[j]);
                }
                fclose(p);
                f=fopen("6e.txt","r");
                if (f==NULL){
                    printf("Can not open\n");
                    return 1;
                }
                while (!feof(f)){
                    fgets(data.name,100,f);
                    fix(data.name);
                    fgets(str,100,f);
                    sscanf(str,"%f",&data.grade);
                    lst = llInsertTail(lst,data);

                }
                fclose(f);
                print(root);
                print(lst);
                break;
            case 2:
                printf("Hay nhap diem\n");
                scanf("%f",&grade);
                travel(root,grade);
                travel(lst,grade);
                break;
            case 3:
                tree= case4(tree,lst,root);
                print(tree);
                break;
            case 4:
                p=fopen("example.txt", "w");
                if (p==NULL){
                    printf("Can open file\n");
                    return 1;
                }
                for (excellent = tree;excellent!=NULL;excellent=excellent->next){
                    fprintf(p,"%s %f\n",excellent->data.name,excellent->data.grade);
                }
                fclose(p);
                break;
            case 5:
                for (l=root;l!=NULL;l=l->next){
                    a[k]=l->data;
                    k++;
                    m++;
                }
                for (l=lst;l!=NULL;l=l->next){
                    a[k]=l->data;
                    k++;
                    m++;
                }
                for (int j=0;j<m;j++){
                    sort= llInsertSinhVien(sort,a[j]);
                }
                print(sort);
                break;
            case 6: 
            return 1;
        }
    }
    return 0;
}