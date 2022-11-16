#include "BankSystem.h"

// client--------------------------------------------------------------------------------------------------------------

Client::Client(int ID) {
    string tempID = "";
    for (int i = 0; i < 3; ++i) {
        tempID += '0' + (ID % 10);
        ID /= 10;
    }
    reverse(tempID.begin(), tempID.end());
    clientID += tempID;
    cout << "Please Enter Client Name =========> ";
    cin.ignore();
    getline(cin, clientName);
    cout << "Please Enter Client Address =========> ";
    getline(cin, clientAddress);
    cout << "Please Enter Client Number =========> ";
    getline(cin, clientNumber);
    cout << "What Type of Account Do You Like? (1) Basic (2) Saving - Type 1 or 2 =========> ";
    int bankType;
    double clientBalance = -1;
    cin.clear();
    cin.sync();
    cin >> bankType;
    cout << "Please Enter the Starting Balance =========> ";
    cin >> clientBalance;
    if (bankType == 1) {
        while (clientBalance < 0) {
            cout << "\nBalance has to be at least 0 please try again\n\n";
            cout << "Please Enter the Starting Balance =========> ";
            cin >> clientBalance;
        }
        clientBankAccount = new BankAccount;
        clientBankAccount->setBalance(clientBalance);
        clientBankAccount->setClient(this);
        cout << "An account was created with ID " << clientID << " and Starting Balance "
             << clientBankAccount->getBalance() << " L.E. \n";
    } else {
        while (clientBalance < 1000) {
            cout << "\nBalance has to be at least 1000 please try again\n\n";
            cout << "Please Enter the Starting Balance =========> ";
            cin >> clientBalance;
        }
        clientSavingBankAccount = new SavingBankAccount;
        clientSavingBankAccount->setSavingBalance(clientBalance);
        clientSavingBankAccount->setSavingClient(this);
        cout << "An account was created with ID " << clientID << " and Starting Balance "
             << clientSavingBankAccount->getBalance() << " L.E. \n";
    }

    cout << "-------------------------------------------------------------------\n";
}

string Client::getClientName() {
    return clientName;
}

string Client::getClientAddress() {
    return clientAddress;
}

string Client::getClientNumber() {
    return clientNumber;
}

string Client::getClientID() {
    return clientID;
}

BankAccount *Client::getBankAccount() {
    return clientBankAccount;
}

SavingBankAccount *Client::getSavingBankAccount() {
    return clientSavingBankAccount;
}

// Bank system---------------------------------------------------------------------------------------------------------

void BankSystem::listClients(vector<Client> clients) {
    for (int i = 0; i < clients.size(); ++i) {
        cout << "-------------------------- " << clients[i].getClientName() << " --------------------------\n";
        cout << "Address: " << clients[i].getClientAddress() << '\n';
        cout << "Phone: " << clients[i].getClientNumber() << '\n';
        cout << "Account ID: " << clients[i].getClientID() << ' ';
        if (clients[i].getBankAccount() == nullptr) {
            cout << "(Saving)\n";
            cout << "Balance: " << clients[i].getSavingBankAccount()->getBalance() << '\n';
        } else {
            cout << "(Basic)\n";
            cout << "Balance: " << clients[i].getBankAccount()->getBalance() << '\n';
        }
    }
    cout << "-------------------------------------------------------------------\n";
}

int BankSystem::getIndex(string ID) {
    int index = 0;
    index += ID[ID.length() - 1] - '0';
    index += (ID[ID.length() - 2] - '0') * 10;
    index += (ID[ID.length() - 3] - '0') * 100;
    return index;
}

void BankSystem::start() {
    cout << "Welcome to FCAI Banking Application\n";
    int userChoice;
    vector<Client> clients;
    while (true) {
        cout << "1. Create a New Account\n";
        cout << "2. List Clients and Accounts\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Deposit Money\n\n";
        cout << "Please Enter Choice =========> ";
        cin >> userChoice;
        if (userChoice == 1) {
            Client newClient(clients.size());
            clients.push_back(newClient);
        } else if (userChoice == 2) {
            listClients(clients);
        } else if (userChoice == 3) {
            string ID;
            cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
            cin >> ID;
            if (clients[getIndex(ID)].getSavingBankAccount() == nullptr) {
                clients[getIndex(ID)].getBankAccount()->withdraw();
            } else {
                clients[getIndex(ID)].getSavingBankAccount()->savingWithdraw();
            }
        } else if (userChoice == 4) {
            string ID;
            cout << "Please Enter Account ID (e.g., FCAI-015) =========> ";
            cin >> ID;
            if (clients[getIndex(ID)].getSavingBankAccount() == nullptr) {
                clients[getIndex(ID)].getBankAccount()->deposit();
            } else {
                clients[getIndex(ID)].getSavingBankAccount()->savingDeposit();
            }
        } else {
            cout << "\nPlease enter a valid option\n\n";
        }
    }
}

// Bank account--------------------------------------------------------------------------------------------------------

void BankAccount::setBalance(double newBalance) {
    if (newBalance < 0) {
        cout << "Balance has to be at least 0 please try again";
        return;
    }
    balance = newBalance;
}

void BankAccount::setClient(Client *clientPointer) {
    linkedClient = clientPointer;
}

double BankAccount::getBalance() {
    return balance;
}

void BankAccount::withdraw() {
    double withdrawMoney;
    cout << "Please Enter The Amount to Withdraw =========> ";
    cin >> withdrawMoney;
    if(withdrawMoney < 0){
        cout << "\nMoney has to be at least 0\n\n";
        withdraw();
        return;
    }
    else if(withdrawMoney > balance){
        cout << "\nWithdraw money can't be more than balance\n\n";
        withdraw();
        return;
    }
    balance -= withdrawMoney;
}

void BankAccount::deposit() {
    double depositMoney;
    cout << "Please Enter The Amount to Deposit =========> ";
    cin >> depositMoney;
    if(depositMoney < 0){
        cout << "\nMoney has to be at least 0\n\n";
        deposit();
        return;
    }
    balance += depositMoney;
}

// Saving bank account-------------------------------------------------------------------------------------------------

void SavingBankAccount::setSavingBalance(double newBalance) {
    if (newBalance < 1000) {
        cout << "\nBalance has to be at least 1000 please try again\n\n";
        return;
    }
    setBalance(newBalance);
    balance = getBalance();
}

void SavingBankAccount::setSavingClient(Client *clientPointer) {
    setClient(clientPointer);
};

double SavingBankAccount::getSavingBalance() {
    getBalance();
}

void SavingBankAccount::savingWithdraw() {
    double withdrawMoney;
    cout << "Please Enter The Amount to Withdraw =========> ";
    cin >> withdrawMoney;
    if(withdrawMoney < 0){
        cout << "\nMoney has to be at least 0\n\n";
        savingWithdraw();
        return;
    }
    else if(balance-withdrawMoney < 1000){
        cout << "\nBalance can't be less than minimum balance (1000)\n\n";
        savingWithdraw();
        return;
    }
    balance -= withdrawMoney;
    setBalance(balance);
}

void SavingBankAccount::savingDeposit() {
    double depositMoney;
    cout << "Please Enter The Amount to Deposit =========> ";
    cin >> depositMoney;
    if(depositMoney < 100){
        cout << "\nMoney has to be at least 100\n\n";
        savingDeposit();
        return;
    }
    balance += depositMoney;
    setBalance(balance);
}