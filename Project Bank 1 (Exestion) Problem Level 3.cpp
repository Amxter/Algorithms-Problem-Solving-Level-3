#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;

struct stClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance ;
    bool MarkForDelete = false;
};
struct stUser
{
    string UserName;
    string Password;
    short Penmissions;
    bool MarkForDelete = false; 
};
enum enMainMenueOptions {eShowClientList = 1, eAddNweClients,eDeletClient, eUpdeatInfoClient, eFiendClient, eTransaction , eManageUser , eLogout};
enum enMenueTransaction {Deposit = 1, Withdraw,TotalBalanc, MainMenue};
enum enMenueManageUsers{eListUsers = 1 , eAddNewUser , eDeleteUser , eUpdateUser , eFindUser , eMainMenue };

 stUser UserLogin;
 const string ClientsFileName = "FileName.txt"; 
 const string UsarsFileName   = "Admin.txt";

void ChooseMainMenueu();
void GoBackToMainScreen();
void GoBackToMenueTransaction();
void GoBackToMenueManageUsers();
void Login();

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
    cout << "           [6] Transaction. " << endl;
    cout << "           [7] Manage User. " << endl;
    cout << "           [8] Logout. " << endl;
    cout << "________________________________________________________" << endl;
    cout << "Choose What do you want do you ?? [ 1 to 8 ] ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 8);
    return enMainMenueOptions(Number);

}
bool DoyouWentMore(string S1)
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
stClient ConvertLinetoRecord(string Line, string Seperator = "#//#")

{
    stClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to

    return Client;
}
vector <stClient> LoadCleintsDataFromFile(string FileName)
{
    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        stClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

stUser ConvertLinetoRecordUsar(string Line, string Seperator = "#//#")

{
    stUser Usar ;
    vector<string> vUsarData;
    vUsarData = SplitString(Line, Seperator);
    Usar.UserName = vUsarData[0];
    Usar.Password = vUsarData[1];
    Usar.Penmissions = stod(vUsarData[2]);

    return Usar;
}
vector <stUser> LoadUsarsDataFromFile(string FileName)
{
    vector <stUser> vUsar;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        stUser Usar;
        while (getline(MyFile, Line))
        {
            Usar = ConvertLinetoRecordUsar(Line);
            vUsar.push_back( Usar);
        }
        MyFile.close();
    }
    return vUsar ;
}


