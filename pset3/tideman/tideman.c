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
pair pairs[MAX * (MAX - 1) / 2];

// Array of candidates.
string candidates[MAX];

// Locked pairs.
bool locked[MAX][MAX];

// Pairs count.
int pair_count;

// Candidates count.
int candidate_count;


// Functions prototypes.
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void lock_pairs(void);
void sort_pairs(void);
void print_winner(void);
int comparator(const void *p, const void *q);
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
                return 0;
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

// Update the rank for each new vote.
bool vote(int rank, string name, int ranks[])
{
    // Update ranks
    for (int i = 0; i < candidate_count; i++)
    {
        // Check if the candidate is exists.
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    // No candidates found, don't update anything and return false.
    return false;
}


// Update the preferences voter's rank after one vote.
void record_preferences(int ranks[])
{
    // The prefered candidate.
    for (int i = 0; i < candidate_count; i++)
    {
        // The candidate prefered over.
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Adding pairs where a candidates is prefered over another candidate.
void add_pairs(void)
{
    pair_count = 0;
    // Loop through candidates and specify the winner and loser for each pair.
    for (int i = 0; i < candidate_count; i++)
    {
        // We need another loop to get the prefered over candidate and compare with the cadidates[i].
        // Starts with the second candidate to the one we are looping on.
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}


// Sorting pairs
void sort_pairs(void)
{
    // If u want, try to implement a sorting algorithm like "Merge Sort" and use it.
    // I've already has that done in another language, so I'm just going to use qsort function.
    // Check this https://www.codingunit.com/c-reference-stdlib-h-function-qsort .
    qsort(pairs, pair_count, sizeof(pair), comparator);
}

// Comparing function, in order to sort pairs with qsort(Already implemented in stdlib).
// check https://www.geeksforgeeks.org/comparator-function-of-qsort-in-c/ for more details.
int comparator(const void *p, const void *q)
{
    // Decalraing two pointer of pair.
    pair *pointer1 = (pair *)p;
    pair *pointer2 = (pair *)q;

    int value = preferences[pointer2->winner][pointer2->loser] - preferences[pointer1->winner][pointer1->loser];

    return value;
}

void lock_pairs(void)
{
    // Intialize the first locked pairs.
    if (pair_count > 0)
    {
        locked[pairs[0].winner][pairs[0].loser] = true;
    }

    // Starts with the second index, cause the first index already locked.
    for (int i = 1; i < pair_count; i++)
    {
        bool cycle = false;
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[pairs[i].loser][j])
            {
                cycle = true;
                break;
            }
        }

        if (!cycle)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void)
{
    int votes = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            if (locked[k][i] == false)
            {
                votes++;
            }
        }

        // Print all source graph candidates.
        if (votes == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
}