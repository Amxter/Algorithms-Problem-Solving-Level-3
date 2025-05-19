#include <string>
#include <iostream>
#include <vector>
using namespace std;


string JoinString(vector<string> vString, string Delim)
{
	string S1 = "";
	for (string& s : vString)
	{
		S1 = S1 + s + Delim;
	}
	return S1.substr(0, S1.length() - Delim.length());

}


string JoinString( string Arr[]  , int Langth, string Delim)
{
	string S1 = "";
	for (int i = 0 ; i < Langth   ; i++  )
	{
		S1 = S1 + Arr[i] + Delim;
	}
	return S1.substr(0, S1.length() - Delim.length());

}


int main()
{
	vector<string> vString = { "Mohammed","Faid","Ali","Maher" };
	string ArrString[] = {"Mohammed","Faid","Ali","Maher"};
	cout << "\nVector after join: \n";
	cout << JoinString(ArrString  , 4, ",,,");
	system("pause>0");
}