
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

void STACK_PUSH(Stack *s, char element);
char STACK_POP(Stack *s);
void NUM_Stack_PUSH(NUM_Stack *s, double element);
double NUM_Stack_POP(NUM_Stack *s);
void LINK_PRINT(Stack *s);
void NUM_LINK_PRINT(NUM_Stack *s);

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
    printf("\t[ warning: NUM_Stack is empty! ]\n");
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

void LINK_PRINT(Stack *s){
    if(! s->next) return ;
    s=s->next;
    printf("\t \tTOP-| ");
    while(s){ printf("%c, ", s->val); s=s->next; }
    printf("\n");
}

void NUM_LINK_PRINT(NUM_Stack *s){
    if(! s->next) return ;
    s=s->next;
    printf("\t \tTOP-| ");
    while(s){ printf("%.2lf, ", s->val); s=s->next; }
    printf("\n");    
}

