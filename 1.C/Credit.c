#include <stdio.h>
#include <cs50.h>
#include <math.h>

int lengthCalculate(long credit);
bool lengthValidation(int length);
bool checksumValidation(long credit, int length);
void companyTracker(int firstTwoNumbers, int length);

int main(void)
{
	long credit;
	credit = get_long("Enter your credit card number \n");
	int length = lengthCalculate(credit);
	if (!lengthValidation(length))
	{
		printf("INVALID\n"); //length is not valid
		return 0;
	}
	if (checksumValidation(credit, length)) //check the checksum by luhn algorithm
	{
		int firstTwoNumbers = (credit / pow(10, length - 2));
		companyTracker(firstTwoNumbers, length);
	}
	else
	{
		printf("INVALID\n");
		return 0;
	}

}

int lengthCalculate(long credit)
{
	int length = 0;
	while (credit != 0)
	{
		credit /= 10;
		++length;
	}
	return length;
}

bool lengthValidation(int length)
{
	if (length == 13 || length == 15 || length == 16)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool checksumValidation(long credit, int length)
{
	int sum = 0;
	//Luhn's Algorithm 
	for (int i = 0; i < length; i++, credit /= 10)
	{
		if ((length - i) % 2 == 0)  //other digits
		{
			sum += credit % 10;
		}
		else //even digit
		{
			if ((credit % 10) * 2 >= 10)  //2 digits
			{
				int holder = (credit % 10) * 2;
				sum += holder / 10 + holder % 10;
			}
			else
			{
				sum += (credit % 10) * 2;
			}
		}
		// printf("%i\n",sum);
	}

	//Validating the card
	if (sum % 10 == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void companyTracker(int firstTwoNumbers, int length)
{
	//checking the company of the credit card
	//VISA(4) or MASTERCARD(51,52,53,54,55) or AMEX(34,37) or INVALID
	if (((firstTwoNumbers / 10 == 4) && (length == 13)) || ((firstTwoNumbers / 10 == 4) && (length == 16)))
	{
		printf("VISA\n");
	}
	else if (((firstTwoNumbers == 34) && (length == 15)) || ((firstTwoNumbers == 37) && (length == 15)))
	{
		printf("AMEX\n");
	}
	else if (((firstTwoNumbers == 51) && (length == 16)) || ((firstTwoNumbers == 52) && (length == 16)) || ((firstTwoNumbers == 53)
		&& (length == 16)) || ((firstTwoNumbers == 54) && (length == 16)) || ((firstTwoNumbers == 55) && (length == 16)))
	{
		printf("MASTERCARD\n");
	}
	else
	{
		printf("INVALID\n");
	}
}