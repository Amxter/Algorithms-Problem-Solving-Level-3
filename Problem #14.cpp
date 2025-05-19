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
			arr[i][j] = RandomNumber(0, 1);


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

bool ISScalarMatrix(int Matrix1[3][3], int Rows, int Cols)
{

	for (short i = 0; i < Rows; i++)
	{

		
		for (short j = 0; j < Cols; j++)
		{
			if (i != j)
			{
				if (Matrix1[i][j] != 0)
					return  false;
			}
			else
			{
				  
				if (Matrix1[i][j] != Matrix1[0][0])
					return  false;
			}


		}
	}
	return  true;
}




int main()
{

	srand((unsigned)time(NULL));
	int Matrix1[3][3] = { { 9,0,0 } , { 0,9,0 } , { 0,0,9 } };



	cout << "Matrix Number 1 : " << endl;
	//FillMatrixWithRandomNumbers(Matrix1, 3, 3);

	PrintMatrix(Matrix1, 3, 3);

	cout << endl << endl;




	if (ISScalarMatrix(Matrix1, 3, 3))
		cout << "Matrixs is Scalar . " << endl;
	else
	{
		cout << "Matrixs is not Scalar . " << endl;
	}
	system("pause>0");
}