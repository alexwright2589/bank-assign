#pragma once
#include<sstream>  
#include "Account.h"
#include <string>
#include "InterestEarning.h"
#include <windows.h>
#include <vector>
using namespace std;
class Current : public Account
{
public:
	double overdraft;
	int numberoftrans = 0;
	/// ^^^The extra variables needed in order to define a current account
	int blnce;

	
	Current(string str2, int str3)
	{
		accountID = str3;
		balance = stod(str2);
		accounttype = "Current Account";
		overdraft = 500.000;
	};
	/// ^^^setting the predefined attributes of an account also assigning values to the new attributes we have defined above to the relevant 
	double withdraw(double trans)
	{
		try
		{
			if (overdraft + balance >= trans)
			{
				if (balance >= trans)
				{
					numberoftrans++;
					history.push_back(Transaction(1, trans));
					balance = (balance - trans);
					cout << ("\nYour new balance for account" + to_string(accountID) + " is:" + to_string(balance)) << endl;
					return balance;
				}
				else
				{
					history.push_back(Transaction(1, trans));
					trans = (trans - balance);
					balance = 0.000;
					overdraft = (overdraft - trans);
					cout << ("\nYour new balance for account" + to_string(accountID) + " is:" + to_string(balance)) << endl;
					cout << ("Your remaining overdraft is:" + to_string(overdraft)) << endl;
					return(balance + overdraft);

				};
			}
			/// ^^^If statement to check you have enough money with try and catch for exception handling then nested if to see wether it should take the money from just your balance or overdraft aswell
			/// Then creates a transaction and stores it in history sets the new balance and overdraft if needed outputs relevant info returns balance
			else
			{
				throw(trans);
			};
		
		}
		catch (double trans)
		{
			cout << "Combining your balance and overdraft you have not got enough money in your account to make this withdrawal" << endl;
			return false;
		}
		/// ^^^catches trans if the required withdrawal is too much for your balance and overdraft outputs relevent error message
	};
	double deposit(double trans)
	{
		history.push_back(Transaction(2, trans));
		balance = (balance + trans);
		cout << ("\nYour new balance is:" + to_string(balance)) << endl;
		return balance;
	}
	/// ^^^similar to withdraw except no checks are needed because your adding money not taking it away
	string toString()
	{
		
		string summary = (+"\nAccount ID is: " + to_string(accountID)) + ("\nBalance is: " + to_string(balance)) + ("\nAccount type is: " + accounttype) + ("\nYour current overdraft left is: " + to_string(overdraft));
		for (int i = 0; i < history.size(); i++)
		{
			summary += history[i].toString();
		}
		return summary;
	}
	/// ^^^The more advanced toString methods adding overdraft into the output and also outputting the transaction history
	
	
	double GetBalance(int str1)
	{
		return NULL;
	}

};