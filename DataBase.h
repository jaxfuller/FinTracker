#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>

using namespace std;

class DataBase
{
public:
	static void createDB(const char* s);
	static void createExpensesTable(const char* s);
	static void createIncomeTable(const char* s);
	static void resetTables(const char* s);
	static void setPlaceHolderValues(const char* s);
	static void deletePlaceHolderValues(const char* s);
	static void insertIncome(const char* s, double amount, string source);
	static void insertExpense(const char* s, double amount, string desc, int category);
	static double sumOfColumn(const char* s, string tableName, string columnName);
	static double sumOfCategory(const char* s, string tableName, string columnName,string cat);
};

#endif