#include <stdio.h>
#include <stdlib.h> // includes malloc(), free(), realloc()
#include <string.h> // includes memcpy()

#include "chain.h" // do not modify this file

// put your function prototypes for additional helper functions below:


// implementation
//chain.c implementation
matrix *create_matrix(int num_rows, int num_cols)
{   
   // Allocating memory for the matrix structure 
   matrix *temp_Matrix = (matrix *)malloc(sizeof(matrix));
    if (temp_Matrix == NULL){ // Checking whether the memory allocation was successful
        return NULL; 
    }

    temp_Matrix->num_rows =num_rows;// Initialize the matrix structure with the given number of rows
    temp_Matrix->num_cols =num_cols;// Initialize the matrix structure with the given number of columns

    temp_Matrix->data = (int **)malloc(num_rows * sizeof(int *));// Allocating memory for the data of the matrix
    
    if (temp_Matrix->data ==NULL){ // Checking ehether the memory allocation was successful
        free(temp_Matrix); 
        return NULL;
    }
    // Allocating memory for each row of the matrix
    for (int i = 0; i <num_rows; i++){ 
        temp_Matrix->data[i] = (int *)malloc(num_cols * sizeof(int));
        
        
        if (temp_Matrix->data[i] == NULL) {// Checking whether the memory allocation was successful
            
            for (int j = 0; j < i; j++) { // Freeing the previously allocated memory
                free(temp_Matrix->data[j]);
            }
            free(temp_Matrix-> data);
            free(temp_Matrix);
            return NULL;
        }
    }

    return temp_Matrix;
}

void add_row(matrix *mat, int *row)
{
    if (mat == NULL || row == NULL){ // Checking  whether the matrix and row are not NULL
        return;
    }
    
    int new_row = mat->num_rows ;// Obtaining the index of the new row
    
    mat->data = (int **)realloc(mat->data,(new_row + 1) * sizeof(int *));// Reallocating memory to accommodate the new row
    mat->data[new_row] =(int *)malloc(mat->num_cols * sizeof(int));

    for (int i = 0; i < mat->num_cols; i++){
        mat->data[new_row][i] =row[i]; // Coping the values of the new row to the matrix
    }

    mat->num_rows++; // Incrementing the number of rows in the matrix
}

void add_col(matrix *mat, int *col)
{
    
    if (mat == NULL || col == NULL){ // Checking  whether the matrix and row are not NULL
        return;
    }
    
    int new_col =mat->num_cols;// Obtaining the index of the new column
    
    for (int i = 0; i <  mat->num_rows; i++){
        // Reallocating memory to accommodate the new column
        mat->data[i] = (int *)realloc(mat->data[i], (new_col + 1) * sizeof(int));
        mat->data[i][new_col] = col[i];
    }

    mat->num_cols++;// Incrementing the number of columns in the matrix
   
}

void increment(matrix *mat, int num)
{
    if (mat == NULL){ // Checking whether the matrix is not NULL
        return;
    }

    // Looping through each element of the matrix and increment it by the given number
    for (int i = 0; i < mat->num_rows; i++){
        for (int j = 0; j < mat->num_cols; j++){
            mat->data[i][j] += num;
        }
    }

}

void scalar_multiply(matrix *mat, int num)
{
    if (mat == NULL){// Checking whether the matrix is not NULL
        return;
    }

    // Looping through each element of the matrix and multiply it by the given number
    for (int i = 0; i < mat->num_rows; i++){
        for (int j = 0; j < mat->num_cols; j++){
            mat->data[i][j] *=num;
        }
    }
}

void scalar_divide(matrix *mat, int num)
{
    if (mat == NULL || num == 0){ // Checking whether the matrix is not NULL and the divisor is not 0
        return;
    }

    // Looping through each element of the matrix and divide it by the given number
    for (int i = 0; i < mat->num_rows; i++){
        for (int j = 0; j < mat->num_cols; j++){
            mat->data[i][j] /=num;
        }
    }
}

void scalar_power(matrix *mat, int num)
{
    if (mat == NULL || num < 0){ // Checking whether the matrix is not NULL and the power is not negative
        return;
    }

    for (int i = 0; i < mat->num_rows; i++){
        
        for (int j = 0; j <mat->num_cols; j++){
            
            int source_Value =mat->data[i][j];
            
            for (int k = 1; k < num; k++){
                mat->data[i][j] *=source_Value; // Multiplying the element by itself 'num' times
            }
        }
    }
}

void delete_matrix(matrix *mat)
{
    if (mat == NULL){  // Checking  whether the matrix is not NULL
        return;
    }

    for (int i = 0; i < mat->num_rows;i++){
        
        free(mat->data[i]); // Freeing the memory for each row of the matrix
    }
    free(mat->data); // Freeing the memory for the data of the matrix
    free(mat); // Free the memory for the matrix itself      
}



/*
    DO NOT MODIFY BELOW
*/
// print out matrix in row-major order
// elements in the same row are space-separated
// each row starts in a new line
void print_matrix(matrix *mat) 
{
    int row_idx, col_idx;
    for(row_idx = 0; row_idx < mat->num_rows; ++row_idx) {
        for(col_idx = 0; col_idx < mat->num_cols; ++col_idx) {
            if (col_idx == mat->num_cols-1) {
                printf("%d\n", mat->data[row_idx][col_idx]);
            } else {
                printf("%d ", mat->data[row_idx][col_idx]);
            }
        }
    }
}

//Add the rest of the functions needed for the chain below

//Function to clone a matrix and return a new matrix with the same values
matrix *clone(matrix *init)
{
    
    //Creating a new matrix with the same number of rows and columns as the initial matrix
    matrix *newMat = create_matrix(init->num_rows, init->num_cols);
    for (int i = 0; i < init->num_rows; i++){
        
        for (int j = 0; j < init->num_cols; j++){
            newMat->data[i][j] = init->data[i][j];
        }
    }
    return newMat;
}

//Function to insert a new node before a given index in the chain
void insert_node_before(chain *chn, int index, matrix *mat) {
    node *newNode = (node *)malloc(sizeof(node));
    newNode->mat = mat;

    if (chn->head == NULL){
        
        //If the chain is empty, set the head to the new node
        newNode->prev = newNode;
        newNode->next = newNode;
        chn->head = newNode;
    } 
    else{
        //If the chain is not empty, find the node at the given index
        node *current =chn->head;

        if (index >= 0){
            for (int i = 0; i < index; i++){
                current = current->next;
            }
        } else if (index < 0){
            for (int i = 0; i > index; i--){
                current = current->prev;
            }
        }
        
        //Inserting the new node before the found node
        newNode->prev =current->prev;
        newNode->next =current;
        current->prev->next =newNode;
        current->prev =newNode;

        
    }
}

//Function to insert a new node after a given index in the chain
void insert_node_after(chain *chn, int index, matrix *mat) {
    index =index +1;
    insert_node_before(chn,index,mat);
}

//-----------------Implementation of Lab1-2-3.c file--------------

int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}
