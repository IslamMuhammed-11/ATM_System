// AlgorithmLvl4_ATM_System.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;
void quickWithDrawMenu();
void goBackToMainMenu();
void checkBalance();
void deposit();
void normalWithdraw();
void loginScreen();
//Struct
struct stClients {
    string accountNumber = "";
    string pinCode = "";
    string name = "";
    string phoneNumber = "";
    double accountBalance;
    bool markToDelete = false;
};

//Enums
enum enMainMenuChoices{ enQuickWithdraw = 1 , enNormalWithdraw = 2 , enDeposit = 3 , enCheckBalance = 4 , enLogout = 5};
enum enQuickWithdrawChoices{ enTwenty = 1 , enFifty = 2 , enHundred = 3 , enTwoHundred = 4 , enFourHundred = 5 , enSixHundred = 6 , enEightHundred = 7 , enThousend = 8 , enExit = 9 };

//Global Vars
const string clientFileName = "Clients.txt";
stClients LoggedClient;


//General Functions
vector<string>split(string line, string delim = "#//#") {

    vector<string>vSplit;
    string sWord;
    short pos = 0;
    while ((pos = line.find(delim)) != std::string::npos )
    {
        sWord = line.substr(0, pos);
        if (sWord != "")
        {
        vSplit.push_back(sWord);
        }
        line.erase(0, pos + delim.length());
    }
 
    if (line != "")
    {
        vSplit.push_back(line);
    }
    return vSplit;
}

stClients convertLineToRecord(string line , string delim = "#//#") {
    stClients record;
    vector<string> data;
    data = split(line , delim);
    record.accountNumber = data[0];
    record.pinCode = data[1];
    record.name = data[2];
    record.phoneNumber = data[3];
    record.accountBalance = stod(data[4]);
    return record;

}

string convertRecordToLine(stClients record, string delim = "#//#") {
    string line = "";
    line += record.accountNumber + delim;
    line += record.pinCode + delim;
    line += record.name + delim;
    line += record.phoneNumber + delim;
    line += to_string(record.accountBalance);
    return line;
}

vector<stClients>loadRecordsFromFile(string filename) {
    vector<stClients>vClients;
    stClients client;
    string line;
    fstream myFile;
    myFile.open(filename, ios::in);

    if (myFile.is_open())
    {
        while (getline(myFile,line))
        {
            client = convertLineToRecord(line);
            vClients.push_back(client);
        }
        myFile.close();
    }
    return vClients;
}

bool findClientByAccountNumberAndPassword(string accountNumber, string pinCode, stClients& client) {

    vector<stClients>vClients = loadRecordsFromFile(clientFileName);

    for (stClients& c : vClients) {

        if (c.accountNumber == accountNumber && c.pinCode == pinCode)
        {
            client = c;
            return true;
        }
    }
    return false;
}

vector<stClients>saveDataToFile(string filename , vector<stClients>&vClients) {
    fstream myFile;
    myFile.open(filename, ios::out);

    if (myFile.is_open())
    {
        string fileLine;
        for (stClients& c : vClients) {
            if (c.markToDelete == false)
            {
              
                fileLine = convertRecordToLine(c);
                myFile << fileLine << endl;
            }
        }
        myFile.close();
    }
    return vClients;
}

bool depositBalanceToClientByAccountNumber(double newBalance, string accountNumber, vector<stClients>& vClient) {


    char answer = 'n';
    cout << "Are You Sure You Want To Perform This Transaction ? y/n ";
    cin >> answer;
    if (toupper(answer) == 'Y')
    {
        for (stClients& c : vClient) {

            if (accountNumber == c.accountNumber)
            {
                c.accountBalance += newBalance;
                saveDataToFile(clientFileName, vClient);
                cout << "\nDone Successfully, New Balance is " << c.accountBalance << endl;
                return true;
            }
        }
    }

    return false;
}


// withdraws
//bool withdrawBalanceFromClient(double newBalance) {
//
//
//   
//
//}

//Read User's Choices
enMainMenuChoices readMainMenuChoices() {
    short choice = 0;
    do
    {
        cin >> choice;
    } while (choice < 1 || choice > 5);

    return (enMainMenuChoices)choice;
}

short readQuickWithdrawChoices() {
    short choice = 0;
    do
    {
        cin >> choice;
    } while (choice < 1 || choice > 9);

    return choice;
}
// get Amount From user
short getQuickWithDrawAmount(short quickWithdrawChoice) {

    switch (quickWithdrawChoice)
    {
    case 1: return 20;
    case 2: return 50;
    case 3: return 100;
    case 4: return 200;
    case 5: return 400;
    case 6: return 600;
    case 7: return 800;
    case 8: return 1000;
    default:
        break;
    }
}

int getNormalWithdrawAmount() {
    int amount = 0;
    do
    {
        cout << "Enter An Amount multiple of 5's ? ";
        cin >> amount;
    } while (amount % 5 != 0);
    return amount;
}

double getDepositAmount() {
    double DepositAmount;
    do
    {
        cout << "Enter Positive Deposit Amount ? ";
        cin >> DepositAmount;
    } while (DepositAmount < 1);
    return DepositAmount;
}
//Perform Menus Choices
void performMainMenuChoices(enMainMenuChoices choice) {

    switch (choice)
    {
    case enQuickWithdraw:
        system("cls");
        quickWithDrawMenu();
        goBackToMainMenu();
        break;
    case enNormalWithdraw:
        system("cls");
        normalWithdraw();
        goBackToMainMenu();
        break;
    case enDeposit:
        system("cls");
        deposit();
        goBackToMainMenu();
        break;
    case enCheckBalance:
        system("cls");
        checkBalance();
        goBackToMainMenu();
        break;
    case enLogout:
        loginScreen();
        break;
    default:
        goBackToMainMenu();
        break;
    }
  }

