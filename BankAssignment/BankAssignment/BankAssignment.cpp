#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <windows.h>
#include <iostream>
#include <vector>
#include "Account.h"
#include "Currrent.h"
#include "Savings.h"
#include "Transactions.h"


int main()
{
	std::vector <std::string> parameters;
	std::string userCommand;
	std::string paramcheck;
	std::string acctype;
	double account = 0;
	std::string blnce;
	std::string command;
	std::vector <Account*> Accounts;
	int acc = 0;
	int accID = 0;
	int numberofaccounts = 0;
	int numberoftransactions = 0;
	int currentcheck = 0;
	int isacheck = 0;


	// you may also want to store a collection of opened accounts here

	std::cout << "~~~ Welcome to LincBank! ~~~" << std::endl;
	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		std::cout << "\n\nWhat would you like to do? If unsure type 'options'" << std::endl;
		std::cout << std::endl << ">>> ";

		std::getline(std::cin, userCommand);
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		try 
		{
			if ((parameters.size() >= 1) && (parameters.size() <= 4))
			{
				if (parameters.size() == 1) 
				{
					command = parameters[0];
				}
				else if (parameters.size() == 2)
				{
					command = parameters[0];
					acctype = parameters[1];
				}
				else
				{
					command = parameters[0];
					acctype = parameters[1];
					blnce = parameters[2];
				}
			}
			else 
			{
				paramcheck = userCommand; //did this so others wouldnt catch 
				throw(paramcheck);
			}
		}
		/// ^^^ a quick simple try and catch to ensure the user hasnt inputted more than the max amount of paranthesis needed
		catch (string paramcheck) 
		{
			std::cout << "You have inputted too many parameters\nThe data you inputted was: " << paramcheck << std::endl;
		}
		//^^^ relevant error message
		try 
		{
			if ((command.compare("options") == 0) && (parameters.size() == 1))
			{
				std::cout << "\nThe options are presented below with the exact format you must enter your choice in before each explanation\n" << std::endl;
				std::cout << "1. open type initial_deposit: -> open a current (1), savings (2) or ISA (3) account \n2. view [index]: -> view balance and recent transactions\n3. withdraw sum: -> withdraw funds from most recently viewed account\n4. deposit sum: -> deposit funds into most recently viewed account\n5. transfer src dest sum: -> transfer funds between accounts\n6. project years: -> project balance forward in time\n7. exit: -> close this application\n8. options: -> view these options again" << std::endl;

			}
			//^^^Simple output for the options just an array of options, can only enter this if statement if 'options' is the only input due to the .size check
			else if (command.compare("open") == 0 && (stoi(parameters[1]) >= 1) && (stoi(parameters[1]) <= 3))
			{
				if (stod(acctype) == 1)
				{
					if (currentcheck >= 1)
					{
						std::cout << "\nYou already have a current account you can only have one!" << std::endl;
						continue;
					}
					else
					{
						numberofaccounts++;
						accID++;
						Accounts.push_back(new Current(parameters[2], accID));
						currentcheck++;
					}
				}
				//^^^ creates the current account but also checks to ensure you dont already have one as you are only aloud one current account
				else if (stod(acctype) == 2)
				{
					numberofaccounts++;
					accID++;
					Accounts.push_back(new Savings(parameters[1], parameters[2], accID));
				}
				//^^^ creates a regular savings account
				else if ((stod(acctype) == 3) && (stod(blnce) >= 1000))
				{
					if (isacheck >= 1)
					{
						std::cout << "\nYou already have an ISA account you can only have one!" << std::endl;
						continue;
					}
					else
					{
						numberofaccounts++;
						accID++;
						Accounts.push_back(new Savings(parameters[1], parameters[2], accID));
						isacheck++;
					}
				}
				else 
				{
					numberofaccounts--;
					std::cout << "You must open an isa with 1000 pounds or more!\nPlease try again" << std::endl;
				}
				//^^^Creates the ISA account only if the user has entered a balance of over £1000
			}


			else if (command.compare("view") == 0)
			{
				if (numberofaccounts > 0)
				{
					if (parameters.size() == 2)
					{
						std::cout << "\n" << Accounts.at(stod(parameters[1])-1)->toString();
						account = stod(parameters[1]);
					}
					else 
					{
						for (int i = 0; i < numberofaccounts; i++)
						{
							std::cout << "\n"<<Accounts.at(i)->toString();
						}
					}

				}
				else
				{
					std::cout << "You have no accounts to view" << std::endl;
				}

				// ^^^This displays an account according to an index (starting from 1) checks to ensure there are account to view first
				// alternatively, this display all accounts if no index is provided
			}
			else if (command.compare("withdraw") == 0 && (stoi(parameters[1]) > 0))
			{
				if (parameters.size() == 2 && account != 0)
				{
					Accounts.at(account - 1)->withdraw(stod(parameters[1]));
				}
				else
				{
					std::cout << "You must view the account you want to withdraw from first or you have entered invalid parameters size" << std::endl;
				}
				//^^^This allows user to withdraw funds from an account only if they have selected an account first by viewing it
			}
			else if (command.compare("deposit") == 0 && (stoi(parameters[1]) > 0))
			{
				if (parameters.size() == 2 && account != 0)
				{
					Accounts.at(account - 1)->deposit(stod(parameters[1]));
				}
				else
				{
					std::cout << "You must view the account you want to withdraw from first or you have entered invalid parameters size" << std::endl;
				}
				//^^^ This allows the user to deposit funds into an account same only if they have viewed it
			}
			else if (command.compare("transfer") == 0 && (parameters.size() == 4))
			{
				try 
				{
					if (Accounts.at((stod(parameters[1])) - 1)->withdraw(stod(parameters[3])) == false)
					{
						throw(parameters[1]);
					}
					else 
					{
						Accounts.at((stod(parameters[2])) - 1)->deposit(stod(parameters[3]));
						std::cout << "\nSuccessful transfer" << std::endl;
					}
				}
				catch (string parameters[1])
				{
					std::cout << "You do not have enough money in the first account to do this" << std::endl;
				}


				//^^^This allows the user to transfer funds between accounts
				// i.e., a withdrawal followed by a deposit but it must check that there is enough money in the first account before it does this
			}
			else if (command.compare("project") == 0 && parameters.size() <= 2)
			{
				Accounts.at(account-1)->GetBalance(stoi(parameters[1]));
				//^^This computes the compound interest t years into the future
			}
			else if (command.compare("search") == 0)
			{
				
			}
			//else if (command.compare("search"))
			//{
			//	allow users to search their account history for a transaction
			//  (this is a stretch task)
			//}
			else
			{
				throw(userCommand);
			}
			//^^^ if none of the above conditions are met it will simply execute the catch command and outputs a relevant error message below
		}
		catch (string userCommand)
		{
			std::cout << "You have inputted wrong data please try again" << std::endl;
		}

	}
	for (auto Account : Accounts)
	{
		delete Account;
	}
	//^^^ This delets all the accounts once the program is over or exited

	std::cout << "Press any key to quit...";
	std::getchar();
}