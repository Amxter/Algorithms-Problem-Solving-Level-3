


#include <iostream>
#include <string>
#include <iomanip>


using namespace std;

void PrintMatrix(int arr[3][3], short Rows, short Cols)
{
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			//printf(" %0*d ", 2, arr[i][j]);
			cout << setw(3) << arr[i][j] << " ";
		}
		cout << "\n";
	}
}


short MinNumberInMatrix(int arr[3][3], short Rows, short Cols)
{
	int Num = arr[0][0];
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{

			if (Num > arr[i][j])
				Num = arr[i][j];
		}

	}

	return Num; 

}

short MaxNumberInMatrix(int arr[3][3], short Rows, short Cols)
{
	int Num = arr[0][0];
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{

			if (Num < arr[i][j])
				Num = arr[i][j];
		}

	}

	return Num;

}
 



int main()
{
	int Matrix1[3][3] = { {711,5,12},{22,20,1},{1,11,9} };
 

	cout << "\nMatrix1:\n";
	PrintMatrix(Matrix1, 3, 3);
 

	cout << "\nMinimum Number is: ";
	cout << MinNumberInMatrix(Matrix1, 3, 3);
	
	
	cout << "\n\nMax Number is: ";
	cout << MaxNumberInMatrix(Matrix1, 3, 3);
	system("pause>0");
}
 
 