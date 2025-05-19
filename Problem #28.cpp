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
string InvertLetterAllString(string st )
{

	for (int i = 0; i < st.length(); i++)
	{

		st[i] = isupper(st[i]) ? tolower(st[i]) : toupper(st[i]);

	}

	return st ;

}
int main()
{
	string st = ReadString();
	cout << "\nChar after inverting String :\n";
	st = InvertLetterAllString(st );
	cout << st << endl;
	system("pause>0");
}