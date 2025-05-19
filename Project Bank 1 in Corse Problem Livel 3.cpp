
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};
enum enMainMenueOptions {
    ShowClientList = 1, AddNweClients,
    DeletClient, UpdeatInfoClient
    , FiendClient, eExist
};


const string ClientsFileName = "FileName.txt" ;


void CleanScreen()
{
    system("cls");
}
void HowNumberFromTo(int& Number, int From, int To)
{
    while (Number < From || Number > To)
    {
        cout << "\nWrong : \nPlesea Enter once again Number From " << From << " to " << To << " ??  ";
        cin >> Number;

    }


}
enMainMenueOptions PrintMainMenueuScreen()
{

    int Number = 0;
    cout << "________________________________________________________" << endl;
    cout << "            Main   Menueu   Screen  " << endl;
    cout << "________________________________________________________" << endl;
    cout << "           [1] Show Client List. " << endl;
    cout << "           [2] Add New Client. " << endl;
    cout << "           [3] Delel Client. " << endl;
    cout << "           [4] Update Client Info. " << endl;
    cout << "           [5] Fiend Client. " << endl;
    cout << "           [6] Exit. " << endl;
    cout << "________________________________________________________" << endl;
    cout << "Choose What do you want do you ?? [ 1 to 6 ] ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 6);
    return enMainMenueOptions(Number);

}
bool DoyouMore(string S1)
{
    char ch;

    cout << "\n\n" << S1;
    cin >> ch;

    return (ch == 'y' || ch == 'Y');
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
    Client.AccountBalance = stod(vClientData[4]);//cast string to

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



void PrintClientRecord(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")  Client(s).";


    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (sClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void GoBackToMainScreen();
void ShowAllClientsListScreen(vector <sClient> vClients)
{
    CleanScreen();
    PrintAllClientsData(vClients); 
    GoBackToMainScreen();

}

string ConvertRecorToLine(sClient Client, string  Seperator = "#//#")
{
    string ConvertRecor = "";

    ConvertRecor += Client.AccountNumber + Seperator  ;
    ConvertRecor += Client.PinCode + Seperator;
    ConvertRecor += Client.Name + Seperator;
    ConvertRecor += Client.Phone + Seperator;
    ConvertRecor += to_string(Client.AccountBalance);

    return ConvertRecor;
}
bool FindAccountNumber(vector <sClient> vClients , string AccountNumber )
{
    for (sClient &Client : vClients)
    {
        if (AccountNumber == Client.AccountNumber)
            return true;
    }
    return false ;

}
void ReadNewcliantInfo(sClient &Client)
{
  
    cout << "\nEnter Pin Code ?? ";
    getline(cin >> ws , Client.PinCode);
    cout << "\nEnter Name  ?? ";
    getline(cin, Client.Name);
    cout << "\nEnter Phone ?? ";
    getline(cin, Client.Phone);
    cout << "\nEnter Account Balance ?? ";
    cin >> Client.AccountBalance ;

}
void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}
void ShowAddNweClientsScren(vector <sClient> & vClients)
{
   

    do
    {
    CleanScreen();
    sClient  Client ;
    vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "Please Enter is Info Client : " << endl << endl; 
    cout << "Enter Account Number ?? "; 
    getline( cin >> ws , Client.AccountNumber);
    while (FindAccountNumber(vClients, Client.AccountNumber))
    {
        cout << "\n\n Client wath [ " << Client.AccountNumber << " ] already exists , Enter ather Account NUmber ?? ";
        cin >> Client.AccountNumber; 

    }
    ReadNewcliantInfo(Client);
    AddDataLineToFile(ClientsFileName, ConvertRecorToLine(Client));

        } while (DoyouMore("Client Added Succsaflly , Do you want to Add Client ?? Y/N "));

    GoBackToMainScreen();

}




bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <sClient>& vClients)
{
    for (sClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)

{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for

                DataLine = ConvertRecorToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}
void PrintInfoClient(sClient  Client)
{
    cout << "\n\nThe Folowing are the client Datails" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Account Number  : " << Client.AccountNumber << endl ;
    cout << "Pin code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "--------------------------------------" << endl << endl ;
}
sClient FindInfoClientInvoctor(vector <sClient>  vClients, string AccountNumber)
{
    for (sClient &Client : vClients)
    {
        if (Client.AccountNumber == AccountNumber)
            return Client;

    }

}
void PrintScreen(string Titel )
{

    cout << "\n\n-------------------------------" << endl;
    cout << "        " << Titel  << endl;
    cout << " -------------------------------" << endl;
}
void ShoweDeletClientScreen(vector <sClient>& vClients)
{
 
        CleanScreen();
        sClient  Client;
         
        PrintScreen("Delet Cleint Screen");
        cout << "Enter Account Number ?? ";
        getline(cin >> ws, Client.AccountNumber);
        if (FindAccountNumber( vClients, Client.AccountNumber))
        {
            Client = FindInfoClientInvoctor(vClients, Client.AccountNumber);
            PrintInfoClient(Client);
            if (DoyouMore("Do you Sour went Delet htis client Y/N?? "))
            {

                MarkClientForDeleteByAccountNumber(Client.AccountNumber, vClients);
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDelet Client Successfully " << endl;
                GoBackToMainScreen();

            }
            else
            {
                GoBackToMainScreen();
            }

        }
        else
        {
            cout << "Cleint wath Account Number (" << Client.AccountNumber << ") Is not Found !!! " << endl << endl;
            GoBackToMainScreen();
        }

 


}


sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)
    
{
    sClient Client;
  
  
        
 
        if (DoyouMore("Are you sure you want update this client? y/n  ?"))
        {
            for (sClient& C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
            return true;
        }
     
 
}
void ShoweUpdeatInfoClientScreen(vector <sClient>& vClients)
{

    CleanScreen();
    PrintScreen("Updet Cleint Screen");
    string AccountNumber ;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, AccountNumber );

    if (FindAccountNumber(vClients, AccountNumber))
    {
        PrintInfoClient(FindInfoClientInvoctor(   vClients,  AccountNumber));
        UpdateClientByAccountNumber(AccountNumber, vClients);
        GoBackToMainScreen();
    }
    else
    {
        cout << "Cleint wath Account Number (" << AccountNumber << ") Is not Found !!! " << endl << endl;
        GoBackToMainScreen();
    }
}

void ShowFiendClientScreen(vector <sClient> vClients)
{
    CleanScreen();
    PrintScreen("Find Client Screen");

    string AccountNumber;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, AccountNumber);

    if (FindAccountNumber(vClients, AccountNumber))
    {
        PrintInfoClient(FindInfoClientInvoctor(vClients, AccountNumber));
        GoBackToMainScreen();
    }
    else
    {
        cout << "Cleint wath Account Number (" << AccountNumber << ") Is not Found !!! " << endl << endl;
        GoBackToMainScreen();
    }

}

void ExistINProgramer()
{
    CleanScreen();
    cout << "\n\n-----------------------------" << endl;
    cout << "      Progran end :) " << endl;
    cout << "-----------------------------" << endl;
}




void ChooseMainMenueu()
{
    CleanScreen();
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    switch (PrintMainMenueuScreen())
    {case enMainMenueOptions::ShowClientList :
        ShowAllClientsListScreen(vClients);
        break;
    case enMainMenueOptions::AddNweClients :
        ShowAddNweClientsScren(vClients);
        break;
    case enMainMenueOptions::DeletClient :
        ShoweDeletClientScreen( vClients);
        break;
    case enMainMenueOptions::UpdeatInfoClient :
        ShoweUpdeatInfoClientScreen(vClients);
        break;
    case enMainMenueOptions::FiendClient :
        ShowFiendClientScreen(vClients);
        break;
    case enMainMenueOptions::eExist :
        ExistINProgramer() ;
        break;
    }
}

int main()
{
    ChooseMainMenueu();
}

void GoBackToMainScreen() 
{
    
    cout << "Enter any character is go main Menue .....";
    system("pause>0");
    ChooseMainMenueu();

}