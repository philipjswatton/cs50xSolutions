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
    /*take:

    a) integer voter denoting the voter number
    b) integer rank denoting the candidate rank for voter i (i.e. 1st pref, 2nd pref, etc)
    c) string name denoting the name given by the voter


    need to:
    a) check that the name exists
    b) if so, edit the preferences array accordingly
    */

    //check existence by cycling over all candidate names

    int candidateID = -1; //initialise at impossible value

    for (int k = 0; k < candidate_count; k++) {
        if (strcmp(name, candidates[k].name) == 0) { //returns 0 if there is a match
            candidateID = k; //replace candidate ID with the array position of candidate k
        }
    }

    if (candidateID != -1) {
        preferences[voter][rank] = candidateID; //the (rank) preference for the given voter is stored as candidate k
        return true;
    } else {
        return false;
    }
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    /*task:
    cycle through the 'preferences' array to update candidates[i].votes

    while cycling:
    a) look at first preference
    b) if eliminated, move to next preference
    c) repeat until a non-eliminated preference is found
    d) add a vote to that preference
    */

    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int choice = preferences[i][j]; //get preference j for
            if (candidates[choice].eliminated == false) { //if candidate is not eliminated, do this stuff which includes a break for the loop
                candidates[choice].votes += 1;
               // printf("candidate %i has %i votes\n", choice, candidates[choice].votes); //diagnostic tool
                break; //end the for loop as no longer necessary to keep cycling through
            }
        }
    }


    //return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    /*Task:
    a) calculate votes for candidates as a share of all votes
    b) if one candidate has a vote share higher than 50%, that candidate is declared as the winner and this function should return true

    Breakdown:
    1) get sum of all votes (because there are no empty votes, this is actually just the n of voters right)
    2) cycle through candidates to see if any of their vote shares divided by the n of voters is > 0.5
    3) if so, print that candidate's name and return true
    4) if no winner, return false*/



    int winner = 0; //initialise this value - if no winner, won't change, not useful for declaring winner but useful for returning false

    for (int i = 0; i < candidate_count; i++) {

        /*int calc = candidates[i].votes / voter_count; //diangostic tool
        printf("%i\n", calc);*/

        if (((double) candidates[i].votes / voter_count) > 0.5) {
            printf("%s\n", candidates[i].name);
            winner = 1;
        }
    }

    if (winner == 1) {
            return true;
    } else {
        return false;
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    /*Task:
    a) cycle through (remaining?) candidates list
    b) find candidate with lowest number of votes
    c) return int with lowest n of votes*/

    int min = 0;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > min && candidates[i].eliminated == false) {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    /*Task:
    a) Take minimum score
    b) Count number of *remaining* candidates whose vote is equal to the minimum
    c) If the number of *remaining* candidates with this vote share is equal to the number of remaining candidates overall, return true
    d) Otherwise, return false*/
    
    int remaining = 0;
    int atMin = 0;
    
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].eliminated == false) {
            remaining ++; //if a candidate is still in the election, add 1 to the count of remaining candidates
            if (candidates[i].votes == min) {
                atMin++; //if a candidate is still in the election and their vote count is equal to the minimum, add 1 to the count of remaining candidates at the mimum vote share
            }
        }
    }
    
    if (remaining == atMin) {
        return true;
    } else {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    /*Task:
    a) Check if candidate's vote share is equal to minimium votes
    b) If so, eliminate them*/
    
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min) {
            candidates[i].eliminated = true;
        }
    }
}
