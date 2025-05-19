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

void FillMatrixWithRandomNumbers(int arr[3][3], short Rows, short Cols)

{
	int x = 1;
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			arr[i][j] = RandomNumber(1, 10);
		
				 
		}
	}
}
void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			cout << setw(2) << arr[i][j] << "    ";
		}
		cout << "\n";
	}
}

void Reusolt(int arr[3][3], int arr1[3][3], int arr2[3][3] , short Rows, short Cols)
{
	int x = 0;
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols ; j++)
		{
		
			arr2[i][j] = arr[i][j] * arr1[i][j];

		}
	}
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));
	int arr[3][3];
	int arr1[3][3];
	int arr2[3][3];
	FillMatrixWithRandomNumbers(arr, 3, 3);
	FillMatrixWithRandomNumbers(arr1, 3, 3);
	cout << endl<< endl ;
	PrintMatrix(arr, 3, 3);
	cout << endl << endl;
	PrintMatrix(arr1, 3, 3);


	cout << endl << endl;
	Reusolt(arr, arr1, arr2, 3, 3);
	PrintMatrix(arr2, 3, 3);
	system("pause>0");
}