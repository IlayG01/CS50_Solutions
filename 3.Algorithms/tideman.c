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
	int intensity;
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
void swap(pair* xp, pair* yp);
void lock_pairs(void);
int circle_check(int winner, int loser);
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
		// ranks[i] is voter's ith+1 preference
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
	if (name)  // no null
	{
		for (int index = 0; index < candidate_count; index++)  //travel candidates array
		{
			if (!strcmp(candidates[index], name))  //if name is on candidates(string) array
			{
				ranks[rank] = index;
				return true;
			}
		}
	}
	return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
	for (int i = 0; i < candidate_count - 1;
		i++)  // travel the array of ranks, starting with the best reference index stop at the last.
	{
		for (int j = i; j < candidate_count - 1; j++)
		{
			preferences[ranks[i]][ranks[j + 1]]++; //line of candidate gets +1 where needed
		}
	}
	return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
	int index = 0;
	for (int i = 0; i < candidate_count; i++)
	{
		for (int j = 0; j < candidate_count; j++)
		{
			if (preferences[i][j] > preferences[j][i])  //ith wins jth in head to head fight
			{
				pairs[index].winner = i;
				pairs[index].loser = j;
				pairs[index].intensity = preferences[i][j] - preferences[j][i];
				pair_count++;
				index++;
			}
			else
			{
				continue;
			}
		}
	}
	return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
	int max_idx;

	// One by one move boundary of unsorted subarray 
	for (int i = 0; i < pair_count - 1; i++)
	{
		// Find the minimum element in unsorted array 
		max_idx = i;
		for (int j = i + 1; j < pair_count; j++)
		{
			if (pairs[j].intensity > pairs[max_idx].intensity)
			{
				max_idx = j;
			}
		}

		// Swap the found maximum element with the first element 
		swap(&pairs[max_idx], &pairs[i]);
	}
	return;
}

void swap(pair* xp, pair* yp)
{
	pair temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
	for (int i = 0; i < pair_count; i++) // travel the pairs
	{
		if (circle_check(pairs[i].winner, pairs[i].loser)) // check no circles is created
		{
			locked[pairs[i].winner][pairs[i].loser] = true;
		}
	}
	return;
}

int circle_check(int winner, int loser)
{
	if (loser == winner)
	{
		return 0;
	}

	for (int i = 0; i < candidate_count; i++)
	{
		if (locked[loser][i])  //check if got some locked
		{
			return circle_check(winner, i);
		}
	}

	return 1;
}

// Print the winner of the election
void print_winner(void)
{
	for (int i = 0; i < candidate_count; i++)
	{
		int counter = 0; // aim to count candidate_count falses
		for (int j = 0; j < candidate_count; j++)
		{
			if (!locked[j][i])
			{
				counter++;
			}
		}
		if (counter == candidate_count)
		{
			printf("%s\n", candidates[i]);
		}
	}
	return;
}