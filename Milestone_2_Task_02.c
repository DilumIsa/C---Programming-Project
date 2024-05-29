#include <stdio.h>

// Defined sizes
#define MAX_map_height 100
#define MAX_map_width 100
#define MAX_length 10000

// Initate the size of the global array using some defined values
char result_array[MAX_map_height][MAX_map_width];
int cell_to_cell_going[MAX_map_height][MAX_map_width];
char character_array[MAX_length];

// declared the global variables
int map_height, map_width;
int area_of_map;
int start_rows, start_cols;
int end_rows, end_cols;
int tel_1_rows, tel_1_cols;
int tel_2_rows, tel_2_cols;

// Function to create a 2D array from an input string character array
char creating_2d_array(int map_height, int map_width, char *character_array, char result_array[MAX_map_height][MAX_map_width])
{
    int count = 0;
    for (int i = 0; i < map_height; i++)
    {
        for (int j = 0; j < map_width; j++)
        {
            result_array[i][j] = character_array[count];
            count += 1;
        }
    }
    return result_array[MAX_map_height][MAX_map_width];
}

// Function to check if a move is valid within the map boundaries
int is_valid_move(int x, int y)
{
    return (x >= 0 && x < map_height && y >= 0 && y < map_width);
}

// Function to get the distance between two characters
int get_distance(int C1, int C2)
{
    // if two characters are same or they are in the given range give to move on using return 1
    if (C1 == C2 || (C2 > C1 && C2 - C1 <= 2) || (C1 > C2 && C1 - C2 <= 3))
    {
        return 1;
    }
    else
    {
        // Return a large value to indicate an invalid or unreachable move.it gives as a reference value for the invalid move(To cover the infinite distance)
        return 2147483647;
    }
}

// Function to calculate the new row value based on the move
int new_rows_value(int start_rows, int i)
{
    // Define the possible changes in the current row for each direction {left, up, right, down}.
    int x[4] = {-1, 0, 1, 0};
    return start_rows + x[i];
}

// Function to calculate the new column value based on the move
int new_cols_value(int start_cols, int i)
{
    // Define the possible changes in the current col for each direction {left, up, right, down}.
    int y[4] = {0, 1, 0, -1};
    return start_cols + y[i];
}

// Function to find the minimum distance for given 2 poisitions using recursion
int findFunc_Minimum_Distance(int start_rows, int start_cols, int end_rows, int end_cols, int cell_to_cell_going[MAX_map_height][MAX_map_width])
{
    // if starting position and ending position is same return 0 because there is no need to move.
    if (start_rows == end_rows && start_cols == end_cols)
    {
        return 0;
    }

    // Mark the current cell as before went cell.
    cell_to_cell_going[start_rows][start_cols] = 1;

    // Initialize the minimum distance to a large value.
    int minimum_Distance = 2147483647;

    // Iterate over possible moves using above functions(left, up, right, down).
    for (int i = 0; i < 4; i++)
    {
        // Calculate the new row and col values after making a move.
        int newX = new_rows_value(start_rows, i);
        int newY = new_cols_value(start_cols, i);

        // Check if the move is valid
        // not going to the current cell before
        // and the getting distance is valid: [MAIN PART OF THIS CODE]
        if (is_valid_move(newX, newY) && !cell_to_cell_going[newX][newY] && get_distance(result_array[start_rows][start_cols], result_array[newX][newY]) == 1)
        {
            // Recursively find the getting distance for the new position: [MAIN PART OF THIS CODE]
            int distance = findFunc_Minimum_Distance(newX, newY, end_rows, end_cols, cell_to_cell_going);

            // if getting distance is valid check the minimum distance from the getting distances
            if (distance != 2147483647)
            {
                // if minimum_Distance < (distance + 1)(representing the distance of the current move): Keep the minimum_Distance as well.
                // Otherwise Update minimum_Distance with the shorter path (distance + 1):[Used recursively thinking]
                minimum_Distance = (minimum_Distance < (distance + 1)) ? minimum_Distance : (distance + 1);
            }
        }
    }

    // Mark the current cell as not before went cell for going backward.
    cell_to_cell_going[start_rows][start_cols] = 0;

    return minimum_Distance;
}

// Function to find minimum distances for various paths
void min_arr(int start_rows, int start_cols, int end_rows, int end_cols, int tel_1_rows, int tel_1_cols, int tel_2_rows, int tel_2_cols, int cell_to_cell_going[MAX_map_height][MAX_map_width])
{
    // Array to store different paths
    int min_path_arr[5][4] = {{start_rows, start_cols, end_rows, end_cols},
                              {start_rows, start_cols, tel_1_rows, tel_1_cols},
                              {start_rows, start_cols, tel_2_rows, tel_2_cols},
                              {tel_1_rows, tel_1_cols, end_rows, end_cols},
                              {tel_2_rows, tel_2_cols, end_rows, end_cols}};

    // Loop the each path
    for (int i = 0; i < 5; i++)
    {
        // Find the minimum distance for the current path
        int minimum_Distance = findFunc_Minimum_Distance(min_path_arr[i][0], min_path_arr[i][1], min_path_arr[i][2], min_path_arr[i][3], cell_to_cell_going);

        // Check if the minimum distance is maximum integer value (indicating an invalid path)
        if (minimum_Distance == 2147483647)
        {
            // if the path is invalid Print -1 
            printf("-1 ");
        }
        else
        {
            // Print the minimum distance
            printf("%d ", minimum_Distance);
        }
    }
}

int main()
{
    // Input map height map width 
    //Input starting and ending position values
    scanf("%d %d", &map_height, &map_width);
    scanf("%d %d", &start_rows, &start_cols);
    scanf("%d %d", &end_rows, &end_cols);

    // Input character string 
    area_of_map = map_height * map_width;
    scanf("%s", character_array);

    // Input teleport door 1 and teleport door 2 position values
    scanf("%d %d", &tel_1_rows, &tel_1_cols);
    scanf("%d %d", &tel_2_rows, &tel_2_cols);

    // created 2D array using input characters
    creating_2d_array(map_height, map_width, character_array, result_array);

    // Initialize the cell_to_cell_going array
    for (int i = 0; i < MAX_map_height; i++)
    {
        for (int j = 0; j < MAX_map_width; j++)
        {
            cell_to_cell_going[i][j] = 0;
        }
    }

    // Find the minimum distance considering teleport doors
    min_arr(start_rows, start_cols, end_rows, end_cols, tel_1_rows, tel_1_cols, tel_2_rows, tel_2_cols, cell_to_cell_going);

    return 0;
}
