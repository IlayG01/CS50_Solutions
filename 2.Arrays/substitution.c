#include<stdio.h>
#include<ctype.h>
#include<math.h>
#include<cs50.h>
#include<string.h>

bool isDuplicationInKey(string key);

int main(int argc, char* argv[])
{
	if (argc != 2) //cheking valid numbers of params
	{
		printf("Usage: ./substitution key\n");
		return 1;
	}
	else if (strlen(argv[1]) != 26) //checking length of key param
	{
		printf("Key must contain 26 characters.\n");
		return 1;
	}
	else // the algorithm
	{
		int subtitution[26];  // array holding the subtitution needed for each letter, a/A=index0 and so...
		for (int i = 0, j = 65; i < 26; i++, j++)  // converting the key to upper case only, and to numbers so we can find the subtitution.
		{
			argv[1][i] = (int)toupper(argv[1][i]);  // the convertion
			subtitution[i] = j - (int)toupper(argv[1][i]);  //the subtitution made
			if (!(argv[1][i] >= 65 && argv[1][i] <= 90))   //defensive programming on the input - no invalid characters
			{
				printf("Key must contain 26 characters.\n");
				return 1;
			}
		}

		if (isDuplicationInKey(argv[1]))
		{
			printf("Key must contain 26 different characters.\n");
			return 1;
		}
		string textToEncrypt = get_string("plaintext: "); // input from user

		for (int index = 0, length = strlen(textToEncrypt); index < length;
			index++) // cyper making, with if-tree to make sure the upper/lower is taken care
		{
			if ((int)textToEncrypt[index] >= 97 && (int)textToEncrypt[index] <= 122) //upper case senario
			{
				int mapper = (int)textToEncrypt[index] - 97;
				textToEncrypt[index] -= subtitution[mapper];
			}
			if ((int)textToEncrypt[index] <= 90 && (int)textToEncrypt[index] >= 65) //lower case senario
			{
				int mapper = (int)textToEncrypt[index] - 65;
				textToEncrypt[index] -= subtitution[mapper];
			}
		}

		printf("ciphertext: %s\n", textToEncrypt);
		return 0;
	}
}


bool isDuplicationInKey(string key)
{
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			if (i != j && key[i] == key[j])
			{
				return true;
			}
		}
	}
	return false;
}