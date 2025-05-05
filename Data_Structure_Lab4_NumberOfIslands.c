#include <stdio.h>              // for input/output functions like printf
#include <stdlib.h>             // for dynamic memory allocation functions like malloc and free
#include <string.h>             // for strlen and strcpy

// function to perform dfs to mark all connected land ('1') as visited ('0')
void dfs(char** grid, int i, int j, int m, int n) {
    if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == '0') {   // check if out of bounds or water
        return;                                                     // stop recursion
    }

    grid[i][j] = '0';                                               // mark the current cell as visited

    dfs(grid, i - 1, j, m, n); // up
    dfs(grid, i + 1, j, m, n); // down
    dfs(grid, i, j - 1, m, n); // left
    dfs(grid, i, j + 1, m, n); // right
}

// function to count the number of islands
int numIslands(char** grid, int gridSize, int* gridColSize) {
    if (grid == NULL || gridSize == 0) {                            // check if grid is empty
        return 0;                                                   // no islands in an empty grid
    }

    int m = gridSize;                                               // number of rows
    int n = gridColSize[0];                                         // number of columns
    int num_islands = 0;                                            // counter for islands

    // iterate through each cell in the grid
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '1') {                                // if the cell is land
                num_islands++;                                      // increment the island counter
                dfs(grid, i, j, m, n);                              // perform dfs to mark the entire island
            }
        }
    }

    return num_islands;                                             // return the total number of islands
}

// example usage
int main() {
    int gridSize = 4;                                               // number of rows in the grid
    int gridColSize[] = {5, 5, 5, 5};                               // number of columns in each row

    // dynamically allocate a writable grid
    char** grid = (char**)malloc(gridSize * sizeof(char*));         // allocate memory for the grid rows
    grid[0] = (char*)malloc(strlen("11110") + 1);                   // allocate memory for the first row
    strcpy(grid[0], "11110");                                       // copy the first row data
    grid[1] = (char*)malloc(strlen("11010") + 1);                   // allocate memory for the second row
    strcpy(grid[1], "11010");                                       // copy the second row data
    grid[2] = (char*)malloc(strlen("11000") + 1);                   // allocate memory for the third row
    strcpy(grid[2], "11000");                                       // copy the third row data
    grid[3] = (char*)malloc(strlen("00000") + 1);                   // allocate memory for the fourth row
    strcpy(grid[3], "00000");                                       // copy the fourth row data

    int result = numIslands(grid, gridSize, gridColSize);           // call the function to count islands
    printf("number of islands: %d\n", result);                      // print the result

    // free allocated memory
    for (int i = 0; i < gridSize; i++) {                            // iterate through each row
        free(grid[i]);                                              // free memory for each row
    }
    free(grid);                                                     // free memory for the grid

    return 0;                                                       // exit the program
}