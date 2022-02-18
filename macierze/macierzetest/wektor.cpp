#include<stdlib.h>
#include "wektor.h"
#include <malloc.h>
#include <iostream>
#include <stdio.h>

void DeleteVector ( double** pTab, int nSize )
{
	free ( *pTab );
	*pTab = NULL;

}
int CreateW ( double** pTab, int nSize )

{
	*pTab = ( double* ) malloc ( sizeof ( double* ) * nSize );
	if ( !pTab )
		return 0;

	memset ( *pTab, 0, sizeof ( double* ) * nSize );

	return 1;
}
void PrintW ( double* tTab, int nSize ) {
	for ( int i = 0; i < nSize; i++ ) {
		printf ( "x" );
		printf ( "%d", i + 1 );
		printf ( "=" );
		printf ( "%lf", *tTab++ );
		printf ( "\n" );
	}

}