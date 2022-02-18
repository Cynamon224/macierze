#include <iostream>
#include <algorithm>
#include <malloc.h>
#include <stdio.h>
#include<stdlib.h>
#include "matrix.h"
void Complement ( double** pTabO, double** pTabI, int nRow, int nCol, int nDim );
void ComplMatrix ( double** pTabD, double** pMatrix, int nDim ); //macierz dopelnien


int CreateMatrix ( double*** pTab, int nSize )

{
	*pTab = ( double** ) malloc ( sizeof ( double* ) * nSize );

	if ( !pTab )
		return 0;

	memset ( *pTab, 0, sizeof ( double* ) * nSize );

	double** p = *pTab;  // pomocniczy wska nik do alokacji
	for ( int i = 0; i < nSize; i++ )
	{
		*p = ( double* ) malloc ( sizeof ( double ) * nSize );
		if ( !*pTab ) return 0;

		memset ( *p++, 0, sizeof ( double ) * nSize );

	}
	return 1;
}
void PrintMatrix ( double** tTab, int nSize ) {


	for ( int i = 0; i < nSize; i++ ) {
		double* p = *tTab++;
		for ( int j = 0; j < nSize; j++ ) {
			printf ( "%lf ", *p++ );

		}
		printf ( "\n" );


	}

}
void DeleteMatrix ( double*** pTab, int nSize )// *pTab==NULL
{
	double** ptr = *pTab;
	for ( int i = 0; i < nSize; i++ ) {
		free ( *ptr++ );
	}
	free ( *pTab );
	*pTab = NULL;

}
void TransMatrix ( double** pTab, int nDim )
{
	double** tTab = pTab;
	for ( int i = 0; i < nDim - 1; i++ ) {

		double* temp2 = *tTab++ + i +1;
		
		for ( int j = i + 1; j < nDim; j++ ) {

			double temp = pTab [j][i];
			pTab [j][i] = *temp2;
			*temp2++ = temp;

		}
	}

}


double Det ( double** pTab, int nSize )
{

	if ( nSize == 1 ) {
		return **pTab;
	}
	if ( nSize == 2 ) {

		return **pTab * pTab [1][1] - pTab [0][1] * pTab [1][0];
	}

	double** tTab = NULL;
	
	if ( !CreateMatrix ( &tTab, nSize - 1 ) ) {
		printf ( "nie udalo sie stworzyc macierzyDET\n" );
		return 7;
	}
	double det = 0;
	double* temp2 = *pTab;
	int sgn = 1;
	for ( int i = 0; i < nSize; i++ ) {

		Complement ( tTab, pTab, 0, i, nSize );

		det += sgn * Det ( tTab, nSize - 1 ) * *temp2++;
		sgn = -sgn;

	}
	DeleteMatrix ( &tTab, nSize - 1 );
	return det;
}


void Complement ( double** OUT, double** INPUT, int nRow, int nCol, int nDim ) {

	for ( int i = 0; i < nDim; i++ ) {

		double* Icol = *INPUT++;
		if ( i == nRow ) continue;

		double* Ocol = *OUT++;

		for ( int j = 0; j < nDim; j++, Icol++ ) {

			if ( j == nCol )continue;

			*Ocol++ = *Icol;//nowa macierz z pominieciem nrow i ncol

		}

	}

}

void LayoutEqu ( double** pInv, double* pB, double* pRes, int nSize ) {

	for ( int i = 0; i < nSize; i++ ) {
		double* Col = *pInv++;
		double* tB = pB;
		for ( int j = 0; j < nSize; j++ ) {

			*pRes += *Col++ * *tB++;
		}
		pRes++;
	}

}
void ComplMatrix ( double** pTabD, double** pMatrix, int nDim ) //macierz dopelnien
{

	double** tTab = NULL;
	if ( !CreateMatrix ( &tTab, nDim ) ) {
		perror ( "nie udalo sie stworzyc macierzy w complmatrix\n" );
		return;
	}
	
	for ( int i = 0; i < nDim; i++ ) {
		double* colD = *pTabD++;

		int sgn = ( i % 2 ? -1 : 1 );
		for ( int j = 0; j < nDim; j++, colD++ ) {
			
			Complement ( tTab, pMatrix, i, j, nDim );
			sgn = -sgn;
			*colD += sgn * ( Det ( tTab, nDim - 1 ) );
			
		}
		
	}
	DeleteMatrix ( &tTab, nDim );

}
void InverseMatrix ( double** pInv, double** pTab, int nSize, double det ) {

	ComplMatrix ( pInv, pTab, nSize );
	TransMatrix ( pInv, nSize );

	for ( int i = 0; i < nSize; i++ ) {
		double* temp2 = *pInv++;

		for ( int j = 0; j < nSize; j++ ) {
			*temp2++ /= det;
		}
	}
}
