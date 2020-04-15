#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "check.h"
#include "stack.h"
//  DEFINE
#define MAX 100

//  FUNCTION_ANNOUNCEMENT
void FORMULAR_GET(char input[][MAX], int *size);
bool FORMULAR_CHECK(char input[][MAX], int size);

void FORMULAR_IN_TO_POST_FIX(char input[][MAX], int size, char *ret);
double FORMULAR_CALCULATE(char *formula, int *list, int listSize);

double STR_TO_INT(char *str,int *site);

void INPUT_DATA(int *list, int *size, char *templet);
//  MAIN
int main(void){
    char input[MAX][MAX], take[MAX]; memset(take,'\0', MAX);
    int size=0; //how many element in formula
    //  CONPUTION
    printf("************************************\n");
    printf("*          中序式轉後序式          *\n");
    printf("************************************\n\n");
    int flag=1;
    while(flag){
        //  initialize
        for(int i=0;i<size;i++) memset(input[i],'\0', MAX);
        memset(take,'\0', MAX);
        size=0;
        // get input
        FORMULAR_GET(input, &size);
        // check formular
        if( ! FORMULAR_CHECK(input, size)) break;

        printf("\n==== #INFIX_TO_POSTFIX# ====\n中序轉後序堆疊: \n");
        FORMULAR_IN_TO_POST_FIX(input, size, take);
        printf("* 轉換結果: ");
        puts(take);
        printf("-------------------------------\n");
        int list[MAX]={0}, listSize=0;
        // input data
        INPUT_DATA(list, &listSize, take);
        // calculate postfix 
    
        printf("\n==== @POSTFIX_EVALUATION@ ====\n計算堆疊: \n");
        printf("* 計算結果: %.2lf\n", FORMULAR_CALCULATE(take, list, listSize));
        printf("-------------------------------\n\n"); 
    
        //
        printf("繼續按1, 結束按0: ");
        scanf("%d", &flag); getchar();
        if(flag) printf("\n=================================\n\n");    
    } 
    //  END
    return 0;
}

//  FUNCTION
double FORMULAR_CALCULATE(char *formula, int *list, int listSize){
    NUM_Stack *s=(NUM_Stack*)malloc(sizeof(NUM_Stack));
    s->next=NULL;
    double ret=0;
    int i=0, j=0;
    while(formula[i]!='\0'){
        if(formula[i]=='+'||formula[i]=='-'||formula[i]=='*'||formula[i]=='/'||formula[i]=='%'){
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
        if(formula[i]>='A'&&formula[i]<='Z'){
            double tmp=list[j]; j++;
            /*
            else if(formula[i]>='0'&&formula[i]<='9'){
                double num=STR_TO_INT(&formula[i], &i);
            */
            NUM_Stack_PUSH(s,tmp);           
        }
        NUM_LINK_PRINT(s);
        i++;
    }
    ret = s->next->val;
    return ret;
}


void INPUT_DATA(int *list, int *size, char *templet){
    int i=0, k=0;
    while(templet[i]){
        if(templet[i]>='A'&&templet[i]<='Z'){
            printf("輸入變數%c : ", templet[i]);
            scanf("%d", &list[k]);
            k++;
        }
        i++;
    }
    size[0]=k;
}
bool FORMULAR_CHECK(char input[][MAX], int size){
    if(! CHECK_PRTHSES(input,size)) return false;
    if(! CHECK_OPERA(input, size)) return false;
    if(! CHECK_SEQ(input, size)) return false;
    return true;
}

void FORMULAR_IN_TO_POST_FIX(char input[][MAX], int size, char *ret){
    Stack *s=(Stack*)malloc(sizeof(Stack));
    s->next=NULL;
    int k=0;
    for(int i=0;i<size;i++){

        if(input[i][0]>='A'&&input[i][0]<='Z'){
            int j=0;
            ret[k]=input[i][0];
            //while(input[i][j]) { ret[k]=input[i][j]; j++; k++; }
            //ret[k]=' '; 
            k++;
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
        else if(input[i][0]=='+'||input[i][0]=='-'){
            if(s->next==NULL) STACK_PUSH(s, input[i][0]);
            else if(s->next&&(s->next->val=='('||s->next->val=='['||s->next->val=='{')){
                STACK_PUSH(s, input[i][0]); 
            }
            else{
                char tmp=STACK_POP(s);  
                if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; }
                while(s->next&&(s->next->val=='+'||s->next->val=='-'||s->next->val=='*'||s->next->val=='/')&&(s->next->val!='('||s->next->val!='['||s->next->val!='{')) 
                    { tmp=STACK_POP(s); ret[k]=tmp; k++;  }
                STACK_PUSH(s, input[i][0]); 
            }
        }
        else if(input[i][0]=='*'||input[i][0]=='/'){
            if(s->next==NULL) STACK_PUSH(s, input[i][0]);
            else if(s->next&&(s->next->val=='('||s->next->val=='['||s->next->val=='{'||s->next->val=='+'||s->next->val=='-')){
                STACK_PUSH(s, input[i][0]); 
            }
            else{
                char tmp=STACK_POP(s);
                if(tmp=='*'||tmp=='/') { ret[k]=tmp; k++; }
                while(s->next&&(s->next->val=='*'||s->next->val=='/')) 
                    { tmp=STACK_POP(s); ret[k]=tmp; k++; } 
                STACK_PUSH(s, input[i][0]);            
            }           
        }
        LINK_PRINT(s);
    }
    while(s->next) { 
        char tmp=STACK_POP(s);
        if(tmp=='+'||tmp=='-'||tmp=='*'||tmp=='/') { ret[k]=tmp; k++; } 
    }
}

void FORMULAR_GET(char input[][MAX], int *size){
    FILE *fptr=fopen("./test.cpp","r");
    char take[MAX]={'\0'};
    int i=0; 
    fgets(take,MAX,fptr);
    puts(take);
    int k=0;
    for(i=0;i<strlen(take);i++){
        input[k][0]=take[i];
        input[k][1]='\0';
        k++;
    }
    size[0]=k;

    fclose(fptr);
}

double STR_TO_INT(char *str, int *site){
    double ret=0;
    int i=0, ten=1;
    if(str[i+1]<'0'||str[i+1]>'9') return str[0]-'0'; 
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

