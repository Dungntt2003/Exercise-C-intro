#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// data.h

// thay doi cau truc o day
typedef struct {
  char id[10];
  char name[30];
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
  printf("%s - %s - %g\n", data.id, data.name, data.grade);
}

data_t convert(char id[], char name[], float grade) {
  data_t data;
  strcpy(data.id, id);
  strcpy(data.name, name);
  data.grade = grade;
  return data;
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


// llistStudent.c

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


// Find a student with ID

void FindByID (root_t root,char id[]){
    node_t* p;
    int count=0;
    for (p = root; p!= NULL; p = p->next) {
        if (strcmp(p->data.id,id)==0) {
            printf("%s %s %g\n",p->data.id,p->data.name,p->data.grade);
            count++;
        }
    }
    if (count==0)
    printf("Khong co sinh vien nhu vay\n");
}


/// Delete a student with ID


root_t Delete_Student(root_t root,char id[]){
    node_t* p;
    int count=0;
    for (p = root; p!= NULL; p = p->next) {
        if (strcmp(p->next->data.id,id)==0) {
            root = llDeleteAfter(root,p);
            count++;
        }
    }
    if (count==0)
    printf("Khong co sinh vien nhu vay\n");
    return root;
}

void WriteOnFile (root_t root, FILE *s){
  node_t *p=NULL;
  for (p=root; p!=NULL; p=p->next){
    fprintf(s,"%s %s %g\n",p->data.id,p->data.name,p->data.grade);
  }

}

int main(){
    root_t lst =llInit();
    int key;
    data_t a[100];
    int i=0,n=0;
    data_t data;
    char str[100];
    FILE *f;
    while (1){
        printf("Menu\n");
        printf("1.Nhap 1 sinh vien\n");
        printf("2.Tim ma so sinh vien\n");
        printf("3.Xoa ma so sinh vien\n");
        printf("4.Hien thi sinh vien\n");
        printf("5. Thoat\n");
        printf("6. Ghi toan bo thong tin ra file\n");
        printf("7. In ra sinh vien dat\n");
        scanf("%d",&key);
        switch (key){
            case 1 :
                printf("Hay nhap mssv : ");
                scanf("%s",data.id);
                printf("Hay nhap ten : ");
                scanf("%s",data.name);
                printf("Hay nhap diem : ");
                scanf("%f",&data.grade);
                lst = llInsertSinhVien(lst,data);
                break;
            case 2:
                printf("Hay nhap 1 ID muon tim : ");
                scanf("%s",data.id);
                FindByID(lst,data.id);
                break;
            case 3:
                printf("Hay nhap ID muon xoa : ");
                scanf("%s",data.id);
                lst = Delete_Student(lst,data.id);
                break;
            case 4:
                llPrint(lst);
                break;
            case 5:
                return 1;
            case 6:
              f=fopen("thisinh.txt","w");
              if (f==NULL){
                printf("Khong the mo file\n");
                return 1;
              }
              WriteOnFile(lst,f);
              fclose(f);
              break;
            case 7:
              f=fopen("thisinh.txt","r");
              if (f==NULL){
                printf("Khong the mo file\n");
                return 1;
              }
              int count=0;
              while (!feof(f)){
                  fgets(str,100,f);
                  sscanf(str,"%s %s %f",a[i].id,a[i].name,&a[i].grade);
                  i++;
                  n++;
              }
              for (int j=0;j<n;j++){
                if (a[j].grade>=4)
                  {
                    printf("%s %s %g\n",a[j].id,a[j].name,a[j].grade);
                    count++;
                  }
              }
              printf("Ty le sinh vien dat la : %g\n",count*1.0/n);
              break;
        }
    }
    llDeleteAll(lst);
    return 0;
}