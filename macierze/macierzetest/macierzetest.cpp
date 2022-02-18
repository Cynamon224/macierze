#include <malloc.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "matrix.h"
#include "wektor.h"
#include <math.h>
#define _DEBUG_

void ReadData ( FILE* fin, double** pMatrix, double* b, int nDim );

int main ( int argc, char* argv [] )
{
	if ( argc != 2 )
	{
		printf ( "Usage:%s <plik_we>", argv [0] );

		return  1;
	}

	FILE* fin = NULL;
	if ( ( fin = fopen ( argv [1], "r" ) ) == NULL ) {
		printf ( "error open file %s", argv [1] );
		return 2;
	}
	int nSize;
	fscanf ( fin, "%d", &nSize );


	double** pMatrix = NULL;
	double* b = NULL;

	if ( !CreateMatrix ( &pMatrix, nSize ) || ( !CreateW ( &b, nSize ) ) ) {
		printf ( "nie udalo sie stworzyc macierzy lub wektora\n" );
		return 3;
	}

	ReadData ( fin, pMatrix, b, nSize );
	fclose ( fin );

#ifdef _DEBUG_
	printf ( "Rozmiar macierzy:" );
	printf ( "%d", nSize );
	printf ( "\n\n" );
	printf ( "Macierz z pliku:\n" );
	PrintMatrix ( pMatrix, nSize );
	printf ( "\n " );
	printf ( "Wektor:\n" );
	PrintW ( b, nSize );
	printf ( "\n\n" );
#endif

	int det = Det ( pMatrix, nSize );
	//TransMatrix(pMatrix, nSize);
	if ( fabs ( det ) < 1.e-16 ) {
		printf ( "Error: wyznacznik=0 macierz osobliwa\n" );
		return 4;
	}


#ifdef _DEBUG_
	printf ( "Macierz z pliku po obliczeniu wyznacznika:\n" );
	PrintMatrix ( pMatrix, nSize );
	printf ( "\n\n" );
#endif

	double** pMatrix2 = NULL;
	CreateMatrix ( &pMatrix2, nSize );
	if ( !CreateMatrix ( &pMatrix2, nSize ) ) {
		printf ( "nie udalo sie stworzyc macierzy\n" );
		return 5;
	}
	InverseMatrix ( pMatrix2, pMatrix, nSize, det );

#ifdef _DEBUG_
	printf ( "Macierz z odwrotna:\n" );
	PrintMatrix ( pMatrix2, nSize );
	printf ( "\n\n" );
#endif

	double* w = NULL;
	if ( !CreateW ( &w, nSize ) ) {
		printf ( "nie udalo sie stworzyc wektora na rozwiazania\n" );
		return 6;
	}

	LayoutEqu ( pMatrix2, b, w, nSize );
	printf ( "Rozwiazanie ukladu rownan:\n" );
	PrintW ( w, nSize );

	DeleteMatrix ( &pMatrix, nSize );

	DeleteMatrix ( &pMatrix2, nSize );

	DeleteVector ( &b, nSize );
	DeleteVector (  &w, nSize );

	return 0;
}


void ReadData ( FILE* fin, double** pMatrix, double* b, int nDim ) {


	for ( int i = 0; i < nDim; i++ )
	{

		double* ptr = *pMatrix++;

		for ( int j = 0; j < nDim; j++ )
		{
			fscanf ( fin, "%lf", ptr++ );
		}
		fscanf ( fin, "%lf", b++ );

	}

}
