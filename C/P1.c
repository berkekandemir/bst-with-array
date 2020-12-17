#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

// Constant Values
const int SIZE = 500; // 50, 100, 500
const int SIZE_WITH_NULLs = 100000; // 10000 for 50; 100000 for 100, 500;
                                   // because there is so many empty spaces in tree.
const int INT_MAX = 2147483647; // I assumed that there wont't be any number equal to that.

// Function Definitions
void insert(int tree[], int number, int ind){
    if (tree[ind] != INT_MAX) { // There won't be any duplicate number.
        if (number > tree[ind]) {
            int new_ind = ind * 2 + 2;
            insert(tree, number, new_ind);
        } else if (number < tree[ind]) {
            int new_ind = ind * 2 + 1;
            insert(tree, number, new_ind);
        }
    } else {
        tree[ind] = number;
        return;
    }
    return;
}

void traverse(int tree[], int ind, FILE *write_file){ // Pointers for File I/O, was compulsory
    if (ind > (SIZE_WITH_NULLs - 1)) {
        return;
    } 
    traverse(tree, (ind * 2) + 1, write_file);
    if (tree[ind] != INT_MAX) {
        fprintf(write_file, "%d ", tree[ind]);
    }
    traverse(tree, (ind * 2) + 2, write_file);
}

int main(int argc, char* argv[]) {
    // Tree
    int tree[SIZE_WITH_NULLs];
    for (int i = 0; i < SIZE_WITH_NULLs; i++) {
        tree[i] = INT_MAX;
    }
    int ind = 0;

    // File Reading into an Array
    FILE *read_file; // I had to use pointers because 
                     // I couldn't find any resource for reading a file without pointers
    read_file = fopen("numbers_500.txt", "r");
    char line[3433]; // 344 for 50; 689 for 100; 3433 for 500 
    int numbers[SIZE];
    fgets(line, 3433, (FILE*) read_file);
    fclose(read_file);
    char *piece; // I had to use pointers because 
                 // I couldn't find any resource for splitting a line without pointers
    piece = strtok(line, " ");
    int count = 0;
    while (piece != NULL) {
        numbers[count] = atoi(piece);
        piece = strtok(NULL, " ");
        count++;
    }

    // Tree Building without any Pointers as Mentioned in the HW File
    /////////////////////////////////////////////////////////////////
    clock_t start, end;
    start = clock();
    for (int i = 0; i < SIZE; i++) {
        insert(tree, numbers[i], ind);
    }
    end = clock();
    double elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    /////////////////////////////////////////////////////////////////

    // File Writing by Inorder Traversing the Tree
    FILE *write_file; // I had to use pointers because 
                      // I couldn't find any resource for reading a file without pointers
    write_file = fopen("numbers_500_sorted.txt", "a");
    fprintf(write_file, "Total time: %lf seconds\n", elapsed_time);
    traverse(tree, ind, write_file);
    fclose(write_file);
}