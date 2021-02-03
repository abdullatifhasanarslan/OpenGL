#include <stdio.h>


int factorial(int i){
	int result=1;
	while(i>1){
		result=result*i;
		i--;
	}
	return result;
}


int main(){
	int i;
	int temp;
	int array[5];
	i=0;
	while(i<5){
		temp=factorial(i);
		array[i]=temp;
		i++;
	}
	return 0;
}
