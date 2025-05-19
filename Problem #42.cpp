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

string SwipWord(string S1, string FindWord, string Word)
{
	short LocationWord;


	while ( S1.find(FindWord) != std::string::npos )
	{ 
		LocationWord = S1.find(FindWord);
		S1.erase(LocationWord, FindWord.length()   );
		S1.insert(LocationWord, Word);
	}
	return S1;
}


int main()
{
	string S1 = "buyhb Amer ionnin oninioi; Amer non";
	cout << SwipWord(S1, "Amer", "x");

	system("pause>0");
}