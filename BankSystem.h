#ifndef BANK_BANKSYSTEM_H
#define BANK_BANKSYSTEM_H

#include <bits/stdc++.h>

using namespace std;

class BankAccount;

class SavingBankAccount;

class Client {
private:
    string clientName, clientAddress, clientNumber, clientID = "FCAI-";
    BankAccount *clientBankAccount = nullptr;
    SavingBankAccount *clientSavingBankAccount = nullptr;
public:
    Client(int ID);

    string getClientName();

    string getClientAddress();

    string getClientNumber();

    string getClientID();

    BankAccount *getBankAccount();

    SavingBankAccount *getSavingBankAccount();

    void setClientAddress(Client &clientPointer);
};

class BankSystem {
public:
    void listClients(vector<Client> clients);

    int getIndex(string ID);

    void start();
};

class BankAccount {
private:
    double balance = -1;
    Client *linkedClient;
public:
    void setBalance(double newBalance);

    void setClient(Client *clientPointer);

    double getBalance();

    void withdraw();

    void deposit();
};

class SavingBankAccount : public BankAccount {
private:
    double balance = 0;
    Client *linkedClient;
public:
    void setSavingBalance(double newBalance);

    void setSavingClient(Client *clientPointer);

    double getSavingBalance();

    void savingWithdraw();

    void savingDeposit();
};

#endif //BANK_BANKSYSTEM_H