void PrintClientRecord(stClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <stClient> vClients)
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
    for (stClient Client : vClients)
    {
        PrintClientRecord(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ShowAllClientsListScreen()
{
    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClientsData(vClients);
  

}

string ConvertRecorToLine(stClient Client, string  Seperator = "#//#")
{
    string ConvertRecor = "";

    ConvertRecor += Client.AccountNumber + Seperator;
    ConvertRecor += Client.PinCode + Seperator;
    ConvertRecor += Client.Name + Seperator;
    ConvertRecor += Client.Phone + Seperator;
    ConvertRecor += to_string(Client.AccountBalance);

    return ConvertRecor;
}
bool FindAccountNumber(vector <stClient> vClients, string AccountNumber , stClient  &Client )
{
    for (stClient& C  : vClients)
    {
        if (AccountNumber == C.AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;

}
void ReadNewcliantInfo(stClient& Client)
{

    cout << "\nEnter Pin Code ?? ";
    getline(cin >> ws, Client.PinCode);
    cout << "\nEnter Name  ?? ";
    getline(cin, Client.Name);
    cout << "\nEnter Phone ?? ";
    getline(cin, Client.Phone);
    cout << "\nEnter Account Balance ?? ";
    cin >> Client.AccountBalance;

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
void ShowAddNweClientsScren()
{


    do
    {
        
        stClient  Client;
        vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
        cout << "Please Enter is Info Client : " << endl << endl;
        cout << "Enter Account Number ?? ";
        getline(cin >> ws, Client.AccountNumber);
        while (FindAccountNumber(vClients, Client.AccountNumber , Client ))
        {
            cout << "\n\n Client wath [ " << Client.AccountNumber << " ] already exists , Enter ather Account NUmber ?? ";
            cin >> Client.AccountNumber;

        }
        ReadNewcliantInfo(Client);
        AddDataLineToFile(ClientsFileName, ConvertRecorToLine(Client));

    } while (DoyouWentMore("Client Added Succsaflly , Do you want to Add Client ?? Y/N "));

    GoBackToMainScreen();

}


bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stClient>& vClients)
{
    for (stClient& C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <stClient> SaveCleintsDataToFile(string FileName, vector <stClient> vClients)

{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stClient C : vClients)
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
void PrintInfoClient(stClient  Client)
{
    cout << "\n\nThe Folowing are the client Datails" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Pin code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "--------------------------------------" << endl << endl;
}
void PrintScreen(string Titel)
{

    cout << "\n\n-------------------------------" << endl;
    cout << "        " << Titel << endl;
    cout << " -------------------------------" << endl;
}
void ShoweDeletClientScreen()
{

     
    stClient  Client;
    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Delet Cleint Screen");
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Client.AccountNumber);
    if (FindAccountNumber(vClients, Client.AccountNumber, Client ))
    {
        PrintInfoClient(Client);
        if (DoyouWentMore("Do you Sour went Delet htis client Y/N?? "))
        {

            MarkClientForDeleteByAccountNumber(Client.AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nDelet Client Successfully " << endl;
           

        }
      

    }
    else
    {
        cout << "Cleint wath Account Number (" << Client.AccountNumber << ") Is not Found !!! " << endl << endl;
       
    }




}


stClient ChangeClientRecord(string AccountNumber)
{
    stClient Client;
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
bool UpdateClientByAccountNumber(string AccountNumber, vector<stClient>& vClients)

{
 

    if (DoyouWentMore("Are you sure you want update this client? y/n  ?"))
    {
        for (stClient& C : vClients)
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
void ShoweUpdeatInfoClientScreen()
{

    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName); 
    PrintScreen("Updet Cleint Screen");
    stClient  Clients;
     
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);

    if (FindAccountNumber(vClients, Clients.AccountNumber , Clients ))
    {
        PrintInfoClient(Clients);
        UpdateClientByAccountNumber(Clients.AccountNumber, vClients);
       
    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;
       
    }
}


void ShowFiendClientScreen()
{
    vector <stClient> vClients = LoadCleintsDataFromFile(ClientsFileName); 
    PrintScreen("Find Client Screen");
    stClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);

    if (FindAccountNumber(vClients, Clients.AccountNumber , Clients))
    {
        PrintInfoClient(Clients);
         
    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;
        
    }

}

int EnterNumber(string S1)
{
    int Number;
    cout << S1 << endl;
    cin >> Number;
    return Number;

}
void DepositInClient(string AccountNumber, vector<stClient>& vClients , int NumberIsDeposit)

{
  

    if (DoyouWentMore("Are you sure you want update this client? y/n  ?"))
    {
        for (stClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += NumberIsDeposit;
                cout << "\n\nNwe Balanc is " << C.AccountBalance;
                break;
            }
        }
        SaveCleintsDataToFile(ClientsFileName, vClients);
       
        cout << "\nClient Updated Successfully.";
         
    }


}
void ShowDepositScreen()
{
    vector <stClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Deposit Screen");
    stClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);
    ;
    if (FindAccountNumber(vClients, Clients.AccountNumber , Clients ))
    {
        PrintInfoClient(Clients);
        int NumberIsDeposit = EnterNumber("Please Enter Deposit amount ??? ");
        DepositInClient(Clients.AccountNumber, vClients, NumberIsDeposit);
         
    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;
         
    }

}
void ShowWithdrawScreen( )
{
    vector <stClient>  vClients = LoadCleintsDataFromFile(ClientsFileName); 
    PrintScreen("Deposit Screen");
    stClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);
    ;
    if (FindAccountNumber(vClients, Clients.AccountNumber , Clients ))
    {
        PrintInfoClient(Clients);
        int NumberIsDeposit = -1*EnterNumber("Please Enter Withdraw amount ??? ");

        while (NumberIsDeposit <= Clients.AccountBalance )
        {
            cout << "\nAmount Exceeds the balance, you can withdraw up  to : " << Clients.AccountBalance << endl;
            cout << "Please enter another amount? ";
            cin >> NumberIsDeposit;


        }
       
        DepositInClient(Clients.AccountNumber, vClients, NumberIsDeposit);
    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;
        
    }

}
 
void PrintClientRecordBalanc(stClient Client)
{
    cout << "| " << setw(20) << left << Client.AccountNumber;
    cout << "| " << setw(50) << left << Client.Name;
    cout << "| " << setw(30) << left << Client.AccountBalance;
}
void PrintAllClientsDataBalanc(vector <stClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")  Client(s).";


    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "Accout Number";
    cout << "| " << left << setw(50) << "Client Name";
    cout << "| " << left << setw(30) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stClient &Client : vClients)
    {
        PrintClientRecordBalanc(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
 
double TotaalBalanc(vector <stClient> vClients)
{
    double totalBalan = 0; 
   for ( stClient & Client :  vClients )
   {
        totalBalan += Client.AccountBalance ; 
   }

    return  totalBalan ; 
}  
void ShowTotalBalancScreen( )
{

    vector <stClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);
   
     PrintAllClientsDataBalanc(vClients);
     cout << "\t\t\t Total Balanc Is = " <<   TotaalBalanc(vClients) << endl ;
  

}
 
enMenueTransaction PrintMenueTransaction()
{

    int Number = 0;
    cout << "________________________________________________________" << endl;
    cout << "               Menue     Transaction " << endl;
    cout << "________________________________________________________" << endl;
    cout << "           [1] Deposit. " << endl;
    cout << "           [2] Withdraw. " << endl;
    cout << "           [3] Total Balans. " << endl;
    cout << "           [4] Main Menue. " << endl;
    cout << "________________________________________________________" << endl;
    cout << "Choose What do you want do you ?? [ 1 to 4 ] ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 4);
    return  enMenueTransaction(Number);


}
void MenueTransaction()
{ 
    CleanScreen();
   
    switch (PrintMenueTransaction())
    {
    case enMenueTransaction::Deposit:
        CleanScreen();
             ShowDepositScreen( );
             GoBackToMenueTransaction();
            break;
    case enMenueTransaction::Withdraw :
        CleanScreen();
          ShowWithdrawScreen();
          GoBackToMenueTransaction();
        break;
    case enMenueTransaction::TotalBalanc :
        CleanScreen();
         ShowTotalBalancScreen();
         GoBackToMenueTransaction();
        break;
    case enMenueTransaction::MainMenue :
        CleanScreen();
           ChooseMainMenueu() ;
        break;
 
    }


}


void PrintUsarRecord(stUser Usar)
{
    cout << "| " << setw(20) << left << Usar.UserName;
    cout << "| " << setw(30) << left << Usar.Password;
    cout << "| " << setw(10) << left << Usar.Penmissions;
}
void PrintAllUsarsData(vector <stUser> vUsars)
{
    cout << "\n\t\t\t\t\tClient List (" << vUsars.size() << ")  Client(s).";


    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(20) << "Accout Number";
    cout << "| " << left << setw(30) << "Password";
    cout << "| " << left << setw(10) << "Penmissions";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stUser & Usar : vUsars)
    {
        PrintUsarRecord(Usar);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
void ShowListUsers()
{
    vector <stUser> vUsars = LoadUsarsDataFromFile(UsarsFileName); 
    PrintAllUsarsData(vUsars);
}
 
short ReadPenmissionsUser()
{
    short Penmissions = 0 ;
    char Ch;  
    cout << "Do you went to give full access ? y/n ?? ";
    cin >> Ch ; 
    if (Ch == 'Y' || Ch == 'y')
        return -1; 
    cout << "\nDo you went to give access : " << endl << endl ;
    cout << "Show Show Client List ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 0);
    cout << "\nAdd Nwe Clients ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 1);
    cout << "\nDelet Client ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 2);
    cout << "\nUpdeat Info Client ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 3);
    cout << "\nFiend Clienta ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 4);
    cout << "\nTransaction  ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 5);
    cout << "\nManage User ?? y/n ?? ";
    cin >> Ch;
    if (Ch == 'Y' || Ch == 'y')
        Penmissions += pow(2, 6);

    return  Penmissions;
}
string ConvertRecorToLine(stUser  User, string  Seperator = "#//#")
{
    string ConvertRecor = "";

    ConvertRecor += User.UserName + Seperator;
    ConvertRecor += User.Password + Seperator;
    ConvertRecor += to_string(User.Penmissions);
 

    return ConvertRecor;
}
bool FindUserName(vector <stUser> vUsar , string UserName, stUser & Usar)
{
    for (stUser& U : vUsar)
    {
        if (UserName == U.UserName)
        {
            Usar = U ;
            return true;
        }
    }
    return false;

}
void AddNweUsarsScren()
{
    do
    {
        CleanScreen();
        stUser  Usar;
        vector <stUser> vUsar = LoadUsarsDataFromFile(UsarsFileName);
        cout << "Please Enter is Info Usar : " << endl << endl;
        cout << "Enter Name User ?? " ;
        getline(cin >> ws, Usar.UserName);
        while (FindUserName(vUsar, Usar.UserName , Usar))
        {
            cout << "\n\n Usar wath [ " << Usar.UserName << " ] already exists , Enter ather Usar Name ?? ";
            cin >> Usar.UserName ;

        }
        cout << "\nEnter Password  ?? ";
        getline(cin >> ws, Usar.Password );
        Usar.Penmissions = ReadPenmissionsUser();
        AddDataLineToFile(UsarsFileName, ConvertRecorToLine(Usar));

    } while (DoyouWentMore("Usar Added Succsaflly , Do you want to Add Client ?? Y/N "));

     

}

bool MarkUsarForDeleteByUserName(string UserName , vector <stUser> &vUsar)
{
    for (stUser& U : vUsar)
    {
        if (U.UserName == UserName)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
vector <stUser> SaveUsarsDataToFile(string FileName, vector <stUser> vUsar)

{
    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite
    string DataLine;
    if (MyFile.is_open())
    {
        for (stUser U : vUsar )
        {
            if (U.MarkForDelete == false)
            {
                //we only write records that are not marked for

                DataLine = ConvertRecorToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsar ;
}
void PrintInfoUser(stUser  User)
{
    cout << "\n\nThe Folowing are the Usar Datails" << endl;
    cout << "--------------------------------------" << endl;
    cout << "User Name   : " << User.UserName << endl;
    cout << "Password    : " << User.Password << endl;
    cout << "Penmissions : " << User.Penmissions << endl;
    cout << "--------------------------------------" << endl << endl;
}
void ShoweDeletUsarScreen()
{
 
    stUser  User;
    vector <stUser> vUsar = LoadUsarsDataFromFile(UsarsFileName);
    PrintScreen("Delet Usar Screen");
    cout << "Please Enter is Info Usar : " << endl << endl;
    cout << "Enter Name User ?? ";
    getline(cin >> ws, User.UserName);
    if (FindUserName(vUsar, User.UserName, User))
    {
        PrintInfoUser( User) ;
        if (DoyouWentMore("Do you Sour went Delet htis User Y/N?? "))
        {

            MarkUsarForDeleteByUserName(User.UserName, vUsar);
            SaveUsarsDataToFile(UsarsFileName, vUsar);
            cout << "\n\nDelet Client Successfully " << endl;


        }


    }
    else
    {
        cout << "Usar wath Usar Name (" << User.UserName << ") Is not Found !!! " << endl << endl;

    }




}

bool UpdateUserByUserName(string UserName, vector <stUser>& vUser)

{


    if (DoyouWentMore("Are you sure you want update this client? y/n  ?"))
    {
        for (stUser & U : vUser)
        {
            if (U.UserName == UserName)
            {
                cout << "Enter Name Password ?? ";
                getline(cin >> ws, U.Password );
                cout << endl;
                U.Penmissions = ReadPenmissionsUser();
                break;
            }
        }
        SaveUsarsDataToFile(UsarsFileName, vUser );
        cout << "\n\nClient Updated Successfully.";
        return true;
    }


}
void ShoweUpdeatInfoUserScreen()
{
   
    stUser  User;
    vector <stUser> vUser = LoadUsarsDataFromFile(UsarsFileName);
    PrintScreen("Updet Usar Screen");
    cout  << endl;
    cout << "Enter Name User ?? ";
    getline(cin >> ws, User.UserName);
 

    if (FindUserName(vUser, User.UserName, User)) 
    {
        PrintInfoUser(User);
        UpdateUserByUserName( User.UserName , vUser );

    }
    else
    {
        cout << "Usar wath Usar Name (" << User.UserName << ") Is not Found !!! " << endl << endl;

    }
}

void ShowFiendUserScreen()
{

    stUser  User;
    vector <stUser> vUser = LoadUsarsDataFromFile(UsarsFileName);
    PrintScreen("Find Usar Screen");
    cout << endl;
    cout << "Enter Name User ?? ";
    getline(cin >> ws, User.UserName);

    if (FindUserName(vUser, User.UserName, User))
    {
        PrintInfoUser(User);
    }
    else
    {
        cout << "Usar wath Usar Name (" << User.UserName << ") Is not Found !!! " << endl << endl;
    }

}

enMenueManageUsers PrintMenueManageUssers()
{
    int Number = 0; 
    cout << "________________________________________________________" << endl;
    cout << "                 Menue Manage Users " << endl;
    cout << "________________________________________________________" << endl;
    cout << "           [1] List Users. " << endl;
    cout << "           [2] Add New User. " << endl;
    cout << "           [3] Delete User. " << endl;
    cout << "           [4] UpdateUser. " << endl;
    cout << "           [5] FindUser. " << endl;
    cout << "           [6] Main Menue. " << endl;
    cout << "________________________________________________________" << endl;
    cout << "Choose What do you want do you ?? [ 1 to 6 ] ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 6);
    return  enMenueManageUsers(Number);


}
void MenueManageUsers()
{
    CleanScreen();
    switch (PrintMenueManageUssers())
    {
    case enMenueManageUsers::eListUsers:
        CleanScreen();
        ShowListUsers();
        GoBackToMenueManageUsers();
            break;
    case enMenueManageUsers::eAddNewUser:
        CleanScreen();
        AddNweUsarsScren();
        GoBackToMenueManageUsers();
        break;
    case enMenueManageUsers::eDeleteUser:
        CleanScreen();
        ShoweDeletUsarScreen();
        GoBackToMenueManageUsers();
        break;
    case enMenueManageUsers::eUpdateUser:
        CleanScreen();
        ShoweUpdeatInfoUserScreen();
        GoBackToMenueManageUsers();
        break;
    case enMenueManageUsers::eFindUser:
        CleanScreen();
        ShowFiendUserScreen();
        GoBackToMenueManageUsers();
        break;
    case enMenueManageUsers::eMainMenue :
        CleanScreen();
         ChooseMainMenueu();
        
        break;
    default:
        break;
    }



}

bool DoYouHavePenmissions(stUser User , enMainMenueOptions  MainMenueOptions )
{
    if (User.Penmissions == -1)
        return true;

    switch (MainMenueOptions)
    {
    case enMainMenueOptions::eShowClientList:
        return ((User.Penmissions & 1) == 1);
    case enMainMenueOptions::eAddNweClients:
        return ((User.Penmissions & 2) == 2);
    case enMainMenueOptions::eDeletClient:
        return ((User.Penmissions & 4) == 4);
    case enMainMenueOptions::eUpdeatInfoClient:
        return ((User.Penmissions & 8) == 8);
    case enMainMenueOptions::eFiendClient:
        return ((User.Penmissions & 16) == 16);
    case enMainMenueOptions::eTransaction:
        return ((User.Penmissions & 32) == 32);
    case enMainMenueOptions::eManageUser:
        return ((User.Penmissions & 64) == 64 );
    default :
        return false; 
    }

    

}
void YouDontHavePenmissions()
{
    cout << "\n_______________________________________" << endl;
    cout << "Access Denied ," << endl;
    cout << "Uou dont have permission to do this ," << endl;
    cout << "Please conact your Admin . " << endl;
    cout << "_______________________________________" << endl;
}
void LogoutInBank()
{
    Login();
}
void ChooseMainMenueu()
{
    CleanScreen();
      stUser User; 
    switch (PrintMainMenueuScreen())
    {
    case enMainMenueOptions::eShowClientList:
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eShowClientList))
            ShowAllClientsListScreen();
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eAddNweClients:
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eAddNweClients))
        ShowAddNweClientsScren( );
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eDeletClient:
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eDeletClient))
        ShoweDeletClientScreen();
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eUpdeatInfoClient:
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eUpdeatInfoClient))
        ShoweUpdeatInfoClientScreen();
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eFiendClient:
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eFiendClient))
        ShowFiendClientScreen();
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eTransaction :
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eTransaction))
    MenueTransaction();
        else
            YouDontHavePenmissions();
    GoBackToMainScreen();
       break;
    case enMainMenueOptions::eManageUser :
        CleanScreen();
        if (DoYouHavePenmissions(UserLogin, enMainMenueOptions::eManageUser))
        MenueManageUsers();
        else
            YouDontHavePenmissions();
        GoBackToMainScreen();
        break;
    case enMainMenueOptions::eLogout:
        CleanScreen();
        LogoutInBank();
        break;
    }
}



