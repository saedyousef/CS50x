#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

// Max number of candidates.
#define MAX 9

// Pair type, which each pair has a winner and loser attribute.
typedef struct
{
    int winner;
    int loser;
}
pair;

// Global variables.
// Preferences array, the number of voters who prefer candidate over other candidate.
int preferences[MAX][MAX];

// Pairs array to store the each pair in the elecetion.
pair pairs[MAX * (MAX -1) / 2];

// Array of candidates.
string candidates[MAX];

// Locked pairs.
bool locked[MAX][MAX];

// Lock attribute.
bool lock = true;

// Pairs count.
int pair_count = 0;

// Candidates count.
int candidate_count;

// Main.
int  main(int argc, string argv[])
{
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");

        // Return 1 so we can chase it in debugging.
        return 1;
    }

    // Assign the count of candidates.
    // argc - 1, because the first argument is for the run command.
    candidate_count = argc - 1;

    // Validate the enterd number of candidates.
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);

        // Return 2 so we can chase it in debugging.
        return 2;
    }

    // Assign the candidates names into the candidates array.
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1]; // Remember, we ignore the first argument.
    }

    // Setting default values before we start calculating the ranks, and to get Graph cleared.
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    // Prompt user to enter the voters count.
    int voter_count = get_int("Number of voters: ");

    // Looping through votes.
    for (int i = 0; i < voter_count; i++)
    {
        // Ranks array.
        int ranks[candidate_count];

        // Get prefered candidates for each vote.
        for (int c = 0; c < candidate_count; c++)
        {
            // Prompt the user to rank the candidates as prefered.
            string name = get_string("Rank %d: ", c + 1);

            // Now vote and check
            if (!vote(c, name, ranks))
            {
                printf("Invalid vote.\n");

                // Return 3 so we can chase it in debugging.
                return 3;
            }
        }

        // Now record preferences.
        record_preferences(ranks);

        // New line.
        printf("\n");
    }

    // Update, sort and lock pairs then print the winner!
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();

    // Means the main function executed with 0 errors.
    return 0;
}