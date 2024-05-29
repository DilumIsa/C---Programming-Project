#include <stdio.h>

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
    int num_1, num_2, num_3;

    // printf("Enter three numbers: ");
    scanf("%d %d %d", &num_1, &num_2, &num_3);

    if (is_fibonacci_equal(num_1, num_2, num_3))
    {
        printf("TRUE\n");
    }
    else
    {
        printf("FALSE\n");
    }

    return 0;
}