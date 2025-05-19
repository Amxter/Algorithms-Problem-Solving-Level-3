#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
const string ClientsFileName = "FileName.txt";


struct sClient
{
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance;
	bool MarfDeletClient = false;

};
 
string ReadClientAccountNumber()
{
	string AccountNumber;
	cout << "Pleas Enter Account Number ?? ";
	cin >> AccountNumber;
	return AccountNumber;

}

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

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")

{
	sClient Client;
	vector<string> vClientData;
	vClientData = SplitString(Line, Seperator);
	Client.AccountNumber = vClientData[0];
	Client.PinCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);//cast string to double

	return Client;
}
 
vector <sClient> LoadCleintsDataFromFile(string FileName)
{
	vector <sClient> vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);//read Mode
	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLinetoRecord(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}
	return vClients;
}

bool FindClientByAccountNumber(string AccountNumber, sClient &Client , vector <sClient> vClient )
{
	for (sClient C : vClient)
	{
	
		if (C.AccountNumber == AccountNumber )
		{
			Client = C ;

				return true;
		}

	}

	return false ;
}

void PrintClientCard(sClient Client)
{
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code : " << Client.PinCode;
	cout << "\nName : " << Client.Name;
	cout << "\nPhone : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")

{
	string stClientRecord = "";
	stClientRecord += Client.AccountNumber + Seperator;
	stClientRecord += Client.PinCode + Seperator;
	stClientRecord += Client.Name + Seperator;
	stClientRecord += Client.Phone + Seperator;
	stClientRecord += to_string(Client.AccountBalance);
	return stClientRecord;
}

void MarkDeletAccountNumber(string AccountNumber , vector <sClient> &vClient )
{

	for (sClient &c : vClient)
	{
		if (c.AccountNumber == AccountNumber)
		{
			c.MarfDeletClient = true;
			 
		}

	}




}

void SaveAllClinetInFile( vector <sClient>  vClient)
{
		fstream MyFile;
		MyFile.open(ClientsFileName, ios::out);//overwrite
		string DataLine;
		if (MyFile.is_open())
		{
			for (sClient &C : vClient)
			{
				if ( C.MarfDeletClient == false  )
				{
						DataLine = ConvertRecordToLine(C);
					MyFile << DataLine << endl;
				}
			}

			MyFile.close();
		}
		 
	}

void DeletClinetInFile(string AccountNumber , sClient Client ,vector <sClient> vClient )
{

	if (FindClientByAccountNumber(AccountNumber, Client, vClient))
	{
		PrintClientCard(Client);
	 
		char ch;
		cout << "\n\n Do you Delet Client With Account Number ";
		cout << Client.AccountNumber << " Y/N ?? ";
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
		{
			 
			MarkDeletAccountNumber(AccountNumber, vClient );
			SaveAllClinetInFile(vClient);


			 vClient = LoadCleintsDataFromFile(ClientsFileName);

			cout << "\n\nClient Deleted Successfully.";

		}

	}
	else
	{
		cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";

	}



}

 
int main()
{

	sClient Client;
	vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName); 
	string AccountNumber = ReadClientAccountNumber();
	DeletClinetInFile(AccountNumber , Client , vClient );




	system("pause>0");
	return 0;
}