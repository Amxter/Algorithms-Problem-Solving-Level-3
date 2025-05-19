#include <string>
#include <iostream>
#include <vector>
using namespace std;
vector<string> SplitString(string S1, string Delim)
{


}
string ReadString()
{
	string S1;
	cout << "Please Enter Your String?\n";
	getline(cin, S1);
	return S1;
}
short CountWords(string S1)
{
	string delim = " "; // delimiter
	short Counter = 0;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			Counter++;
		}
		//erase() until positon and move to next word.
		S1.erase(0, pos + delim.length());
	}
	if (S1 != "")
	{
		Counter++; // it counts the last word of the string.
	}
	return Counter;
}
 
int main()
{
	string S1 = ReadString();
	cout << "\nThe number of words in your string is: ";
	cout << CountWords(S1);
	system("pause>0");
}