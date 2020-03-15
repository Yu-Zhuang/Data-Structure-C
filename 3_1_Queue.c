#include<stdio.h>
#include<stdlib.h>

typedef struct Q{
	int val;
	struct Q *next;
}Queue;
#define SIZE 7

void Enqueue(Queue* Q, int num);
void Dequeue(Queue* Q, int* num); 
void printQueue(Queue* Q);

int main(void){
	Queue *queue=(Queue*)malloc(sizeof(Queue)); //announce variable 
	queue->val=0; queue->next=NULL; //initialize variable 

	int list[SIZE]={ 3,2,6,1,7,4,5 };
	int nums[SIZE]={0};

	printf("===============Enqueue==============\n");
	for(int i=0;i<SIZE;i++){
		Enqueue(queue, list[i]);
		printQueue(queue);
	}
	printf("===============Dequeue==============\n");
	for(int i=0;i<SIZE;i++){
		Dequeue(queue, &list[i]);
		printQueue(queue);
	}
	return 0;
}
void Enqueue(Queue* Q, int num){
	Queue *newnode=(Queue*)malloc(sizeof(Queue));
	newnode->val=num;
	newnode->next=NULL;
	while(Q->next) Q=Q->next;
	Q->next=newnode;
}
void Dequeue(Queue* Q, int* num){
	*num=Q->next->val;
	Q->next=Q->next->next;
}
void printQueue(Queue* Q){
	Q=Q->next;
	while(Q) { printf("%d ", Q->val); Q=Q->next; }
	printf("\nend\n");
}





