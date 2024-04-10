// general purpose standard C lib
#include <stdio.h>
#include <stdlib.h> // stdlib includes malloc() and free()

// user-defined header files
#include "chain.h"


#include <stdbool.h>
#define MAX_COLS 10

// function prototypes
void print_chain(chain * chn); 
void run(chain * chn);


int main()
{
    chain * chn = (chain *) malloc(sizeof(chain));
    chn->head = NULL;
	run(chn);
    print_chain(chn);
    free(chn);
	return 0;
}

// parse the input
void run(chain *chn) 
{
    int row;
    scanf("%d", &row);

    int *first_row = (int *)malloc(MAX_COLS * sizeof(int));
    int column = 0;
    
    do {
        scanf("%d", &first_row[column++]);
    } 
    while (getchar() != '\n' && column < MAX_COLS);
    first_row = (int *)realloc(first_row, column * sizeof(int)); 

    matrix *currentMat = create_matrix(row, column); //Creating the initial matrix with the first row
    for (int i = 0; i < column; i++){
        currentMat->data[0][i] = first_row[i];
    }
    free(first_row);

    for (int j = 1; j < row; j++){//Populating the rest of the matrix rows
        currentMat->data[j] = (int *)malloc(column * sizeof(int)); 
        for (int count = 0; count < column; count++) {
            scanf("%d", &currentMat->data[j][count]);
        }
    }

    //Inserting the initial matrix as the first node in the chain
    insert_node_after(chn, -1, currentMat);
    node *current = chn->head;

    int flag = true;
    int command;
    while (flag){
        scanf("%d", &command);

        switch (command) {
            case 0:
                flag = false;
                break;
                
            case 1:
                break;
                
            case 2:  //Inserting row
            {
                int new_row[current->mat->num_cols];
                for (int i = 0; i < current->mat->num_cols; i++) {
                    scanf("%d", &new_row[i]);
                }
                matrix *mat = clone(current->mat);
                add_row(mat, new_row);
                insert_node_after(chn, -1, mat);
                current = current->next;
                break;
            }
            
            case 3: //Inserting column
            {
                int new_col[current->mat->num_rows];
                for (int i = 0; i < current->mat->num_rows; i++) {
                    scanf("%d", &new_col[i]);
                }
                matrix *mat = clone(current->mat);
                add_col(mat, new_col);
                insert_node_before(chn, 0, mat);
                current = current->next;
                break;
            }
            
            case 4: //Incrementing values
            {
                matrix *mat = clone(current->mat);
                int inc;
                scanf("%d", &inc);
                increment(mat, inc);
                insert_node_before(chn, 0, mat);
                current = current->next;
                break;
            }
            
            case 5: //Multiplying by scalar
            {
                int multiplier;
                scanf("%d", &multiplier);
                matrix *mat = clone(current->mat);
                scalar_multiply(mat, multiplier);
                insert_node_before(chn, 0, mat);
                current = current->next;
                break;
            }
            
            case 6: //Dividing by scalar
            {
                int divisor;
                scanf("%d", &divisor);
                matrix *mat = clone(current->mat);
                scalar_divide(mat, divisor);
                insert_node_before(chn, 0, mat);
                current = current->next;
                break;
            }
            
            case 7: //Raising to power
            {
                int power;
                scanf("%d", &power);
                matrix *mat = clone(current->mat);
                scalar_power(mat, power);
                insert_node_before(chn, 0, mat);
                current = current->next;
                break;
            }
            case 8: //Deleting matrix
            {
                matrix *mat = current->mat;
                current = current->next;  
                delete_matrix(mat);
                break;
            }
            
            default:
            {
                flag = false;
                break;
                
            }
        }
    }
	
}

//Print the chain
void print_chain(chain * chn)
{
    node *current = chn->head;

    do {
        print_matrix(current->mat);
        printf("\n");
        current = current->next;
    } while (current != chn->head); 
   
}
