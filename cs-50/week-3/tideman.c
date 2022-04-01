#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// https://cs50.harvard.edu/x/2022/psets/3/tideman/

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
    for(int j = 0; j < candidate_count; j++)
    {
        if(strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            return true;
        } 
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // every voter rates all candidates
    for(int i = 0; i < candidate_count; i++)
    {
        for(int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for(int i = 0; i < candidate_count; i++) {
        for(int j = i + 1; j < candidate_count; j++) {
            if(preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            } else if(preferences[i][j] < preferences[j][i]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

int preference(int i) {
    pair p = pairs[i];
    return preferences[p.winner][p.loser];
}

int preferenceAux(pair aux[], int i) {
    pair p = aux[i];
    return preferences[p.winner][p.loser];
}

void exch(int i, int j) {
    pair tmp = pairs[i];
    pairs[i] = pairs[j];
    pairs[j] = tmp;
}

void qsort3way(int lo, int hi) {
    if(hi <= lo) return;
    
    int lt = lo, gt = hi;
    int v = preference(lo);
    
    int i = lo + 1;
    while(i <= gt) {
        int p = preference(i);
        if(p > v) { exch(lt++, i++); }
        else if(p < v) { exch(i, gt--); }
        else i++;
    }

    qsort3way(lo, lt - 1);
    qsort3way(gt + 1, hi);
}

void merge(pair aux[], int lo, int mid, int hi) {
    // fill in the aux array
    for(int i = lo; i <= hi; i++) { aux[i] = pairs[i]; }

    int i = lo; int j = mid + 1;
    for(int k = lo; k <= hi; k++) {
        if(i > mid) { pairs[k] = aux[j++]; }
        else if(j > hi) { pairs[k] = aux[i++]; }
        else if (preferenceAux(aux, i) < preferenceAux(aux, j)) {
            pairs[k] = aux[j++];
        } else {
            pairs[k] = aux[i++];
        }
    }
}

void merge_sort(pair aux[], int lo, int hi) {
    if(hi <= lo) return;
    int mid = lo + (hi - lo) / 2;
    merge_sort(aux, lo, mid);
    merge_sort(aux, mid + 1, hi);

    // shorcurcuit
    if(preference(mid) <= preference(mid + 1)) return;
    merge(aux, lo, mid, hi);
}

void merge_sort_all(void) {
    pair aux[pair_count];
    merge_sort(aux, 0, pair_count - 1);
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    qsort3way(0, pair_count - 1);
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for(int i = 0; i < pair_count; i++) {
        bool acyclic = true;
        // check that there is no loop
        for(int j = 0; j <= i; j++) {
            // check that no of prev pairs contain 
            // pairs[i].looser == pairs[j].winner
            if(pairs[i].loser == pairs[j].winner || pairs[i].winner == pairs[j].loser) {
                acyclic = false;
            }
        }

        if(acyclic) {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
// Prints all winners
void print_winner(void)
{
    for(int i = 0; i < candidate_count; i++) {

        // print all winners that have falses in a locked graph that equals to amount of candidates
        int count = 0;
        for(int j = 0; j < candidate_count; j++) {
            if(!locked[i][j]) count++;
        }

        if(count == candidate_count) printf("%s\n", candidates[i]);
    }

    return;
}