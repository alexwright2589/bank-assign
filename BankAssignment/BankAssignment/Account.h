#pragma once
#include <windows.h>
#include <vector>
#include <string> 
#include <sstream>
#include <iostream>
#include "Transactions.h"
using namespace std;

class Account
{
public:
	string summary;
	int accountID;
	string accounttype;
	double balance;
	vector<Transaction> history;
	virtual double GetBalance(int years) = 0;
	virtual double withdraw(double trans) = 0;
	virtual double deposit(double trans) = 0;
	/// ^^Defining the template of an account is made up and the methods it consists of
	virtual string toString()
	{
		string summary = (+"\naccount ID is: " + to_string(accountID)) + ("\nbalance is: " + to_string(balance)) + ("\naccount type is " + accounttype);
		
		for (int i = 0; i < history.size(); i++)
		{
			summary += history[i].toString();
		}
		return summary;
	}
	/// ^^ this is the base toString methods which only converts accountID balance and account type(As all accounts have these attributes)
};