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
    string Pasword ;
};
struct sAdmin 
{
    string AccountNumber;
    string Name;
    string Phone;
    string Pasword;
};

enum enMainMenueAdminOptions {
    ShowClientList = 1, AddNweClients,
    DeletClient, UpdeatInfoClient
    , FiendClient, Transaction, eExist
};
enum enMainMenueUsarOptions {
    eShowMyInfoUsar = 1, eUpdeatInfoUsar, eDepositUsar , eWithdrawUsar, eMoneytransferUsar, eLogOut
};   
enum enMenueTransactionAdmin {
    Deposit = 1, Withdraw,
    TotalBalanc, MainMenue

};
enum enSingInAdminOrUsar {
    Admin = 1, Usar  , Exist 
    };

const string ClientsFileName = "FileName.txt";  
const string AdminsFileName = "Admin.txt";

void ChooseMainMenueuAdmin();
void GoBackToMainScreenAdmin();
void GoBackToMainScreenUsar(string);
void GoBackToMenueTransactionAdmin();
void MainScreeSingInToSystem();

string Tab(short T)
{
    string S1;
    for (short i = 0; i < T; i++)
    {
        S1 += "\t";

    }
    return S1;
}
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
enMainMenueAdminOptions PrintMainMenueuScreen()
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
    cout << "           [7] Exit. " << endl;
    cout << "________________________________________________________" << endl;
    cout << "Choose What do you want do you ?? [ 1 to 7 ] ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 7);
    return enMainMenueAdminOptions(Number);

}
bool DoyouWentMore(string S1)
{
    char ch;

    cout << "\n\n" << S1;
    cin >> ch;

    return (ch == 'y' || ch == 'Y');
}
int EnterNumber(string S1)
{
    int Number;
    cout << S1 << endl;
    cin >> Number;
    return Number;

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
    Client.Pasword = vClientData[5];

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
    cout << "| " << setw(30) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
    cout << "| " << setw(12) << left << Client.Pasword ;
}
void PrintAllClientsData(vector <sClient> vClients)
{
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ")  Client(s).";


    cout << "\n_______________________________________________________";
    cout << "___________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(30) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "| " << left << setw(12) << "Pasword";
    cout <<
        "\n_______________________________________________________";
    cout << "___________________________________________\n" << endl;
    for (sClient Client : vClients)
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
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintAllClientsData(vClients);


}

string ConvertRecorToLine(sClient Client, string  Seperator = "#//#")
{
    string ConvertRecor = "";

    ConvertRecor += Client.AccountNumber + Seperator;
    ConvertRecor += Client.PinCode + Seperator;
    ConvertRecor += Client.Name + Seperator;
    ConvertRecor += Client.Phone + Seperator;
    ConvertRecor += to_string(Client.AccountBalance) + Seperator ;
    ConvertRecor += Client.Pasword ;
    return ConvertRecor;
}
bool FindAccountNumber(vector <sClient> vClients, string AccountNumber, sClient& Client)
{
    for (sClient& C : vClients)
    {
        if (AccountNumber == C.AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;

}
void ReadNewcliantInfo(sClient& Client)
{

    cout << "\nEnter Pasword ?? ";
    getline(cin >> ws , Client.Pasword);
    cout << "\nEnter Pin Code ?? ";
    getline(cin , Client.PinCode);
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

        sClient  Client;
        vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
        cout << "Please Enter is Info Client : " << endl << endl;
        cout << "Enter Account Number ?? ";
        getline(cin >> ws, Client.AccountNumber);
        while (FindAccountNumber(vClients, Client.AccountNumber, Client))
        {
            cout << "\n\n Client wath [ " << Client.AccountNumber << " ] already exists , Enter ather Account NUmber ?? ";
            cin >> Client.AccountNumber;

        }
        ReadNewcliantInfo(Client);
        AddDataLineToFile(ClientsFileName, ConvertRecorToLine(Client));

    } while (DoyouWentMore("Client Added Succsaflly , Do you want to Add Client ?? Y/N "));

   

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
    cout << "Account Number  : " << Client.AccountNumber << endl;
    cout << "Pin code        : " << Client.PinCode << endl;
    cout << "Name            : " << Client.Name << endl;
    cout << "Phone           : " << Client.Phone << endl;
    cout << "Account Balance : " << Client.AccountBalance << endl;
    cout << "Pasword : " << Client.Pasword << endl;
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


    sClient  Client;
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Delet Cleint Screen");
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Client.AccountNumber);
    if (FindAccountNumber(vClients, Client.AccountNumber, Client))
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

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter Pasword ? ";
    getline(cin >> ws , Client.Pasword );
    cout << "\nEnter PinCode? ";
    getline(cin , Client.PinCode);
    cout << "\nEnter Name? ";
    getline(cin, Client.Name);
    cout << "\nEnter Phone? ";
    getline(cin, Client.Phone);
    cout << "\nEnter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}
bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients)

