
#include <string>
#include <iostream>
using namespace std;
string ReadString()
{
	string S1;
	cout << "\nPlease Enter Your String?\n";
	getline(cin, S1);
	return S1;
}
char ReadChar()
{
	char Ch1;
	cout << "\nPlease Enter a Character?\n";
	cin >> Ch1;
	return Ch1;
}
short CountLetter(string S1, char Letter , bool x = true )
{
	short Counter = 0;
	for (short i = 0; i < S1.length(); i++)
	{
		if(x)
		{ 
		   if (S1[i] == Letter)
			Counter++;
		}
		else
		{
			if( tolower(S1[i]) == tolower(Letter) )
				Counter++;
		}
	}
	return Counter;
}

char InvertLetterCase(char char1)
{
	return isupper(char1) ? tolower(char1) : toupper(char1);
}

int main()
{
	string S1 = ReadString();
	char Ch1 = ReadChar();
 
	cout << "\nLetter \'" << Ch1 << "\' Count = " << CountLetter(S1, Ch1) ;
	printf("\nLetter \'%c\' or \'%c\' Count = %d", Ch1, InvertLetterCase(Ch1), CountLetter(S1, Ch1, 1 ) )  ;
	 
	system("pause>0");
}