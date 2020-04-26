#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates - constant vriable
#define MAX 9

// Candidates have name and vote count
typedef struct
{
	string name;
	int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
	// Check for invalid usage
	if (argc < 2)
	{
		printf("Usage: plurality [candidate ...]\n");
		return 1;
	}

	// Populate array of candidates
	candidate_count = argc - 1;
	if (candidate_count > MAX)
	{
		printf("Maximum number of candidates is %i\n", MAX);
		return 2;
	}
	for (int i = 0; i < candidate_count; i++)  //initialize the array of candidates
	{
		candidates[i].name = argv[i + 1];
		candidates[i].votes = 0;
	}

	int voter_count = get_int("Number of voters: ");

	// Loop over all voters
	for (int i = 0; i < voter_count; i++)
	{
		string name = get_string("Vote: ");

		// Check for invalid vote
		if (!vote(name))
		{
			printf("Invalid vote.\n");
		}
	}

	// Display winner of election
	print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
	for (int index = 0; index < MAX; index++)
	{
		if (candidates[index].name)  // no null
		{
			if (!strcmp((candidates[index].name), name))  //if they similar
			{
				candidates[index].votes++;
				return true;
			}
		}
	}
	return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
	int biggest = 0;
	for (int index = 0; index < MAX; index++)  //biggest value of votes
	{
		if (candidates[index].votes > biggest)
		{
			biggest = candidates[index].votes;
		}
	}
	for (int index = 0; index < MAX; index++)  //everyone who have it is winning and pronnounced
	{
		if (candidates[index].votes == biggest)
		{
			printf("%s\n", candidates[index].name);
		}
	}
	return;
}