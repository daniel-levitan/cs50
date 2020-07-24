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

void order_dec(int size, int vector[][2]);
int find_max(int size, int vector[][2], int start);
bool has_cycle(int winner, int loser);


// int wins[MAX];

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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences [ ranks[i] ] [ ranks[j] ] ++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
            }
            else if (preferences[j][i] > preferences[i][j])
            {
                pairs[k].winner = j;
                pairs[k].loser = i;
                k++;
            }
        }
    }
    pair_count = k;
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    // Here I order a new variable
    // array of tuples (first element is the difference, second element is the index)
    int pairs_int[pair_count][2];

    for (int i = 0; i < pair_count; i++)
    {
        pairs_int[i][0] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
        pairs_int[i][1] = i;
    }
    order_dec(pair_count, pairs_int);

    // Here I build a new pair and order it according to the previous variable
    pair new_pairs[pair_count * (pair_count - 1) / 2];
    for (int i = 0; i < pair_count; i++)
    {
        new_pairs[i] = pairs[pairs_int[i][1]];
    }

    // Here I copy the previous order to the global pairs variable
    for (int i = 0; i < pair_count; i++)
    {
        pairs[i] = new_pairs[i];
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        // printf("%d (%d,%d)\n", i, pairs[i].winner, pairs[i].loser );
        if (!has_cycle(pairs[i].winner, pairs[i].loser))
        {
            // printf("locking\n");
            locked[pairs[i].winner][pairs[i].loser] = true;
            // printf("(%d,%d) ", pairs[i].winner, pairs[i].loser );
        }
        // else
        // {
        //     printf("not locking\n");
        // }
    }
    return;
}


bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner])
        return true;

    for (int i = 0; i < pair_count; i++)
    {
        if ((locked[i][winner]) && (locked[loser][i] || has_cycle(i, loser)) )
            return 1;
    }
    return false;
}

int countRow(int row)
{
    int sum = 0;
    for (int j = 0; j < pair_count; j++)
        sum += locked[row][j];

    return sum;
}

bool isColEmpty(int col)
{
    int sum = 0;
    for (int i = 0; i < pair_count; i++)
    {
        sum += locked[i][col];
    }

    if (sum != 0)
        return false;

    return true;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    // for (int j = 0; j < pair_count; j++)
    //     if (isColEmpty(j))
    //         if (countRow(j) != 0)
    //             printf("%s", candidates[j]);

    // for (int j = 0; j < pair_count; j++)
    for (int j = 0; j < candidate_count; j++)
    {
        int sum = 0;
        // for (int i = 0; i < pair_count; i++)
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j])
                sum++;
        }
        if (!sum)
            printf("%s\n", candidates[j]);
    }
}


int find_max(int size, int vector[][2], int start)
{
    int max = vector[start][0]; // first item
    int index = start;

    for (int i = start; i < size; i++)
    {
        if (vector[i][0] > max)
        {
            max = vector[i][0];
            index = i;
        }
    }
    return index;
}

void order_dec(int size, int vector[][2])
{
    int greatest;
    int temp[2];

    for (int i = 0; i < size; i++)
    {
        greatest = find_max(size, vector, i);
        temp[0] = vector[i][0];
        temp[1] = vector[i][1];

        vector[i][0] = vector[greatest][0];
        vector[i][1] = vector[greatest][1];

        vector[greatest][0] = temp[0];
        vector[greatest][1] = temp[1];
    }
}

