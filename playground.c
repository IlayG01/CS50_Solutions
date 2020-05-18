#include <stdio.h>

void function(int[] A, int length, int num)
{
	int sum;
	int num_of_digits;
	int holder = num;

	int index;
	int* pindex = &index;
	while (holder > 0)
	{
		holder = holder / 10;
		num_of_digits++;
	}
	for (int i = 0; i < num_of_digits; i++)
	{
		sum = sum + num % 10;
		num = num / 10;
	}
	for (int j = 0; j < length; j++)
	{
		if (A[j] == sum)
		{
			index = j;
			return pindex;
		}
	}
	return -1;
}

void main()
{
	int[] A = { 19, 6, 39, 21, 97, 40, 11, 21, 38, 40};
	length = 10;
	num = 678;
	int* result = function(A, length, num);
	printf("the number is %i", *result);
}