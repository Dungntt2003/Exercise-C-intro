#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// data.h


typedef struct {
  char place[30];
  int hour;
  int minute;
} data_t;

//llist.h

typedef struct node_s {
  data_t data;
  struct node_s *next;
} node_t, *root_t;

//llstudent.h


// data.c


void showData(data_t data) { 
  printf("%-50s %-10d %-10d\n", data.place, data.hour, data.minute);
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


void Find_Place(root_t root, char place[]){
    node_t *p=NULL;
    int count=0;
    for (p=root; p!=NULL; p=p->next){
        if (strcmp(p->data.place,place)==0){
            printf("%d:%d,",p->data.hour,p->data.minute);
            count++;
        }
    }
    printf("\n");
    if (count==0){
        printf("Ban chua toi dia diem do\n");
    }
}

void Find_Time(root_t root,int hour,int minute){
    node_t *p=NULL;
    int count=0;
    for (p=root; p!=NULL; p=p->next){
        if (p->data.hour==hour && p->data.minute==minute){
            printf("%s\n",p->data.place);
            count++;
        }
    }
    printf("\n");
    if (count==0){
       printf("Khong thay lich su di chuyen\n");
    }

}

int check_time(int hour, int minute, int hour1, int minute1)
{
    if (hour1>hour)
    return 1;
    if (hour1==hour && minute1>minute)
    return 1;
}


int Check_Covid (root_t root,char place[],int hour,int minute){
    node_t *p=NULL;
    for (p=root; p!=NULL; p=p->next){
        if (strcmp(p->data.place,place)==0 && check_time(hour,minute,p->data.hour,p->data.minute)==1){
            return 1;
        }
    }
    return 0;
}

int main(){
    int key;
    char str[200];
    root_t lst = llInit();
    FILE *p;
    data_t data;
    int hour,minute;
    char place[40];
    while (1){
        printf("Menu\n");
        printf("1.Nap du lieu log lich su di chuyen\n");
        printf("2.In ra lich su di chuyen\n");
        printf("3.Tim kiem lich su di chuyen theo dia diem\n");
        printf("4.Tim kiem thong tin di chuyen theo thoi gian\n");
        printf("5.Kiem tra truy vet moi nhat\n");
        printf("6.Thoat\n");
        printf("Hay nhap : ");
        scanf("%d",&key);
        switch (key){
            case 1:
                p=fopen("log.txt","r");
                if (p == NULL) {
                    printf("File not found\n");
                    return 1;
                }
                while (!feof(p)){
                    fgets(str,200,p);
                    sscanf(str,"%s %d %d",data.place,&data.hour,&data.minute);
                    lst = llInsertTail(lst,data);
                }
                printf("Doc thanh cong du lieu\n");
                fclose(p);
                break;
            case 2:
                printf("%-50s %-10s %-10s\n","Dia diem","Gio","Phut");
                llPrint(lst);
                break;
            case 3:
                printf("Hay nhap vao dia diem ban muon tim : ");
                scanf("%s",place);
                Find_Place(lst,place);
                break;
            case 4:
                printf("Hay nhap thoi gian : ");
                do scanf("%d",&hour);
                while (hour <0 || hour >24);
                printf("Nhap phut : ");
                do scanf("%d",&minute);
                while (minute <0 || minute >60);
                Find_Time(lst,hour,minute);
                break;
            case 5:
                printf("Hay nhap lich trinh cua benh nhan covid : ");
                scanf("%s %d %d",place,&hour,&minute);
                if (Check_Covid(lst,place,hour,minute)==1)
                printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lpa tuc\n");
                else printf("Lich su di chuyen cua ban OK\n");
                break;
            case 6:
                llDeleteAll(lst);
                return 1;
        }
    }
    return 0;
}