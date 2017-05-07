#include<stdio.h>

int main(){
	int test[10];
	int i=0;
	test[5]=99;

	for(i=0;i<10;i++)if(test[i]==99) break;
	printf("%d\n",i);
}