{


    if (DoyouWentMore("Are you sure you want update this client? y/n  ?"))
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
void ShoweUpdeatInfoClientScreen()
{

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Updet Cleint Screen");
    sClient  Clients;

    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);

    if (FindAccountNumber(vClients, Clients.AccountNumber, Clients))
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
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Find Client Screen");
    sClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);

    if (FindAccountNumber(vClients, Clients.AccountNumber, Clients))
    {
        PrintInfoClient(Clients);

    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;

    }

}

void DepositInClient(string AccountNumber, vector<sClient>& vClients, int NumberIsDeposit , string S1 )
{


    if (DoyouWentMore(S1))
    {
        for (sClient& C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += NumberIsDeposit;
                cout << "\n\nNwe Balanc is " << C.AccountBalance;
                break;
            }
        }
        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\nClient Deposit Successfully.";

    }


}
void ShowDepositScreen()
{
    vector <sClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Deposit Screen");
    sClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);
    ;
    if (FindAccountNumber(vClients, Clients.AccountNumber, Clients))
    {
        PrintInfoClient(Clients);
        int NumberIsDeposit = EnterNumber("Please Enter Deposit amount ??? ");
        DepositInClient(Clients.AccountNumber, vClients, NumberIsDeposit , "Are you sure you want update this client? y/n  ?" );

    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;

    }

}
void ShowWithdrawScreen()
{
    vector <sClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);
    PrintScreen("Deposit Screen");
    sClient  Clients;
    cout << "Enter Account Number ?? ";
    getline(cin >> ws, Clients.AccountNumber);
    ;
    if (FindAccountNumber(vClients, Clients.AccountNumber, Clients))
    {
        PrintInfoClient(Clients);
        int NumberIsDeposit = EnterNumber("Please Enter Withdraw amount ??? ");

        while (NumberIsDeposit <= Clients.AccountBalance)
        {
            cout << "\nAmount Exceeds the balance, you can withdraw up  to : " << Clients.AccountBalance << endl;
            cout << "Please enter another amount? ";
            cin >> NumberIsDeposit;


        }

        DepositInClient(Clients.AccountNumber, vClients, -1 * NumberIsDeposit , "Are you sure you want Withdraw this client? y/n  ?");
    }
    else
    {
        cout << "Cleint wath Account Number (" << Clients.AccountNumber << ") Is not Found !!! " << endl << endl;

    }

}
void PrintClientRecordBalanc(sClient Client)
{
    cout << "| " << setw(20) << left << Client.AccountNumber;
    cout << "| " << setw(50) << left << Client.Name;
    cout << "| " << setw(30) << left << Client.AccountBalance;
}
void PrintAllClientsDataBalanc(vector <sClient> vClients)
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
    for (sClient& Client : vClients)
    {
        PrintClientRecordBalanc(Client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;

}
double TotaalBalanc(vector <sClient> vClients)
{
    double totalBalan = 0;
    for (sClient& Client : vClients)
    {
        totalBalan += Client.AccountBalance;
    }

    return  totalBalan;
}
void ShowTotalBalancScreen()
{

    vector <sClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);

    PrintAllClientsDataBalanc(vClients);
    cout << "\t\t\t Total Balanc Is = " << TotaalBalanc(vClients) << endl;


}
enMenueTransactionAdmin PrintMenueTransaction()
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
    return  enMenueTransactionAdmin(Number);


}
void MenueTransaction()
{

    switch (PrintMenueTransaction())
    {
    case enMenueTransactionAdmin::Deposit:
        CleanScreen();
        ShowDepositScreen();
        GoBackToMenueTransactionAdmin();
        break;
    case enMenueTransactionAdmin::Withdraw:
        CleanScreen();
        ShowWithdrawScreen();
        GoBackToMenueTransactionAdmin();
        break;
    case enMenueTransactionAdmin::TotalBalanc:
        CleanScreen();
        ShowTotalBalancScreen();
        GoBackToMenueTransactionAdmin();
        break;
    case enMenueTransactionAdmin::MainMenue:
        CleanScreen();
        ChooseMainMenueuAdmin();
        break;

    }


}

