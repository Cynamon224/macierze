#ifndef MATRIX_H
#define MATRIX_H
void PrintMatrix ( double** pTab, int nSize );
int CreateMatrix ( double*** pTab, int nSize );
void TransMatrix ( double** pTab, int nDim );
double Det ( double** pTab, int nSize );
void LayoutEqu ( double** pInv, double* pB, double* pRes, int nSize );
void DeleteMatrix ( double*** pTab, int nSize );
void InverseMatrix ( double** pInv, double** pTab, int nSize, double det );
#endif