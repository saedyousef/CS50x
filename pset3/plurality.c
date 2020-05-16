#include <stdio.h>
#include <cs50.h>
#include <string.h>

// Max candidates 
#define MAX 9

// Candidate type
typedef struct{
    string name;
    int votes;
}
candidate;

// Candidates array
candidate candidates[MAX];

// Number of candidates
int candidateCount;

// Prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check if no arguments has been passed
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidateCount = argc - 1;

    // Check if the candidates count more than the max value.
    if (candidateCount > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 1;
    }

    // Fill candidates data in the candidates array.
    for (int i = 0; i < candidateCount; i++)
    {
        candidates[i].votes = 0;
        candidates[i].name = argv[i + 1];
    }
    // Promt user to enter number of voters.
    int votesCount = get_int("Number of voters:");
    string name;

    // Calculate votes.
    for (int i = 0; i < votesCount; i++)
    {
        name = get_string("Vote: ");

        // Check invalid votes.
        if (!vote(name))
        {
             printf("Invalid vote.\n");
        }
    }

    // Print out the winner candidate.
    print_winner();
}


bool vote(string name)
{
    for (int i = 0; i < candidateCount; i++)
    {

        // Check if the name matches any of candidates.
        if (strcmp(name,  candidates[i].name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    // If the name didn't match any of candidates.
    return false;
}

void print_winner(void)
{
    int tempVotes = 0;

    // Store the the highest votes.
    for (int i = 0; i < candidateCount; i++)
    {
        if (candidates[i].votes >= tempVotes)
        {
            tempVotes = candidates[i].votes;
        }
    }

    // Matching the candidates votes count with the highest votes and print all matches.
    for (int i = 0; i < candidateCount; i++)
    {
        if (candidates[i].votes == tempVotes)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
