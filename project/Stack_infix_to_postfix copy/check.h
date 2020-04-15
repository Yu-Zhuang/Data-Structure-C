
#define MAX 100

typedef struct s{
    char val;
    struct s *next;
}S;
    //check
bool CHECK_PRTHSES(char input[][MAX], int size);
bool CHECK_OPERA(char input[][MAX], int size);
bool CHECK_SEQ(char input[][MAX], int size);
    //stack
void CHECK_STACK_PUSH(S *s, char element);
int CHECK_STACK_POP(S *s, char target);

bool CHECK_SEQ(char input[][MAX], int size){
    if(input[0][0]=='+'||input[0][0]=='-'||input[0][0]=='*'||input[0][0]=='/'){
        printf("\t[ error 006: Inappropriate sequence! ]\n");
        return false;
    }
    int i=0;
    while(i!=size){
        if((input[i][0]=='('||input[i][0]=='['||input[i][0]=='{')&& i+1!=size){
            if(input[i+1][0]=='+'||input[i+1][0]=='-' || input[i+1][0]=='*' || input[i+1][0]=='/'){
                printf("\t[ error 006: Inappropriate sequence! ]\n");
                return false;
            }
        }
        else if((input[i][0]==')'||input[i][0]==']'||input[i][0]=='}')&& i!=0){
            if(input[i-1][0]=='+'||input[i-1][0]=='-' || input[i-1][0]=='*' || input[i-1][0]=='/'){
                printf("\t[ error 006: Inappropriate sequence! ]\n");
                return false;
            }
        }
        i++;
    }
    return true;
}

bool CHECK_OPERA(char input[][MAX], int size){
    int i=0, flag=0;

    while(i!=size){
        if(((input[i][0]>='A'&&input[i][0]<='Z')||(input[i][0]>='a'&&input[i][0]<='z'))&& flag==0){
            flag=1;
        }
        else if( (input[i][0]=='+'||input[i][0]=='-' || input[i][0]=='*' || input[i][0]=='/') && flag==1){
            flag=0;
        }else{
            if(input[i][0]>='A'&&input[i][0]<='Z'){
                printf("\t[ error 004: Operands without operators! ]\n");
                return false;
            }
            else if(input[i][0]=='+'||input[i][0]=='-' || input[i][0]=='*' || input[i][0]=='/'){
                printf("\t[ error 005: Operators without operands! ]\n");
                return false;
            }
        }
        i++;
    }
    if(flag==0){
            printf("\t[ error 005: Operators without operands! ]\n");
            return false;
    }
    return true;
}

bool CHECK_PRTHSES(char input[][MAX], int size){
    S *head=(S*)malloc(sizeof(S));
    head->next=NULL;
    int i=0;
    while(i!=size){
        if(input[i][0]=='('||input[i][0]=='['||input[i][0]=='{'){
            CHECK_STACK_PUSH(head,input[i][0]);
        }
        else if(input[i][0]==')'||input[i][0]==']'||input[i][0]=='}'){
            char tmp;
            switch(input[i][0]){
                case ')': tmp='('; break;
                case ']': tmp='['; break;
                case '}': tmp='{'; break;
                default: break;
            }
           if( CHECK_STACK_POP(head,tmp)==0) return false;
        }
        i++;
    }
    if(head->next==NULL) return true;
    else{
        printf("\t[ error 002: Missing closing parentheses! ]\n");
        return false;
    }
}

void CHECK_STACK_PUSH(S *s, char element){
    S *newnode=(S*)malloc(sizeof(S));
    newnode->val=element;
    newnode->next=s->next;
    s->next=newnode;
}

int CHECK_STACK_POP(S *s, char target){
    if(s->next){
    	if( s->next->val==target){
    	    S *ptr=s->next;
    	    s->next=s->next->next;
    	    free(ptr);
    	    return 1;
    	}
        printf("\t[ error 001: Mismatch between parentheses! ]\n");
        return 0;
    }
    printf("\t[ error 003: Missing opening parentheses! ]\n");
    return 0;
}
