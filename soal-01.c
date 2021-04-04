#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char nama[100];
    int calMaks;
    int calNow;
    struct node* next;
}node;

typedef struct headS{
	node* head;
}headS;

typedef struct tailS{
    node* tail;
}tailS;

void push(headS* stack, char namaS[100], int maksCal, int nowCal){
	node* nodeNew;
	nodeNew = (node*) malloc(sizeof(node));

	strcpy(nodeNew->nama,namaS);
	nodeNew->calMaks = maksCal;
	nodeNew->calNow = nowCal;
	nodeNew->next=stack->head;
	stack->head=nodeNew;
}


headS sortStack(headS *nodeHead){
char name[100];
headS *tempIn = nodeHead;
headS *HHs;
HHs = (headS*) malloc(sizeof(headS));
HHs->head = NULL;
while (tempIn->head != NULL){
    strcpy(name, tempIn->head->nama);
    int tempm = tempIn->head->calMaks;
    int tempn = tempIn->head->calNow;
    popP(&tempIn->head);
    while ((HHs->head!=NULL)&&(HHs->head->calMaks > tempm)){
        push(tempIn,HHs->head->nama,HHs->head->calMaks,HHs->head->calNow);
        popP(&HHs->head);
    }
    push(HHs,name,tempm,tempn);
}
return (*HHs);
}


void printList(node *nodes){
    node *temp = nodes;
    printf("\n");
    while (temp!=NULL)
    {
        printf("%s|%d|%d ", temp->nama, temp->calMaks, temp->calNow);
        temp = temp->next;
    }
}

void popP(node** nodes){
    node* nodes2 = *nodes;
    (*nodes) = (*nodes)->next;
    free(nodes2);
}

int search(node *nodes, int cariNow){
    node *temp = nodes;
    int count;
    while(temp!=NULL){
        if (temp->calNow <= cariNow){
            count++;
        }
        temp = temp->next;
    }
    return count;
}

void findTail(node *nodes, tailS* tailss){
    node *temp = nodes;
    while (temp!=NULL){
        if(temp->next == NULL){
            tailss->tail = temp;
        }
        temp = temp->next;
    }
}

void pushTail(tailS* stack, char namaS[100], int maksCal, int nowCal){
	node* nodeNew;
	nodeNew = (node*) malloc(sizeof(node));

	strcpy(nodeNew->nama,namaS);
	nodeNew->calMaks = maksCal;
	nodeNew->calNow = nowCal;
	nodeNew->next=NULL;
	stack->tail->next=nodeNew;
}

int main (){
    headS *LL;
    LL = (headS*) malloc(sizeof(headS));
    LL->head = NULL;
    tailS *HH;
    HH = (tailS*) malloc(sizeof(tailS));
    int noEnd = 1;
    char name[100], lanjut;
    int calm, caln;
    int iter, cari,jumcari;
    while (noEnd == 1){
            printf ("Masukkan nama : ");
            scanf("%s", &name);
            printf ("Masukkan kalori maks : ");
            scanf("%d", &calm);
            printf ("Masukkan kalori yang diterima : ");
            scanf("%d", &caln);
            if ((calm > 0)&&(caln > 0)){
            push(LL,name,calm,caln);
            }
            printf ("y untuk lanjut n untuk berhenti : ");
            scanf(" %c", &lanjut);
            if (lanjut == 'n'){
                noEnd = 0;
            }
    }
    printList(LL->head);
    headS temp = sortStack(LL);
    *LL=temp;
    printList(LL->head);
    printf("\nMasukkan jumlah data yang ingin dihapus : ");
    scanf(" %d", &iter);
    for (int i=0;i<iter;i++){
        popP(&LL->head);
    }
    printList(LL->head);
    printf("\nMasukkan minimum kalori yang diterima tubuh : ");
    scanf(" %d",&cari);
    jumcari = search(LL->head,cari);
    printf("\nJumlah user dengan kalori saat ini dibawah %d ada sebanyak %d\n", cari, jumcari);
    findTail(LL->head,HH);
    printf ("Masukkan nama : ");
    scanf("%s", &name);
    printf ("Masukkan kalori maks : ");
    scanf("%d", &calm);
    printf ("Masukkan kalori yang diterima : ");
    scanf("%d", &caln);
    if ((calm > 0)&&(caln > 0)){
        pushTail(HH,name,calm,caln);
    }
    printList(LL->head);
}
