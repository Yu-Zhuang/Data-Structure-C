#include<stdio.h>
#include<stdlib.h>
int main(void){
	float a=5.3, b=8.1;
	printf("a:%f, b:%f\n", a, b);
	a=b+(b=a)-a;
	printf("a:%f, b:%f\n", a, b);
	return 0;
}