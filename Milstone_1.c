#include <stdio.h>

// Defined sizes
#define MAX_map_height 100
#define MAX_map_width 100
#define MAX_length 10000

// Initate the size of the global array using some defined values
char result_array[MAX_map_height][MAX_map_width];
int cell_to_cell_going[MAX_map_height][MAX_map_width];
char character_array[MAX_length];

// declared the variables for the map height and map width
int map_height, map_width;

// Function to create a 2D array from a input string character array
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

// Function to calculate the new column value based on the move
int new_col_value(int start_col, int i)
{
    // Define the possible changes in the current col for each direction {left, up, right, down}.
    int x[4] = {-1, 0, 1, 0};
    int new_col = start_col + x[i];
    return new_col;
}

// Function to calculate the new row value based on the move
int new_row_value(int start_row, int i)
{
    // Define the possible changes in the current row for each direction {left, up, right, down}.
    int y[4] = {0, 1, 0, -1};
    int new_row = start_row + y[i];
    return new_row;
}

// Function to find the minimum distance for starting and ending positions using recursion
int findFunc_Minimum_Distance(int start_col, int start_row, int end_col, int end_row, int cell_to_cell_going[MAX_map_height][MAX_map_width])
{
    // if starting position and ending position is same return 0 because there is no need to move.
    if (start_col == end_col && start_row == end_row)
    {
        return 0;
    }

    // Mark the current cell as before went cell.
    cell_to_cell_going[start_col][start_row] = 1;

    // Initialize the minimum distance to a large value.
    int minimum_Distance = 2147483647;

    // Iterate over possible moves using above functions(left, up, right, down).
    for (int i = 0; i < 4; i++)
    {
        // Calculate the new row and col values after making a move.
        int newX = new_col_value(start_col, i);
        int newY = new_row_value(start_row, i);

        // Check if the move is valid
        // not going to the current cell before
        // and the getting distance is valid: [MAIN PART OF THIS CODE]
        if (is_valid_move(newX, newY) && !cell_to_cell_going[newX][newY] && get_distance(result_array[start_col][start_row], result_array[newX][newY]) == 1)
        {
            // Recursively find the getting distance for the new position: [MAIN PART OF THIS CODE]
            int distance = findFunc_Minimum_Distance(newX, newY, end_col, end_row, cell_to_cell_going);

            // if getting distance is valid check the minimum distance from the getting distances
            if (distance != 2147483647)
            {
                // distance plus 1 (representing the distance of the current move)
                if (minimum_Distance < (distance + 1))
                {
                    // Keep the minimum_Distance as well.
                    minimum_Distance = minimum_Distance;
                }
                else
                {
                    // Update minimum_Distance with the shorter path (distance + 1):[Used recursively thinking]
                    minimum_Distance = distance + 1;
                }
            }
        }
    }

    // Mark the current cell as not before went cell for going backward.
    cell_to_cell_going[start_col][start_row] = 0;

    return minimum_Distance;
}

int main()
{
    // declared the variables for the start col, start row, end col and end row
    int start_col, start_row;
    int end_col, end_row;

    // Input map boundaries, starting and ending position values
    scanf("%d %d", &map_height, &map_width);
    scanf("%d %d", &start_col, &start_row);
    scanf("%d %d", &end_col, &end_row);

    // get the string input and create a 2D array
    
    int area_of_map = map_height * map_width;
    char character_array[area_of_map];
    scanf("%s", &character_array);

    creating_2d_array(map_height, map_width, character_array, result_array);
    
    // Declared start character and end ccharacter for formatting output
    char start_value = result_array[start_col][start_row];
    char end_value = result_array[end_col][end_row];

    // Initate the array declaring the value 0
    cell_to_cell_going[MAX_map_height][MAX_map_width] = 0;

    // Find the minimum distance for print the result
    int minimum_Distance = findFunc_Minimum_Distance(start_col, start_row, end_col, end_row, cell_to_cell_going);

    // print the result according to given in the function
    if (minimum_Distance == 2147483647)
    {
        printf("There is no possible path from %c to %c", start_value, end_value);
    }
    else
    {
        printf("The minimum distance from %c to %c is %d\n", start_value, end_value, minimum_Distance);
    }

    return 0;
}
