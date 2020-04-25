#include<stdio.h>
#include<cs50.h>
#include<string.h>
#include<math.h>

int colemanLiauFormula(int letters, int words, int sentences); //function decleration
void outputFromFormula(int grade); //function decleration

int main(void)
{
	//counters
	int lettersCounter = 0;
	int wordsCounter = 0;
	int sentencesCounter = 0;
	//getting input from user
	string text = get_string("Enter your text : ");
	int textLength = strlen(text);
	//algorithm for counting
	for (int i = 0, lettersBetweenSpaces = 0, wordsBetweenSentences = 0; i < textLength; i++)
	{
		if (((65 <= (int)text[i]) && ((int)text[i] <= 90)) || ((97 <= (int)text[i])
			&& ((int)text[i] <= 122)))  // letters counter ++, lettersbetweenspaces ++
		{
			lettersCounter++;
			lettersBetweenSpaces++;
		}
		if ((int)text[i] == 32)  // words counter ++ , words between sentences ++ ,lettersBetweenSpaces initialize
		{
			if (lettersBetweenSpaces >= 1)
			{
				wordsCounter++;
				wordsBetweenSentences++;

			}
			lettersBetweenSpaces = 0;
		}
		// ((int)text[i] == 59)
		if (((int)text[i] == 46) || ((int)text[i] == 33) || ((int)text[i] == 63))  // sentences counter ++, wordsbetweensentences initialize
		{
			if (lettersBetweenSpaces >= 1)
			{
				sentencesCounter++;
				wordsCounter++;
			}
			wordsBetweenSentences = 0;
			lettersBetweenSpaces = 0;

		}

	}
	// printf("Letters --> %i , Words --> %i , Sentences --> %i\n", lettersCounter, wordsCounter, sentencesCounter);
	outputFromFormula(colemanLiauFormula(lettersCounter, wordsCounter,
		sentencesCounter)); //call output function and pass the formula returtning value to it.

}

int colemanLiauFormula(int letters, int words, int sentences)  //little math
{
	int numberOfLettersPer100W = 100 / (float)words * letters;
	int numberOfSentencesPer100 = 100 / (float)words * sentences;
	int index = round((0.0588 * numberOfLettersPer100W) - (0.296 * numberOfSentencesPer100) - 15.8);
	return index;
}

void outputFromFormula(int grade) // if tree
{
	if (grade < 1)
	{
		printf("Before Grade 1\n");
	}
	else if (grade > 16)
	{
		printf("Grade 16+\n");
	}
	else
	{
		printf("Grade %i\n", grade);
	}
}