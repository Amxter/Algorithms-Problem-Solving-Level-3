 

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
void ReadRandomNumber(int arr[3][3] , int Rows , int cols )
{
    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = RandomNumber(1, 100);
        }
    }
}

void PrintMatrix(int arr[3][3], int Rows, int cols)
{

    for (int i = 0; i < Rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << setw(3) << arr[i][j] << "\t";
        }
        cout << endl;
    }
}

int main()
{
    int arr[3][3];

    srand((unsigned)time(NULL)); 
    ReadRandomNumber( arr ,3,3 );
    PrintMatrix ( arr,3,3 );

}

 