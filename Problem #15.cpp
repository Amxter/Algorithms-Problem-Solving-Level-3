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
			arr[i][j] = RandomNumber(0, 10);


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

 
short CountNumberInMatrix(int arr[3][3], int num, short Rows, short Cols)
{
	int counter = 0;
	for (short i = 0; i < Rows; i++)
	{
		for (short j = 0; j < Cols; j++)
		{
			if (arr[i][j] == num)
				counter++;
		}
		 
	}
	return counter; 


}


int main()
{

	srand((unsigned)time(NULL));
	 int Matrix1[3][3]  ;



	cout << "Matrix Number 1 : " << endl;
	FillMatrixWithRandomNumbers(Matrix1, 3, 3);
	PrintMatrix(Matrix1, 3, 3);

	int Number = 0 ;

	cout << "\nEnter the number to count in matrix? ";
	cin >> Number ;
	cout << "\nNumber " << Number << " count in matrix is ";
	cout << CountNumberInMatrix(Matrix1, Number, 3, 3);
	system("pause>0");
 

 
}