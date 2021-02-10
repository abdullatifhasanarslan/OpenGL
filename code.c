#include <stdio.h>
int k ;

int average ( int a , int b , int c )
{
	float result ;
	result = a + b ;
	result = result + c ;
	result = result / 3 ;
	return result ;
}


int factorial ( int i )
{
	int result = 1 ;
	while ( i > 1 )
	{
		result *= i ;
		i -- ;
	}
	return result ;
}


int absolute_difference ( int a , int b )
{
	int result ;
	if ( a > b )
	{
		result = a - b ;
	} 
	else
	{
		result = b - a ;
	}
	return result ;
}

int average ( int a , int b , int c )
{
	int result ;
	result = a + b ;
	result = result + c ;
	result = result / 3 ;
	return result ;
}

int array_test ( )
{
	char array [ 5 ] ;
	array [ 0 ] = 'a' ;
	array [ 1 ] = 'b' ;
	array [ 2 ] = 'c' ;
	array [ 3 ] = 'd' ;
	array [ 4 ] = 'e' ;
}

int main ( )
{
	int array [ 3 ] ;  
	int temp ;
	
	temp = factorial ( 10 ) ;
	array [ 0 ] = temp ;
	
	temp = absolute_difference ( 10 , 20 ) ;
	array [ 1 ] = temp ;
	
	temp = average ( 10 , 20 , 30 ) ;
	array [ 2 ] = temp ;	
	
	array_test ( ) ;

	return 0 ;
}
