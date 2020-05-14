#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    // Prompt user to enter height.
    do
    {
        height = get_int("Height: ");
    }

    // Conditions goes here.
    while (height < 1 || height > 8);

    // Declare counter variable to ge
    for (int rows = 0; rows < height; rows++)
    {
        // Print white spaces to margin the triangle to the center.
        for (int spaces = (height - 1) - rows; spaces > 0; spaces--)
            printf(" ");
        
        // Draw the left triangle
        for (int hashes = 0; hashes <= rows; hashes++)
            printf("#");

        // Print space bwetween the triangles.
        printf("  ");

        // Draw the right triangle
        for (int hashes = 0; hashes <= rows; hashes++)
            printf("#");

        // Insert new line.
        printf("\n");
    }        
}