void performQuickWithdrawChoices(short choice) {

    if (choice == 9)
    {
        return;
    }

    short withdrawAmount = getQuickWithDrawAmount(choice);

    if (withdrawAmount > LoggedClient.accountBalance)
    {
        cout << "\nThe Amount Exceeds The Balance, Please Make Another Choice.\n";
        cout << "Press Any Key To Continue...";
        system("pause>0");
        quickWithDrawMenu(); 
        return;
    }

    vector<stClients>vClients = loadRecordsFromFile(clientFileName);
    depositBalanceToClientByAccountNumber(withdrawAmount * -1 , LoggedClient.accountNumber, vClients);
    LoggedClient.accountBalance -= withdrawAmount;
}

void performNormalWithdraw() {

    int withdrawAmount = getNormalWithdrawAmount();

    if (withdrawAmount > LoggedClient.accountBalance)
    {
        cout << "\nThe Amount Exceeds The Balance, Please Make Another Choice.\n";
        cout << "Press Any Key To Continue...";
        system("pause>0");
        quickWithDrawMenu();
        return;
    }

    vector<stClients>vClients = loadRecordsFromFile(clientFileName);
    depositBalanceToClientByAccountNumber(withdrawAmount * -1, LoggedClient.accountNumber, vClients);
    LoggedClient.accountBalance -= withdrawAmount;
}

void performDeposit() {

    double depositAmount = getDepositAmount();
    
    vector<stClients>vClients = loadRecordsFromFile(clientFileName);
    depositBalanceToClientByAccountNumber(depositAmount, LoggedClient.accountNumber, vClients);
    LoggedClient.accountBalance += depositAmount;
}

//void performQuickWithDrawChoices(short choice) {
//
//    if (choice > 8 )
//    {
//        quickWithDrawMenu();
//        return;
//    }
//
//    short quickWithdraw[8] = { 20,50,100,200,400,600,800,1000 };
//    LoggedClient.accountBalance -= quickWithdraw[choice - 1];
//}
//Menu
void atmMainMenu() {

    system("cls");

    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Main Menu Screen\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << " Quick Withdraw.\n";
    cout << setw(10) << right << "[2]" << " Normal Withdraw.\n";
    cout << setw(10) << right << "[3]" << " Deposit.\n";
    cout << setw(10) << right << "[4]" << " Check Balance.\n";
    cout << setw(10) << right << "[5]" << " Logout.\n";
    cout << "___________________________________________\n";
    cout << "Choose What You Want To Do? [1 - 5]  ";
    performMainMenuChoices(readMainMenuChoices());

}

void quickWithDrawMenu() {

    system("cls");

    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Quick Withdraw\n";
    cout << "___________________________________________\n\n";

    cout << setw(10) << right << "[1]" << " 20";
    cout << setw(11) << right << "[2]" << " 50\n";
    cout << setw(10) << right << "[3]" << " 100";
    cout << setw(10) << right << "[4]" << " 200\n";
    cout << setw(10) << right << "[5]" << " 400";
    cout << setw(10) << right << "[6]" << " 600\n";
    cout << setw(10) << right << "[7]" << " 800";
    cout << setw(10) << right << "[8]" << " 1000\n";
    cout << setw(10) << right << "[9]" << " Exit.\n";
    cout << "___________________________________________\n";
    cout << "Your Balance is " << LoggedClient.accountBalance;
    cout << "\nChoose what To Withdraw From [1] to [8] ? ";
    performQuickWithdrawChoices(enQuickWithdrawChoices(readQuickWithdrawChoices()));
}

//Login
bool checkAccountNumberAndPinCode(string accountNumber, string pinCode) {
    if (findClientByAccountNumberAndPassword(accountNumber, pinCode, LoggedClient))
        return true;
    else
        return false;
}

void loginScreen() {
    bool loginFailed = false;
    string accountNumber, pinCode;

    do
    {
        system("cls");
        cout << "_______________________________________________________\n";
        cout << "\t\tLogin Screen";
        cout << "\n_______________________________________________________\n";
     
        if (loginFailed)
        {
            cout << "Invalid username / password!\n";
        }
        cout << "Enter Account Number? "; cin >> accountNumber;
        cout << "Enter PIN Code? "; cin >> pinCode;

        loginFailed = !checkAccountNumberAndPinCode(accountNumber,pinCode);

    } while (loginFailed);
    atmMainMenu();
}

int main()
{
    loginScreen();
    system("pause>0");
    return 0;
}


void goBackToMainMenu() {
    cout << "\n\nPress Any Key To Go back To Main Menu...";
    system("pause>0");
    atmMainMenu();
}

void normalWithdraw() {
    system("cls");
    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Normal Withdraw Screen\n";
    cout << "___________________________________________\n\n";
    performNormalWithdraw();
}

void deposit() {
    system("cls");
    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Deposit Screen\n";
    cout << "___________________________________________\n\n";
    performDeposit();
}

void checkBalance() {
    system("cls");

    cout << "___________________________________________\n";
    cout << "\n" << right << setw(28) << "Check Balance Screen\n";
    cout << "___________________________________________\n\n";

    cout << "Your balance is " << LoggedClient.accountBalance << endl;  
}


