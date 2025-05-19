#include <string>
#include <iostream>
#include <vector>
using namespace std;
vector<string> SplitString(string S1, string Delim)
{
	vector<string> vString;
	short pos = 0;
	string sWord; // define a string variable
	// use find() function to get the position of the delimiters
	while ((pos = S1.find(Delim)) != std::string::npos)
	{
		sWord = S1.substr(0, pos); // store the word
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		S1.erase(0, pos + Delim.length());
	}
	if (S1 != "")
	{
		vString.push_back(S1); // it adds last word of the string.
	}
	return vString;
}

string JoinString(vector<string> vString, string Delim)
{
	string S1;
	for (string& s : vString)
	{
		S1 = S1 + s + Delim;
	}
	return S1.substr(0, S1.length() - Delim.length());
}
string LowerAllString(string S1)
{
	for (short i = 0; i < S1.length(); i++)
	{
		S1[i] = tolower(S1[i]);
	}
	return S1;
}



string ReplaceWordInStringUsingSplit(string S1, string StringToReplace, string sRepalceTo, bool MatchCase = true)
{
	vector <string> vWords = SplitString(S1, " ");

	for (string& S1 : vWords)
	{
		if (MatchCase)
		{
			if (S1 == StringToReplace)
				S1 = sRepalceTo;

		}
		else
		{

			if (LowerAllString(S1) == LowerAllString(StringToReplace))
				S1 = sRepalceTo;

		}



	}

	return JoinString(vWords, " ");
}


int main()
{
	string S1 = "buyhb amer ionnin oninioi; Amer non";

	cout << ReplaceWordInStringUsingSplit(  S1, "Amer" ,  "XX" , false  ) ;

	system("pause>0");
}