void ExistINProgramer()
{
    CleanScreen();
    cout << "\n\n-----------------------------" << endl;
    cout << "      Progran end :) " << endl;
    cout << "-----------------------------" << endl;
}

void ChooseMainMenueuAdmin()
{
   
    CleanScreen();
    switch (PrintMainMenueuScreen())
    {
    case enMainMenueAdminOptions::ShowClientList:
        CleanScreen();
        ShowAllClientsListScreen();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::AddNweClients:
        CleanScreen();
        ShowAddNweClientsScren();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::DeletClient:
        CleanScreen();
        ShoweDeletClientScreen();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::UpdeatInfoClient:
        CleanScreen();
        ShoweUpdeatInfoClientScreen();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::FiendClient:
        CleanScreen();
        ShowFiendClientScreen();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::Transaction:
        CleanScreen();
        MenueTransaction();
        GoBackToMainScreenAdmin();
        break;
    case enMainMenueAdminOptions::eExist:
        CleanScreen();
        MainScreeSingInToSystem();
        break;
    }
}

 
enMainMenueUsarOptions PrintMainScreeinIsUsar(string Name )
{
    int Number = 0;   
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "                   Welcom "<< Name <<" To BanK Amer             " << endl;
    cout << Tab(4) << "                   Main Menueu BanK Amer                        " << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "[1] Show My Info. " << endl;
    cout << Tab(4) << "[2] Updeat My Info. " << endl;
    cout << Tab(4) << "[3] Deposit. " << endl;
    cout << Tab(4) << "[4] Withdraw. " << endl;
    cout << Tab(4) << "[5] Money Transfer. " << endl;
    cout << Tab(4) << "[6] Log out. " << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "Enter Number ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 6);
    return enMainMenueUsarOptions(Number);

}
void DepositUsar(sClient& Client , vector<sClient> vClients)
{
     
    PrintInfoClient(Client);
    int NumberIsDeposit = EnterNumber("Please Enter Deposit amount ??? ");
    DepositInClient(Client.AccountNumber , vClients,   NumberIsDeposit , " Are you sure you want Deposit this client? y/n  ?");
}
void WithdrawUsar(sClient& Client, vector<sClient> vClients)
{
     
    PrintInfoClient(Client);
    int NumberIsDeposit = EnterNumber("Please Enter Deposit amount ??? ");
    while (NumberIsDeposit >= Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up  to : " << Client.AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> NumberIsDeposit;


    }
    DepositInClient(Client.AccountNumber, vClients, -1* NumberIsDeposit , "Are you sure you want Withdraw this client? y/n  ?" );
}
 
void chackWithdr(double AccountBalance , int Number )
{
    while (Number >=  AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can Money Transfer up  to : " << AccountBalance << endl;
        cout << "Please enter another amount? ";
        cin >> Number;


    }

}

