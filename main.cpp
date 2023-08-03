#include "FinTracker.h"
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <direct.h>


using namespace std;

int main() {
    bool cont = true;
    DataBase DB;

    //declaring directory
    const char* dir = "C:\FinTracker.db";

    //finding or creating tables
    DB.createDB(dir);
    DB.createExpensesTable(dir);
    DB.createIncomeTable(dir);
    DB.setPlaceHolderValues(dir);


    //INTRODUCTION ----------------------------------------------------------------------------------
    cout << "\n\n\n***********************************************\n";
    cout << "*****  Welcome to your financial tracker  *****\n";
    cout << "***********************************************\n\n";

    FinTracker tracker;
    while(cont) { //while true, continue
        string input = "";
        double amount;
        string desc;
        string cat;
        cout << "\nWhat would you like to do? (Type help to see list of commands):\t";
        cin >> input;

        //help or command list
        if (input == "help" || input == "Help" || input == "HELP") {
            cout << "\nAvailible Commands:\n";
            cout << "addexpense - Add an expense to your financial tracker\n";
            cout << "addincome - Add income to your financial Tracker\n";
            cout << "summary - Print your financial summary\n";
            cout << "breakdown - Prints a breakdown of your spending by category\n";
            cout << "reset - Resets data in application\n";
            cout << "info - Prints Program Information\n";
            cout << "quit - Closes the financial tracker\n";
        }

        //adding an expense
        else if (input == "addexpense") {
            cout << "\nEnter the amount:\t";
            cin >> amount;
            cout << "Enter a brief description of the transaction:\t";
            cin >> desc;
            cout << "Enter the expense category (housing, utilities, transportation, food, medical, personal, entertainment, misc):\t";
            cin >> cat;
            if (cat == "housing") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::housing);
                
            }
            else if (cat == "utilities") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::utilities);
            }
            else if (cat == "transportation") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::transportation);
            }
            else if (cat == "food") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::food);
            }
            else if (cat == "medical") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::medical);
            }
            else if (cat == "personal") {
                tracker.addExpense(dir,amount, desc, ExpenseCategory::personal);
            }
            else if (cat == "entertainment") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::entertainment);
            }
            else if (cat == "misc") {
                tracker.addExpense(dir, amount, desc, ExpenseCategory::misc);
            }
            else {
                cout << "Failed to add expense: Category not recognized";
            }
        }

        //adding income
        else if (input == "addincome") {
            cout << "\nEnter income amount:\t";
            cin >> amount;
            cout << "Enter a brief description:\t";
            cin >> desc;

            tracker.addIncome(dir, amount, desc);
        }

        //print summary
        else if (input == "summary") {
            cout << endl;
            tracker.printSummary(dir);
        }

        //print breakdown (BROKEN)
        else if (input == "breakdown") {
            cout << endl;
            tracker.printCategoryBreakdown(dir);
        }

        //info
        else if (input == "info") {
            tracker.printInfo();
        }

        //reset information
        else if (input == "reset") {
            cout << "Are you sure you want to reset your information? Type IMSURE if sure: ";
            cin >> input;
            if (input == "IMSURE") {
                tracker.resetTables(dir);
                tracker.setPlaceHolderValues(dir);
                cout << "\nProgram Reset\n";
            }
            else {
                cout << "Error: Does not match;";
            }
        }

        //quit
        else if (input == "quit") {
            tracker.deletePlaceHolderValues(dir);
            cout << "\nExiting program.....\n";
            cont = false;
        }

        //command not recognized
        else {
            cout << "\nCommand not recognized ... Remember: the program is case sensitive\n";
        }
    }
    return 0;
}