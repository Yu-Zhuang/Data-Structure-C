#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check.h"
//  DEFINE
#define MAX 100
typedef struct stack{
    char val;
    struct stack *next;
}Stack;
typedef struct st{
    double val;
    struct st *next;    
}NUM_Stack;
//  FUNCTION_ANNOUNCEMENT
void FORMULAR_GET(char input[][MAX], int *size);
bool FORMULAR_CHECK(char input[][MAX], int size);

void FORMULAR_IN_TO_POST_FIX(char input[][MAX], int size, char *ret);
double FORMULAR_CALCULATE(char *formula);

double STR_TO_INT(char *str,int *site);

void STACK_PUSH(Stack *s, char element);
char STACK_POP(Stack *s);

void NUM_Stack_PUSH(NUM_Stack *s, double element);
double NUM_Stack_POP(NUM_Stack *s);

void LINK_PRINT(Stack *s);

//  MAIN
int main(void){
    char input[MAX][MAX], take[MAX]; memset(take,'\0', MAX);
    int size=0; //how many element in formula

    //  CONPUTION
    FORMULAR_GET(input, &size);
    FORMULAR_CHECK(input, size);
    FORMULAR_IN_TO_POST_FIX(input, size, take);
    puts(take);
    printf("%.2lf\n", FORMULAR_CALCULATE(take)); 

    //  END
    return 0;
}

//  FUNCTION
double FORMULAR_CALCULATE(char *formula){
    NUM_Stack *s=(NUM_Stack*)malloc(sizeof(NUM_Stack));
    s->next=NULL;
    double ret=0;
    int i=0;
    while(formula[i]!='\0'){
        if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/'){
            double num_1=0, num_2=0;
            num_1=NUM_Stack_POP(s);
            num_2=NUM_Stack_POP(s);
            switch(formula[i]){
                case '+': NUM_Stack_PUSH(s, num_2+num_1); break;
                case '-': NUM_Stack_PUSH(s, num_2-num_1); break;
                case '*': NUM_Stack_PUSH(s, num_2*num_1); break;
                case '/': NUM_Stack_PUSH(s, num_2/num_1); break;
                default : break;
            }
        }
        else if(formula[i]>='0'&&formula[i]<='9'){
            double num=STR_TO_INT(&formula[i], &i);
            NUM_Stack_PUSH(s,num);           
        }
        i++;
    }
    ret = s->next->val;
    return ret;
}
double STR_TO_INT(char *str, int *site){
    double ret=0;
    int i=0, ten=1;
    if(str[i+1]=='\0') return str[0]-'0'; 
    while(str[i]>='0'&&str[i]<='9'){
        ten*=10;
        i++;
    }
    site[0]+= (i-1);
    ten/=10;
    int j=0;
    for(j=0;ten!=0;j++){
        ret+=ten*(str[j]-'0');
        ten/=10;
    }  
    return ret;
}
void FORMULAR_IN_TO_POST_FIX(char input[][MAX], int size, char *ret){
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->next=NULL;
    int k=0;
    for(int i=0;i<size;i++){

        if((input[i][0]>='0'&&input[i][0]<='9')||(input[i][0]>='A'&&input[i][0]<='Z')||(input[i][0]>='a'&&input[i][0]<='z')){
            int j=0;
            while(input[i][j]) { ret[k]=input[i][j]; j++; k++; }
            ret[k]=' '; k++;
        }
        else if(input[i][0]=='('||input[i][0]=='['||input[i][0]=='{'){
            STACK_PUSH(s, input[i][0]);
        }
        else if((input[i][0]==')'||input[i][0]==']'||input[i][0]=='}' )&& s->next){
            char tmp=STACK_POP(s), trgt;
            int flag=0;
            switch (input[i][0]){
                case ')': trgt='('; break;
                case ']': trgt='['; break;
                case '}': trgt='{'; break;
                default : break;
            }
            if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; }
            while( (tmp!=trgt)&& s->next){
                tmp=STACK_POP(s);
                if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; }
            }
        }
        else if(input[i][0]=='+'||input[i][0]=='-'||input[i][0]=='*'||input[i][0]=='/'){
            if(s->next&&(s->next->val=='+'||s->next->val=='-')&&(input[i][0]=='*'||input[i][0]=='/')){
                STACK_PUSH(s, input[i][0]);                
            }
            else{
                if(s->next && (s->next->val!='('&&s->next->val!='['&&s->next->val!='{')) { 
                    char tmp=STACK_POP(s);
                    if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; }
                }
                STACK_PUSH(s,input[i][0]);
            }
        }
        LINK_PRINT(s);
    }
    while(s->next) { 
        char tmp=STACK_POP(s);
        if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; } 
    }
}
void NUM_Stack_PUSH(NUM_Stack *s, double element){
    NUM_Stack *newnode=(NUM_Stack*)malloc(sizeof(NUM_Stack));
    newnode->val=element;
    newnode->next = s->next;
    s->next = newnode;    
}
double NUM_Stack_POP(NUM_Stack *s){
    if(s->next){
        NUM_Stack *tmp=s->next;
        double ret=tmp->val;
        s->next=s->next->next;
        free(tmp);
        return ret;
    }
    printf("\t[ warning: INT_Stack is empty! ]\n");
    return NULL;    
}
void STACK_PUSH(Stack *s, char element){
    Stack *newnode=(Stack*)malloc(sizeof(Stack));
    newnode->val=element;
    newnode->next = s->next;
    s->next = newnode;
}

char STACK_POP(Stack *s){
    if(s->next){
        Stack *tmp=s->next;
        char ret=tmp->val;
        s->next=s->next->next;
        free(tmp);
        return ret;
    }
    printf("\t[ warning: Stack is empty! ]\n");
    return NULL;
}

bool FORMULAR_CHECK(char input[][MAX], int size){
    if(! CHECK_PRTHSES(input,size)) return false;
    if(! CHECK_OPERA(input, size)) return false;
    if(! CHECK_SEQ(input, size)) return false;
    return true;
}

void FORMULAR_GET(char input[][MAX], int *size){
    char take[MAX]={'\0'};
    int i=0; 
    printf("請輸入運算式: ");
    scanf("%[^\n]", take); getchar();
    char *tmp=strtok(take," ");
    while(tmp){
	   strcpy(input[i],tmp);
	   i++;
	   tmp=strtok(NULL," ");
    }
    size[0]=i;
}
void LINK_PRINT(Stack *s){
    if(! s->next) return ;
    s=s->next;
    while(s){ printf("%c,", s->val); s=s->next; }
    printf("\n");
}

