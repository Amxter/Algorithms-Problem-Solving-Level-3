#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
int RandomNumber(int From, int To)
{
	//Function to generate a random number
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}
void FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short
	Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			arr[i][j] = RandomNumber(1, 100);
		}
	}
}
void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << "\n";
	}
}
 
int ColSum(int arr[3][3], short colNumber, short Cols)
{
	int Sum = 0;
	for (short j = 0; j <= Cols - 1; j++)
	{
		Sum += arr[j][colNumber];
	}
	return Sum;
}
void ColSumInArray(int Sum[3], int arr[3][3], short Rows, short Cols)
{

	for (short i = 0; i < Cols; i++)
	{
		Sum[i] = ColSum(arr, i, Rows);

	}
}
void PrintEachColsSum(int Sum[3] , int arr[3][3] , short Rows , short Cols )
{
	ColSumInArray(Sum, arr, Rows, Cols);
	cout << "\nThe the following are the sum of each row in the matrix:\n";
		
		for (short i = 0; i < Cols; i++)
		{
			cout << " Col " << i + 1 << " Sum = " << ColSum(arr, i, Rows) << endl;
				
		}
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int arr[3][3] ;
	int Sum[3]    ;

	FillMatrixWithRandomNumbers(arr, 3, 3);
	cout << "\nThe following is a 3x3 random matrix:\n";
	PrintMatrix(arr, 3, 3);

	PrintEachColsSum(Sum , arr, 3, 3);
	system("pause>0");
}