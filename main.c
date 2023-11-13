#include <stdio.h>
#include <stdlib.h>
//Ömer Faruk Ýlhan - 21118080023

void readInput(int n,int *firstMatrix,int *secondMatrix,FILE *inputFile){
    //These two for loops are getting inputs from input.txt file
    for(int i =0; i <(n*(n+1)/2); i++){
        fscanf(inputFile,"%d",&firstMatrix[i]);//Assign first line inputs(inside of the input.txt file) to the firstMatrix[i]'s address
    }
    for(int i = 0; i < (n*(n+1)/2); i++){
        fscanf(inputFile,"%d",&secondMatrix[i]);//Assign inputs from inputFile of second line to the secondMatrix[i]'s address
    }

}
void multiplyMatrices(int n, int *firstMatrix, int *secondMatrix, int *resultMatrix,FILE *inputFile){

    int i,j,k;
    readInput(n,firstMatrix,secondMatrix,inputFile);
    //i * (2 * n - i - 1) / 2 is used to find the starting index of the row i in a flattened (1D) representation of the lower triangular matrix.
    // Arithmetic series formula for the number of elements in the row.

    for(i = 0; i<n;i++){ // 'i' is for ROWs
        for(j=i; j<n; j++){ //'j' is defined as columns of the matrix.
            int sum =0;//Temporary sum variable for assigning new value to the resultMatrix
            for(k=i; k<=j;k++){//Multiplication two matrices -> using Arithmetic series formula
                sum += firstMatrix[i * (2 * n - i - 1) / 2 + k]*secondMatrix[k * (2 * n - k - 1) / 2 + j];
            }
            resultMatrix[i * (2 * n - i - 1) / 2 + j] = sum;
        }
 }
 print1DMatrix(n,resultMatrix);
 printf("\n\n");
 print2DMatrix(n,resultMatrix);
}
void print1DMatrix(int n, int *arr) {
    printf("Multiplication result as 1D array: \n");
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            printf("%d ", arr[i * (2 * n - i - 1) / 2 + j]);
        }
    }
}
void print2DMatrix(int n, int *arr) {
    printf("Multiplication result as 2D Matrix: \n");
    for (int i = 0; i < n; i++) {//Representation of rows.
        for (int j = 0; j < n; j++) {// For loop for columns.
            if (j < i) { //if column indice is lesser than row indice then it is under the diagonel.
                printf("0\t");
            } else { //Elements that are above diagonel -> print values
                printf("%d", arr[i * (2 * n - i - 1) / 2 + j]);
                if (j < n - 1) {//Spaces between columns
                    printf("\t");
                }
            }
        }
        printf("\n");
    }
}
int main() {
     FILE *inputFile;
     int *firstMatrix,*secondMatrix,*resultMatrix;
     int n;

     inputFile = fopen("input.txt","r");//Get reading access to the input.txt with "r" keyword.
     fscanf(inputFile,"%d",&n); // n input in order to create nxn matrices

    //Dynamic memory alloctaion for matrices with unknown number of elements.
    firstMatrix = (int *)malloc((n*(n+1)/2)*sizeof(int)); //CENG-205 Lecture4 Slide -> Non-zero element size for upper triangular matrix
    secondMatrix = (int *)malloc((n*(n+1)/2)*sizeof(int));
    resultMatrix = (int *)malloc((n*(n+1)/2)*sizeof(int));

    multiplyMatrices(n,firstMatrix,secondMatrix,resultMatrix,inputFile);

    // Prevents resource leaks, releases resource after processes.
    free(firstMatrix);
    free(secondMatrix);
    free(resultMatrix);

    fclose(inputFile);

    return 0;
}
