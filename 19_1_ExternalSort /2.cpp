# include <stdio.h>
# include <stdlib.h>
# include <time.h>


int main(void){
	double START = 0, END = 0;
	START = clock();
	for(int i=0;i<100;i++){
		i += 1;
		i -= 1;
	}
	END = clock();
	printf("time: %lf\n", END-START);
	return 0;
}