void MoneyTransferUsar(sClient MyClient, string AccountNumbertransferUsar, int Number, vector<sClient>& vClients)
{


    sClient Client;
    if (FindAccountNumber(vClients, AccountNumbertransferUsar, Client))
    {
        chackWithdr(MyClient.AccountBalance, Number);

            if (DoyouWentMore("Are you sure you want Transfer Money this client? y/n  ?"))
            {
                for (sClient& C : vClients)
                {
                    if (C.AccountNumber == MyClient.AccountNumber)
                    {
                        C.AccountBalance += (Number*-1) ;
                        cout << "\n\nNwe Balanc is " << C.AccountBalance;
                        break;
                    }
                }
                for (sClient& C : vClients)
                {
                    if (C.AccountNumber == AccountNumbertransferUsar )
                    {
                        C.AccountBalance += Number ;
                       // cout << "\n\nNwe Balanc is " << C.AccountBalance;
                        break;
                    }
                }
                SaveCleintsDataToFile(ClientsFileName, vClients);

                cout << "\nTransfer Money Successfully."; 
        }
    }
    else
    {
        cout << "\n\n Client wath [ " << AccountNumbertransferUsar << " ] already exists " << endl;

    }
}

void ShowMoneyTransferUsar(sClient  &Client ,vector<sClient>& vClients)
{
    int Number = 0;
    string AccountNumbertransferUsar = "";
    PrintInfoClient(Client);
    cout << "Enter Account Number You Would Money Transfer ??";
    cin >> AccountNumbertransferUsar;
    cout << "How Match Money Transfer ??";
    cin >> Number ;
    MoneyTransferUsar(Client , AccountNumbertransferUsar, Number, vClients);
}
void ChooseMainMenueuUsar(string AccountNumber )
{
    CleanScreen();
    sClient  Client ;
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    FindAccountNumber(vClients, AccountNumber, Client);
     
      switch (PrintMainScreeinIsUsar( Client.Name))
    {
     case enMainMenueUsarOptions::eShowMyInfoUsar :
        CleanScreen();
        PrintInfoClient(Client);
        GoBackToMainScreenUsar(Client.AccountNumber);
        break;
    case enMainMenueUsarOptions::eUpdeatInfoUsar :
        CleanScreen();
        PrintInfoClient(Client);
        UpdateClientByAccountNumber(Client.AccountNumber, vClients);
         GoBackToMainScreenUsar(Client.AccountNumber);
        break;
    case enMainMenueUsarOptions::eDepositUsar:
        CleanScreen();
        DepositUsar(Client , vClients );
        GoBackToMainScreenUsar(Client.AccountNumber);
        break;
    case enMainMenueUsarOptions::eWithdrawUsar:
        CleanScreen();
        WithdrawUsar(Client, vClients);
        GoBackToMainScreenUsar(Client.AccountNumber);
        break;
    case enMainMenueUsarOptions::eMoneytransferUsar :
        CleanScreen();
        ShowMoneyTransferUsar(Client, vClients);
        GoBackToMainScreenUsar(Client.AccountNumber);
        break;
    case  enMainMenueUsarOptions::eLogOut:
        CleanScreen();
       MainScreeSingInToSystem();
         
        break;
 
    }

     
}
  

sAdmin ConvertLinetoRecordAdmin(string Line, string Seperator = "#//#")

