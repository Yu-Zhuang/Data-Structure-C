// ===== HEADER =====
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>

// ===== DEFINE =====
# define IS ==
# define IS_NOT !=
# define AND &&
# define OR ||
# define MAX 20

typedef struct m{
	char id[20];
	int status;
	int susTimes;
}MESSAGES;
typedef struct q{
	MESSAGES *val;
	struct q *next;
}NODE;
typedef struct qh{
	int count;
	NODE *next;
	NODE *rear;
}Q_HEAD;

// ===== FUNCTION_ANNOUNCEMENT =====
void DRIVER(int run, int*newMessageNum, int*processorRate, float susccessRate);

void NEW_MESSAGE(Q_HEAD *q_head, int *newMessageNum);
void PROCESSOR(Q_HEAD *q, int *processorRate, int *totalQueue,int *totalArrived,\
				int *firstTimes,int *secondTimes, int *totalMessageSent, int *n);
void SEVER_FREE(Q_HEAD *q, int n);

void STATICS(int totalArrived, int totalMessageSent, int totalRunTime,\
			 int totalQueue, int firstTimes, int secondTimes);

void EN_QUEUE(Q_HEAD *q, MESSAGES *element);
MESSAGES* DE_QUEUE(Q_HEAD *q);

// ===== MAIN =====
int main(void){
	srand(time(NULL));
	int run = 100,\
		newMessageNum[2] = {0,60},\
		processorRate[2] = {20,60};
	float susccessRate = 0.3;
	DRIVER(run, newMessageNum, processorRate, susccessRate);
	return 0;
}

// ===== FUNCTION =====
void DRIVER(int run, int*newMessageNum, int*processorRate, float susccessRate){
	int totalArrived = 0,\
		totalMessageSent = 0,\
		totalRunTime = 0,\
		totalQueue = 0,\
		firstTimes = 0,\
		secondTimes = 0,\
		n = 0;
	// create queue
	Q_HEAD *q_head = (Q_HEAD*)malloc(sizeof(Q_HEAD));
	q_head->count = 0; q_head->next = NULL; q_head->rear = NULL;
	// loop (timeNotEnd or queueNotEmpty) // 1 run == 1 minutes
	for(int i=0; i<run OR q_head->next ; i++){
		if(i<run)
			NEW_MESSAGE(q_head, newMessageNum);
		PROCESSOR(q_head, processorRate, &totalQueue, &totalArrived, &firstTimes,\
					&secondTimes, &totalMessageSent, &n);
		SEVER_FREE(q_head, n);
		totalRunTime += 1;
	}
	// printStatics
	STATICS(totalArrived, totalMessageSent, totalRunTime,\
			totalQueue, firstTimes, secondTimes);
}

void PROCESSOR(Q_HEAD *q, int *processorRate, int *totalQueue,int *totalArrived,\
				int *firstTimes,int *secondTimes, int *totalMessageSent, int *n){
	// qTotalCount += queueCount
	totalQueue[0] += q->count;
	// n = rand(20,60) // 產生處理信件數
	n[0] = rand()%(processorRate[1]-processorRate[0]+1) + processorRate[0];
	// if(n > queueCount) : n = queueCount
	if(n[0] > q->count)
		n[0] = q->count;
	// loop(n) // 一封一封寄
	NODE *qTmp = q->next;
	printf("\n[n]======[ ID ]==============[status | susTimes]\n");
	for(int i=0; i<n[0] AND qTmp ; i++){
		// suscessful rate = 70%
		qTmp->val->status = ( (rand()%10)>2 ) ? 1 : 0;
		printf("hello world\n");
		qTmp->val->susTimes += 1;
		// print the ID of the run
		printf("%d.\t %s \t %d\t %d\n", i+1, qTmp->val->id, qTmp->val->status, qTmp->val->susTimes);
		// if(send) :
		if(qTmp->val->status){
			// totalArrived += 1;
			totalArrived[0] += 1;
			// if(susTimes==1) 1stTimes++; if(susTimes==2) 2ndTimes++;
			switch(qTmp->val->susTimes){
				case 1: firstTimes[0]++; break;
				case 2: secondTimes[0]++; break;
				default: break;
			}
		}
		totalMessageSent[0] += 1;
		qTmp = qTmp->next;
	}
}

