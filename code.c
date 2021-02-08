#include <stdio.h>
int k ;

int factorial ( int i )
{
	int result = 1 ;
	while ( i > 1 )
	{
		result = result * i ;
		i -- ;
	}
	return result ;
}


int main ( )
{
	int i ;  
	int temp ;   
	int array [ 10 ] ;  
	i = 0 ;
	while ( i < 10 )
	{
		array [ i ] = temp ;
		temp = factorial ( i ) ;
		if ( i % 2 )
		{
			i ++ ;
		}
		else if ( i > 5 )
		{
			i = 0 ;
		}
		else
		{
			i *= 2 ;
		}
		i ++ ;
	}
	
	return 0;
}
