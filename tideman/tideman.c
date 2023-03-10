#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[i] = rank;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int length = sizeof(a) / sizeof(int);
    string counted[strlen(ranks)];
    for (int rank = 0; rank < strlen(ranks); i++)
    {
        string voted_candidate = ranks[rank];
        for (int i = 0; i < candidate_count; i++)
        {
            if (strcmp(voted_candidate, cadidates[i]) == 0)
            {
                continue;
            }

            for (int j = 0; j < strlen(counted); j++)
            {
                if (strcmp(counted[j], cadidates[i]) == 0)
                {
                    continue;
                }
                else
                {
                    if (preferences[voted_candidate][cadidates[i]] == NULL)
                    {
                        preferences[voted_candidate][cadidates[i]] = 0;
                    }
                    preferences[voted_candidate][cadidates[i]] += 1;
                }
            }
        }
        counted[rank] = voted_candidate;
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; i < candidate_count; j++)
        {
            string A = candidates[i], B = candidates[j];
            int diff = preference[A][B] - preference[B][A] ? preference[A][B] > preference[B][A] : preference[B][A] - preference[A][B];
            pair[i].winner = A;
            pair[i].loser = B;
            printf("Winner is %s, loser is %s."pair[i].winner, pair[i].loser);
        }
    }

}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    return 0;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return 0;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return 0;
}