void SEVER_FREE(Q_HEAD *q, int n){
	NODE *qTmp = q->next;
	int sentNum = 0;
	// loop(n)
	for(int i=0;i<n;i++){
		// if(send): dequeue;
		if(qTmp->val->status)
			{ DE_QUEUE(q); sentNum += 1; }
		// if(unsend): tmp = dequeue; enqueue(tmp);
		else
			EN_QUEUE(q, DE_QUEUE(q));
		qTmp = qTmp->next;
	}
	// print the number of messages that are sent
	printf("[ Number of messages that are sent successfully ]: %d\n", sentNum);
}
void NEW_MESSAGE(Q_HEAD *q_head, int *newMessageNum){
	char id_templet[]="123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int it_len = strlen(id_templet);
	// n = rand(0,60)
	int n = rand()%(newMessageNum[1]-newMessageNum[0]+1) + newMessageNum[0];
	// create n*newMessage
	for(int i=0;i<n;i++){
		MESSAGES *newMessage = (MESSAGES*)malloc(sizeof(MESSAGES));
		// initialize newMessage
		for(int i=0;i<14;i++)
			newMessage->id[i] = id_templet[rand()%it_len]; 
		newMessage->status = 0; 
		newMessage->susTimes = 0;
		// enqueue newMessage
		EN_QUEUE(q_head, newMessage);
	}
	// print the number of messages that arrive
	printf("\n[ Number of messages that arrive ]: %d\n", n);
}

void STATICS(int totalArrived, int totalMessageSent, int totalRunTime,\
			 int totalQueue, int firstTimes, int secondTimes){
	printf("\n\t===================================================\n");
	printf("\t=                    [ 結果統計 ]                 =\n");
	printf("\t===================================================\n");
	// Total messages that arrived : totalArrived
	printf(" \t* Total messages that arrived : %d\n", totalArrived);
	// Total messages sent : totalMessageSent
	printf(" \t* Total messages sent : %d\n", totalMessageSent);
	// average number of messages successfully sent per minute: totalArrived/T
	printf(" \t* Average number of successfully sent/minute: %.2lf\n",\
			(double)totalArrived/totalRunTime);
	// average number messages in the queue:  qTotalCount/T
	printf(" \t* Average number messages in the queue: %.2lf\n",\
	 		(double)totalQueue/totalRunTime);
	// number of messages sent on the 1st attempt: 1stTimes
	printf(" \t* Number of messages sent on the 1st attempt: %d\n", firstTimes);
	// number of messages sent on the 2nd attempt: 2ndTimes
	printf(" \t* Number of messages sent on the 2nd attempt: %d\n", secondTimes);
	// average number of attempts to send a message successfully: 
											// totalMessageSent/totalArrived
	printf(" \t* Average number of attempts to send a message successfully: %.2lf\n", (double)totalMessageSent/totalArrived);
	printf(" \t* Total run: %d\n", totalRunTime);
}

void EN_QUEUE(Q_HEAD *q, MESSAGES *element){
	if(!q)
		{ printf("\t[ warning: 101 ]\n"); return ; }
	NODE *newnode = (NODE*)malloc(sizeof(NODE));
	newnode->val = element;
	if(q->next){ 
		newnode->next = q->rear->next; 
		q->rear->next = newnode; 
	}
	else{ 
		newnode->next = q->next; 
		q->next = newnode; 
	}
	q->rear = newnode;
	q->count += 1;
}
MESSAGES* DE_QUEUE(Q_HEAD *q){
	NODE *tmp = q->next;
	MESSAGES *ret = tmp->val;
	q->next = q->next->next;
	q->count -= 1;
	if(tmp->val->status){
		free(ret);
		free(tmp);
		return NULL;
	}
	return ret;
}