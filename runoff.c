#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // TODO
    for(int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {
            preferences[voter][rank] = candidates[i].name;
            voter_count++;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
     // TODO
    // loop throuth candidates and voters
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (candidates[j].eliminated == false)
            {
                // check if the first preference is a given candidate
                if (preferences[i][0] == candidates[j].name)
                {
                    // increase the number of votes
                    candidates[j].votes++;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    int even_pass_mark;
    int odd_pass_mark;

    if (voter_count % 2 == 0)
    {
        // get the value of half the total votes
        even_pass_mark = voter_count / 2;

        string winner;
        int winner_count = 0;
        // loop throuth candidates
        for (int i = 0; i < candidate_count; i++)
        {
            // check  if the current candidate vote is higher than the fifty percent mark
            if (candidates[i].votes >= even_pass_mark)
            {
                // assign winner to a name
                winner = candidates[i].name;
                // store winner vote
                winner_count = candidates[i].votes;
                printf("winner: %s", winner);
                return true;
            }
        }
        return false;
    }

    else
    {
        // get the value of half the total votes
        odd_pass_mark = round(voter_count / 3);

        string winner;
        int winner_count = 0;
        // loop throuth candidates
        for (int i = 0; i < candidate_count; i++)
        {
            // check  if the current candidate vote is higher than the fifty percent mark
            if (candidates[i].votes >= odd_pass_mark)
            {
                // assign winner to a name
                winner = candidates[i].name;
                // store winner vote
                winner_count = candidates[i].votes;
                printf("winner: %s", winner);
                return true;
            }
        }
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = winner_count;

    // loop throuth candidates
    for (i = 0; i < candidate_count; i++)
    {
        if(candidates[i].eliminated == false)
        {
            // check if candidate's vote is less than current minimal value
            if (candidates[i].vote <= min)
            {
                // assign minimal vote value to min
                min = candidates[i].vote;
                return min;
            }
        }
    }
    return 0;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    int tie_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if (candidatesi].vote == min)
            {
                tie_count++;
                if (tie_count == candidate_count)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            if(candidates[i].vote == min)
            {
                candidates[i].eliminated = true;
            }
        }
    }
    return;
}
