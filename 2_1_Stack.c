#include<stdio.h>
#include<stdlib.h>

typedef struct S{
	int val;
	struct S *next;
}Stack;
#define SIZE 7

void Push(Stack* S, int num);
void Pop(Stack* S, int* num); 
void printStack(Stack* S);

int main(void){
	Stack *stack=(Stack*)malloc(sizeof(Stack)); //announce variable 
	stack->val=0; stack->next=NULL; //initialize variable 

	int list[SIZE]={ 3,2,6,1,7,4,5 };
	int nums[SIZE]={0};

	printf("===============Push==============\n");
	for(int i=0;i<SIZE;i++){
		Push(stack, list[i]);
		printStack(stack);
	}
	printf("===============Pop==============\n");
	for(int i=0;i<SIZE;i++){
		Pop(stack, &nums[i]);
		printStack(stack);
	}
	return 0;
}
void Push(Stack* S, int num){
	Stack *newnode=(Stack*)malloc(sizeof(Stack));
	newnode->val=num;
	newnode->next=S->next;
	S->next=newnode;
}
void Pop(Stack* S, int* num){
	*num=S->next->val;
	S->next=S->next->next;
}
void printStack(Stack* S){
	S=S->next;
	while(S) { printf("%d ", S->val); S=S->next; }
	printf("\nend\n");
}





