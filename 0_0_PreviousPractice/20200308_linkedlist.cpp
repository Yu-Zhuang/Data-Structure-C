#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct link{
	int val;
	struct link *next;
}LINK;

void createLink(LINK* link, int* nums, int numsSize);
void insertLink(LINK* link, int site, int data);
void deletLink(LINK* link, int site);
void reverseLink(LINK* link);
void printLink(LINK*);

int main(void){
	srand(time(NULL));
	LINK* link=(LINK*)malloc(sizeof(LINK));
	int list[7]={0};
	//initialize 
	printf("templet:\t");
	link->val=0; link->next=NULL;
	for(int i=0;i<7;i++) { list[i]=rand()%10+1; printf("%d,", list[i]); }	
	printf("\n");	
	//run function and output
	printf("linked list:\t");
	createLink(link, list, 7);
	printLink(link);

	printf("after insert:\t");
	insertLink(link,1,9);
	printLink(link);

	printf("after delete:\t");
	deletLink(link,3);
	printLink(link);

	printf("after reverse:\t");
	reverseLink(link);
	printLink(link);

	return 0;
}
void reverseLink(LINK* link){
	LINK *ptr, *end=NULL;
	while(link->next){
		ptr=link->next->next;
		link->next->next=end;
		end=link->next;
		link->next=ptr;
	}
	link->next=end;
}
void createLink(LINK* link, int* nums, int numsSize){
	LINK* ptr=link;
	for(int i=0;i<numsSize;i++){
		LINK *newnode=(LINK*)malloc(sizeof(LINK));
		newnode->val=nums[i]; newnode->next=NULL;
		ptr->next=newnode;
		ptr=newnode;
	}
}
void insertLink(LINK* link, int site, int data){
	LINK *ptr=link, *newnode=(LINK*)malloc(sizeof(LINK));
	int tmp=0;
	newnode->val=data;
	while(tmp!=site) { ptr=ptr->next; tmp++; if(!ptr) break; }
	if(ptr){
		newnode->next=ptr->next;
		ptr->next=newnode;
	}
}
void deletLink(LINK* link, int site){
	LINK *ptr=link;
	int tmp=0;
	while(tmp!=site) { ptr=ptr->next; tmp++; if(!ptr) break; }
	if(ptr) ptr->next=ptr->next->next;
}
void printLink(LINK* link){ 
	LINK* ptr=link->next;
	while(ptr){
		printf("%d,",ptr->val);
		ptr=ptr->next;
	}printf("\n");
}