bool FiendUsarByUsarnameAndPasword( stUser Usar , stUser & FullInfoUsar)
{
    vector <stUser> vUsar  = LoadUsarsDataFromFile( UsarsFileName );

    for (stUser & U : vUsar)
    {
        if (U.UserName == Usar.UserName)
            if (U.Password == Usar.Password)

            {
                FullInfoUsar = U ;
                return true;
            }
                
    }

    return false ;
} 
void Login()
{
    stUser User;
    CleanScreen();
    cout << "\n-----------------------------" << endl;
    cout << "        Login Screen " << endl;
    cout << "-----------------------------" << endl;
    cout << "Plese enter a User Name ? " << endl;
    getline(cin >> ws, User.UserName);
    cout << "\nPlese enter a Pasword ? " << endl;
    cin >> User.Password ;

    if (FiendUsarByUsarnameAndPasword(User , UserLogin ))
    { 
        ChooseMainMenueu();
    }
    else
    {
        do
        {
            CleanScreen();
            cout << "\n\n-----------------------------" << endl;
            cout << "        Login Screen " << endl;
            cout << "-----------------------------" << endl;
            cout << "Invlaid Username Or Password ." << endl;
            cout << "Plese enter a User Name ? " ;
            cin >> User.UserName;
            cout << "\nPlese enter a Password ? " ;
            cin >> User.Password;
        }while (!FiendUsarByUsarnameAndPasword(User , UserLogin ));
        ChooseMainMenueu();
    }


}

int main()
{
    Login();
}

void GoBackToMainScreen()
{

    cout << "Enter any character is go main Menue .....";
    system("pause>0");
     ChooseMainMenueu();

}
void GoBackToMenueTransaction()
{

    cout << "Enter any character is go Transactio Menue .....";
    system("pause>0");
    MenueTransaction();

}
void GoBackToMenueManageUsers()
{

    cout << "Enter any character is go Manage Users .....";
    system("pause>0");
    MenueManageUsers();

}