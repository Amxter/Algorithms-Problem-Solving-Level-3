#include <string>
#include <iostream>
using namespace std;
string ReadString()
{
	string S1;
	cout << "Please Enter Your String?\n";
	getline(cin, S1);
	return S1;
}

short HowUpperLetterInString(string st)
{
	short Counter = 0;
	for (short i = 0; i < st.length() ; i++)
	{
		if (isupper(st[i]))
			++Counter;
	}

	return Counter; 
}
 
short HowLowerLetterInString(string st)
{
	short Counter = 0;
	for (short i = 0; i < st.length(); i++)
	{
		if (islower(st[i]))
			++Counter;
	}

	return Counter;
}

int main()
{
	string st = ReadString();
	cout << "\n  String Length : " << st.length() << endl  ;
	cout << "Upper is : " << HowUpperLetterInString(st) << endl;
	cout << "Lower is : " << HowLowerLetterInString(st) << endl;
	system("pause>0");
}