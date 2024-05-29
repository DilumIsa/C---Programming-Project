#include <stdio.h>

// Defined sizes
#define MAX_map_height 100
#define MAX_map_width 100
#define MAX_length 10000
#define Max_range 2

// Initate the size of the global array using some defined values
char result_array[MAX_map_height][MAX_map_width];
char character_array[MAX_length];
int cell_to_cell_going[MAX_map_height][MAX_map_width];
int tel_index[Max_range];
int tel_doors[MAX_length][Max_range];

// declared the global variables
int map_height, map_width;
int start_rows, start_cols;
int end_rows, end_cols;
int area_of_map;
int first_written_num, second_written_num, no_of_door_cells_in_map, calculated_num, count, m;
int tel_1_val, tel_2_val;

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

// Function to calculate the new raw value based on the move
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

// Function to find the minimum distance when there are no 2 teleport doors.
void arr()
{
    // Declared start character and end character for output
    char start_value = result_array[start_rows][start_cols];
    char end_value = result_array[end_rows][end_cols];

    // Find the minimum distance
    int minimum_Distance = findFunc_Minimum_Distance(start_rows, start_cols, end_rows, end_cols, cell_to_cell_going);

    // print the result according to given in the function
    if (minimum_Distance == 2147483647)
    {
        printf("There is no possible path from %c to %c\n", start_value, end_value);
    }
    else
    {
        printf("The minimum distance from %c to %c is %d\n", start_value, end_value, minimum_Distance);
    }
}

// Function to find the minimum distance when there are two teleport doors.
void min_arr(int tel_1_rows, int tel_1_cols, int tel_2_rows, int tel_2_cols)
{
    // Declared start character and end character for output
    char start_value = result_array[start_rows][start_cols];
    char end_value = result_array[end_rows][end_cols];

    // Variables to store minimum distances for different paths
    int start_to_end_min, start_to_tel_1_min, tel_2_to_end_min, tel_1_to_end_min, start_to_tel_2_min;
    int tel_doors_consider_path_1, tel_doors_consider_path_2;
    int minimum_Distance;

    // Array to store different paths
    int min_path_arr[5][4] = {{start_rows, start_cols, end_rows, end_cols},
                              {start_rows, start_cols, tel_1_rows, tel_1_cols},
                              {start_rows, start_cols, tel_2_rows, tel_2_cols},
                              {tel_1_rows, tel_1_cols, end_rows, end_cols},
                              {tel_2_rows, tel_2_cols, end_rows, end_cols}};

    // Calculate the minimum distances for each path
    start_to_end_min = findFunc_Minimum_Distance(min_path_arr[0][0], min_path_arr[0][1], min_path_arr[0][2], min_path_arr[0][3], cell_to_cell_going);

    start_to_tel_1_min = findFunc_Minimum_Distance(min_path_arr[1][0], min_path_arr[1][1], min_path_arr[1][2], min_path_arr[1][3], cell_to_cell_going);

    start_to_tel_2_min = findFunc_Minimum_Distance(min_path_arr[2][0], min_path_arr[2][1], min_path_arr[2][2], min_path_arr[2][3], cell_to_cell_going);

    tel_1_to_end_min = findFunc_Minimum_Distance(min_path_arr[3][0], min_path_arr[3][1], min_path_arr[3][2], min_path_arr[3][3], cell_to_cell_going);

    tel_2_to_end_min = findFunc_Minimum_Distance(min_path_arr[4][0], min_path_arr[4][1], min_path_arr[4][2], min_path_arr[4][3], cell_to_cell_going);

    // Decide which teleporter path to consider based on the minimum distances
    // Consider the nearest teleport door to the start position
    tel_doors_consider_path_1 = start_to_tel_1_min;
    tel_doors_consider_path_2 = start_to_tel_2_min;

    // Choose the shortest path considering teleporters
    // The first chosen door is the nearest teleport door. The path which satisfies this factor provides the minimum distance
    if (tel_doors_consider_path_1 < tel_doors_consider_path_2)
    {
        minimum_Distance = start_to_tel_1_min + tel_2_to_end_min;
    }
    else
    {
        minimum_Distance = start_to_tel_2_min + tel_1_to_end_min;
    }

    // If the minimum distance for teleport doors is greater than start-to-end distance
    if (minimum_Distance > start_to_end_min)
    {
        // get the minimum distance as start-to-end distance
        minimum_Distance = start_to_end_min;
    }

    // print the result according to given in the function
    if (minimum_Distance == 2147483647)
    {
        printf("There is no possible path from %c to %c\n", start_value, end_value);
    }
    else
    {
        printf("The minimum distance from %c to %c is %d\n", start_value, end_value, minimum_Distance);
    }
}

// Function to calculate Fibonacci number using memory array(use to memorize the data)
int fibonacci_num(int num, int memory[])
{
    if (num <= 1)
    {
        return num;
    }
    else if (memory[num] != -1)
    {
        return memory[num];
    }
    else
    {
        memory[num] = fibonacci_num(num - 1, memory) + fibonacci_num(num - 2, memory);
        return memory[num];
    }
}

// Function to compare if a given number's(num_1) Fibonacci number is equal to other 2 numbers(num_2 or num_3)
// this function retuns the TRUE or FALSE boolean values
int is_fibonacci_equal(int num_1, int num_2, int num_3)
{
    // Memory array to store calculated Fibonacci numbers
    int memory[num_1 + 1];
    for (int i = 0; i <= num_1; ++i)
    {

        // Initialize the memory array
        memory[i] = -1;
    }

    int fib_num = fibonacci_num(num_1, memory);
    return (fib_num == num_2 || fib_num == num_3);
}

int main()
{
    // Input map height map width
    // Input starting and ending position values
    scanf("%d %d", &map_height, &map_width);
    scanf("%d %d", &start_rows, &start_cols);
    scanf("%d %d", &end_rows, &end_cols);

    // Input character string
    area_of_map = map_height * map_width;
    scanf("%s", character_array);

    // Input written numbers on the map and number of door cells in the map
    scanf("%d", &first_written_num);
    scanf("%d", &second_written_num);
    scanf("%d", &no_of_door_cells_in_map);

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

    // created 2D array using input and stored the teleport doors
    tel_doors[no_of_door_cells_in_map][2];

    // Loop to get each teleport door cells (inputted by the user)
    for (int i = 0; i < no_of_door_cells_in_map; i++)
    {
        // Input teleport door cells coordinates
        scanf("%d %d", &tel_doors[i][0], &tel_doors[i][1]);

        // Calculate number for each teleport door cells
        calculated_num = (tel_doors[i][0] * map_width) + tel_doors[i][1];

        // Check if the Fibonacci number of the calculated number is a Fibonacci number matches either first_written_num or second_written_num
        if (is_fibonacci_equal(calculated_num, first_written_num, second_written_num))
        { 
            //To get the count of valid teleport door cell
            count += 1;
            //Store the index of this teleporter in the tel_index array
            tel_index[m++] = i;
        }
    }

    // Store the indices of the two valid teleport doors
    tel_1_val = tel_index[0];
    tel_2_val = tel_index[1];

    // If there are two valid teleport doors 
    if (count == 2)
    {
        //calculate the minimum distance considering teleport doors
        min_arr(tel_doors[tel_1_val][0], tel_doors[tel_1_val][1], tel_doors[tel_2_val][0], tel_doors[tel_2_val][1]);
    }
    else
    {
        // If there are no or only one valid teleport door
        //calculate the minimum distance without teleport doors
        arr();
    }

    return 0;
}