{
    sAdmin Admin;
    vector<string> vAdminData;
    vAdminData = SplitString(Line, Seperator);
    Admin.AccountNumber = vAdminData[0];
    Admin.Name = vAdminData[1];
    Admin.Phone = vAdminData[2];
    Admin.Pasword = vAdminData[3];

    return Admin ;
}
vector <sAdmin> LoadsAdminDataFromFile(string FileName)
{
    vector <sAdmin> vAdmin;
    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode
    if (MyFile.is_open())
    {
        string Line;
        sAdmin Admin;
        while (getline(MyFile, Line))
        {
            Admin = ConvertLinetoRecordAdmin(Line);
            vAdmin.push_back(Admin);
        }
        MyFile.close();
    }
    return vAdmin ;
}
bool FindAccountNumber(vector <sAdmin>  vAdmin, string AccountNumber, sAdmin&  Admin)
{
    for (sAdmin& C : vAdmin)
    {
        if (AccountNumber == C.AccountNumber)
        {
            Admin = C;
            return true;
        }
    }
    return false;

}
bool ChackAccountNumberAndPaswordAdmen(string AccountNumber , string Pasword )
{
        sAdmin Admin;
        vector <sAdmin>  vAdmin = LoadsAdminDataFromFile(AdminsFileName);
        if (FindAccountNumber(vAdmin, AccountNumber, Admin))
        {
            if (Pasword == Admin.Pasword)
                return true;
        }
        return false;
     
}
bool ChackAccountNumberAndPaswordUsar(string AccountNumber, string Pasword , sClient &Client)
{
     
    vector <sClient>  vClients = LoadCleintsDataFromFile(ClientsFileName);
    if (FindAccountNumber(vClients, AccountNumber, Client))
    {
        if (Pasword == Client.Pasword)
        {
            return true;

        }
        }
    return false;

}
enSingInAdminOrUsar PrintMainScreeinIsBankSingIn()
{
    int Number = 0;
    cout << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "                     Welcom To BanK Amer                        " << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "Are You :" << endl;
    cout << Tab(4) << "[1] Admin. " << endl;
    cout << Tab(4) << "[2] Client. " << endl;
    cout << Tab(4) << "[3] Exist. " << endl;
    cout << Tab(4) << "----------------------------------------------------------------" << endl;
    cout << Tab(4) << "Enter Number ?? ";
    cin >> Number;
    HowNumberFromTo(Number, 1, 3);
    return enSingInAdminOrUsar(Number);

}
void SingInAdminInSystem()
{
        CleanScreen();
        ChooseMainMenueuAdmin();
}

void SingInUsarInSystem(string  AccountNumber )
{
        CleanScreen();
        ChooseMainMenueuUsar(AccountNumber);
}

void MainScreeSingInToSystem()
{
    enSingInAdminOrUsar  SingInAdminOrUsar = PrintMainScreeinIsBankSingIn();
    if(SingInAdminOrUsar != enSingInAdminOrUsar::Exist )
    { 
    string AccountNumber = "";
    string Pasword = "";
    cout << Tab(4) << "Pleas Enter A Account Number ?? "  ;
    cin >> AccountNumber; 
    cout << Tab(4) << "Pleas Enter A Pasword ?? " ;
    cin >> Pasword;
    cout << endl << endl;
    if (SingInAdminOrUsar == enSingInAdminOrUsar::Admin)
    {
        if (ChackAccountNumberAndPaswordAdmen(AccountNumber, Pasword))
        {
            SingInAdminInSystem();
        }
        else
        {
            cout << Tab(4) << "Pasword Or Account Number Is mistake , Please once again ......";
            system("pause>0");
            CleanScreen();
            MainScreeSingInToSystem();
        }
        
    }
     else if (SingInAdminOrUsar == enSingInAdminOrUsar::Usar )
    {
        sClient  Client;
        if (ChackAccountNumberAndPaswordUsar(AccountNumber, Pasword, Client))
        {
            SingInUsarInSystem(Client.AccountNumber);
        }
        else
        {
            cout << Tab(4) << "Pasword Or Account Number Is mistake , Please once again ......";
            system("pause>0");
            CleanScreen();
            MainScreeSingInToSystem();

        }
    }
    }
     else
    {
        CleanScreen();
        ExistINProgramer();


    }

}

int main()
{
    MainScreeSingInToSystem();    
    return 0;
}

void GoBackToMainScreenAdmin()
{

    cout << "Enter any character is go main Menue .....";
    system("pause>0");
    ChooseMainMenueuAdmin();

}
void GoBackToMenueTransactionAdmin()
{

    cout << "Enter any character is go Transactio Menue .....";
    system("pause>0");
    MenueTransaction();

}
void GoBackToMainScreenUsar(string AccountNumber )
{

    cout << "Enter any character is go main Menue ....." ;
    system("pause>0");
    ChooseMainMenueuUsar(AccountNumber);

}