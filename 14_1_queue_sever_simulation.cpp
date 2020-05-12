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
	char id[MAX];
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
void CONDITION_SET(int* run, int *newMessageNum, int *processorRate, float *failedRate);
void CONDITION_PRINT(int run, int *newMessageNum, int *processorRate, float failedRate);

void DRIVER(int run, int*newMessageNum, int*processorRate, float failedRate);
void NEW_MESSAGE(Q_HEAD *q_head, int *newMessageNum);
void PROCESSOR(Q_HEAD *q, int *processorRate, int *totalQueue,int *totalArrived,\
				int *firstTimes,int *secondTimes, int *totalMessageSent, int *n,\
				float failedRate, int *qMAX);
void SEVER_FREE(Q_HEAD *q, int n);
void STATICS(int totalArrived, int totalMessageSent, int totalRunTime,\
			 int totalQueue, int firstTimes, int secondTimes, int qMAX);

void EN_QUEUE(Q_HEAD *q, MESSAGES *element);
MESSAGES* DE_QUEUE(Q_HEAD *q);

// ===== MAIN =====
int main(void){
	srand(time(NULL));
	int chose = 1,\
		run = 100,\
		newMessageNum[2] = {0,60},\
		processorRate[2] = {20,60};
	float failedRate = 0.3;

	while(chose){
		CONDITION_SET( &run, newMessageNum, processorRate, &failedRate);
		DRIVER(run, newMessageNum, processorRate, failedRate);	
		CONDITION_PRINT( run, newMessageNum, processorRate, failedRate);	
		printf("繼續按1, 結束按0: "); scanf("%d", &chose); fflush(stdin);
	}
	printf("\t [ 程式結束 ]\n");
	return 0;
}

// ===== FUNCTION =====
void DRIVER(int run, int*newMessageNum, int*processorRate, float failedRate){
	int totalArrived = 0,\
		totalMessageSent = 0,\
		totalRunTime = 0,\
		totalQueue = 0,\
		firstTimes = 0,\
		secondTimes = 0,\
		n = 0,\
		qMAX = 0;
	// create queue
	Q_HEAD *q_head = (Q_HEAD*)malloc(sizeof(Q_HEAD));
	q_head->count = 0; q_head->next = NULL; q_head->rear = NULL;
	// loop (timeNotEnd or queueNotEmpty) // 1 run == 1 minutes
	for(int i=0; i<run OR q_head->next ; i++){
		printf("\n\t  ---------- | Iteration %d | ----------\n", i+1);
		if(i<run)
			NEW_MESSAGE(q_head, newMessageNum);
		PROCESSOR(q_head, processorRate, &totalQueue, &totalArrived, &firstTimes,\
					&secondTimes, &totalMessageSent, &n, failedRate, &qMAX);
		SEVER_FREE(q_head, n);
		totalRunTime += 1;
	}
	// printStatics
	STATICS(totalArrived, totalMessageSent, totalRunTime,\
			totalQueue, firstTimes, secondTimes, qMAX);
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
	printf("# NEW_MESSAGE()-> Number of messages that arrive: %d\n", n);
}

void PROCESSOR(Q_HEAD *q, int *processorRate, int *totalQueue,int *totalArrived,\
				int *firstTimes,int *secondTimes, int *totalMessageSent, int *n,\
				float failedRate, int *qMAX){
	// record max size of queue
	if(q->count > qMAX[0]) qMAX[0] = q->count;
	// qTotalCount += queueCount
	totalQueue[0] += q->count;
	// n = rand(start,end) // 產生處理信件數
	n[0] = rand()%(processorRate[1]-processorRate[0]+1) + processorRate[0];
	// if(n > queueCount) : n = queueCount
	if(n[0] > q->count) n[0] = q->count;
	// loop(n) // 一封一封寄
	NODE *qTmp = q->next;
	printf("# PROCESSOR()->  (Current Queue size: %d )\n\t[n]======[ ID ]==============[ status | susTimes ]\n", q->count);
	for(int i=0; i<n[0] AND qTmp ; i++){
		// suscessful rate 
		qTmp->val->status = ( (rand()%10)>(failedRate*10-1) ) ? 1 : 0;
		qTmp->val->susTimes += 1;
		// print the ID of the run
		printf("\t%d.\t %s \t %d\t %d\n", i+1, qTmp->val->id, qTmp->val->status, qTmp->val->susTimes);
		// if(send suscessful) :
		if(qTmp->val->status){
			// totalArrived += 1;
			totalArrived[0] += 1;
			// 1stTimes++, 2ndTimes calculate;
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
	printf("# SEVER_FREE()-> Number of messages that are sent successfully : %d\n", sentNum);
}

void STATICS(int totalArrived, int totalMessageSent, int totalRunTime,\
			 int totalQueue, int firstTimes, int secondTimes, int qMAX){
	printf("\n\t===================================================\n");
	printf("\t=                    [ 結果統計 ]                 =\n");
	printf("\t===================================================\n");
	printf(" \t* Total messages that arrived : %d\n", totalArrived);
	printf(" \t* Total messages sent : %d\n", totalMessageSent);
	printf(" \t* Average number of successfully sent/minute: %.2lf\n",\
			(double)totalArrived/totalRunTime);
	printf(" \t* Average number messages in the queue: %.2lf\n",\
	 		(double)totalQueue/totalRunTime);
	printf(" \t* Number of messages sent on the 1st attempt: %d\n", firstTimes);
	printf(" \t* Number of messages sent on the 2nd attempt: %d\n", secondTimes);
	printf(" \t* Average number of attempts to send a message successfully: %.2lf\n",\
			(double)totalMessageSent/totalArrived);
	printf(" \t* Total run: %d\n", totalRunTime);
	printf(" \t* Max size of Queue: %d\n", qMAX);
}

void EN_QUEUE(Q_HEAD *q, MESSAGES *element){
	if(!q OR !element) { printf("\t[ warning: 101 ]\n"); return ; }
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
	if(!q OR !q->next) { printf("\t[ warning: 102 ]\n"); return NULL; }
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

void CONDITION_SET(int* run, int*newMessageNum, int*processorRate, float *failedRate){
	char chose='1';
	printf("\n\t@郵件寄送系統模擬@\n");
	printf("是否要使用預設值(1:是, 任意鍵:否): "); scanf("%c", &chose); fflush(stdin);
	if(chose IS '1'){
		run[0] = 100;
		newMessageNum[0] = 0; newMessageNum[1] = 60;
		processorRate[0] = 20; processorRate[1] = 60;
		failedRate[0] = 0.3;
		return;
	}
	printf("\t#請依序輸入模擬條件#\n");
	printf("Iteration times: "); scanf("%d", run);
	printf("Range of newMessageNum(start end): "); scanf("%d %d", &newMessageNum[0], &newMessageNum[1]);
	printf("Range of processorRate(start end: "); scanf("%d %d", &processorRate[0], &processorRate[1]);
	printf("Failed Rate(0~1.0): "); scanf("%f", failedRate);
}
void CONDITION_PRINT(int run, int *newMessageNum, int *processorRate, float failedRate){
	printf("\t---\n\tPS. Condition of this test:\n");
	printf("\t \trun set: %d\n", run);
	printf("\t \tnewMessageNum: %d ~ %d\n", newMessageNum[0], newMessageNum[1]);
	printf("\t \tprocessorRate: %d ~ %d\n", processorRate[0], processorRate[1]);
	printf("\t \tfailedRate: %d %%\n\n", (int)(failedRate*100));
}