#include <cs50.h>
#include <stdio.h>

int recursiv_mario(int height, int space);

//main function - ask for number between 1-8, then callin recursive mario
int main(void)
{
	int numberFromUser;
	do
	{
		numberFromUser = get_int("Enter your number: ");
	} while (numberFromUser <= 0 || numberFromUser > 8);
	recursiv_mario(numberFromUser, 0);
}

//recieve the height of the peramid, with a space. space++, height-- in the recursiv act.
int recursiv_mario(int height, int space)
{
	if (height == 0)
	{
		return 0;
	}

	recursiv_mario(height - 1, space + 1);

	for (int i = 0; i < space; i++)
	{
		printf(" ");
	}
	for (int i = 0; i < height; i++)
	{
		printf("#");
	}
	printf("  ");
	for (int i = 0; i < height; i++)
	{
		printf("#");
	}
	printf("\n");
	return 0;
}