#include <string>
#include <iostream>
#include <vector>
using namespace std;
string ReadString()
{
	string S1;
	cout << "Please Enter Your String?\n";
	getline(cin, S1);
	return S1;
}
 
string TrimRight(string S1)
{
	short SizeS1 = S1.size() -1  ;
	
	 
	while (S1[SizeS1] == ' ')
	{
		
			 
		if (S1[SizeS1] == ' ')
		{ 
			S1.erase(SizeS1);
		}
		else
		{
			return S1; 
		}
			--SizeS1;
	} 

	return S1;

}

string TrimLeft(string S1)
{ 
	while (S1[0] == ' ')
	{
		if (S1[0] == ' ')
		{
			S1.erase(0 , 1 );
		}
		else
		{
			return S1;
		}
		 ;
	}

	return S1;

}


string Trim(string S1)
{
	return (TrimLeft(TrimRight(S1)));
}


int main()
{
 string S1 =	ReadString();  
 //cout << TrimRight(S1) << "xxx" << endl;
 cout << TrimLeft(S1) << "xxx" << endl;

		system("pause>0");
}