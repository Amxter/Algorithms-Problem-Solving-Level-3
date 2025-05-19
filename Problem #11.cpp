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

int SumMatrixs(int arr[3][3], short Rows, int Cols)
{

	int Sum = 0;
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			Sum += arr[i][j];


		}
	}
	return Sum;
}

void EqualiyeMatrcis(int SumMatrxe1, int SumMatrxe2 )
{

	if (SumMatrxe1 == SumMatrxe2)
		cout << "The matrices are equal" << endl;
	else
		cout << "The matrices are not equal" << endl;

}

int main()
{
 
	srand((unsigned)time(NULL));
	int arr[3][3];
	int arr1[3][3];

	FillMatrixWithRandomNumbers(arr, 3, 3);
	PrintMatrix(arr, 3, 3);
	cout << endl << endl;
	FillMatrixWithRandomNumbers(arr1, 3, 3);
	PrintMatrix(arr1, 3, 3);
	cout << endl << endl;
	//cout << "Sum Matrix is : " << SumMatrixs(arr, 3, 3);
	int   SumMatrxe1 = SumMatrixs(arr, 3, 3);
	int   SumMatrxe2 = SumMatrixs(arr1, 3, 3) ;
	EqualiyeMatrcis(SumMatrxe1, SumMatrxe2);

	system("pause>0");
}