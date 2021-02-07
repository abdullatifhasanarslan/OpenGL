

int k;

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
		if(i%2)
		{
			i++;
		}
		else if(i>5)
		{
			i=0;
		}
		else
		{
			i*=2;
		}
		array[i]=temp;
		i++;
	}
	return 0;
}
