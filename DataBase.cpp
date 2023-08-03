#include "DataBase.h"
#include "sqlite3.h"
#include <iostream>
#include <string>

using namespace std;


//create or find database
void DataBase::createDB(const char* s) {
	sqlite3* DB;

	int exit = 0;
	try {
		exit = sqlite3_open(s, &DB);
		if (exit != SQLITE_OK) {
			cerr << "Error Creating/Finding Database";
		}
		else {
			cout << "Database Found or Created" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

void DataBase::resetTables(const char* s) {
	sqlite3* DB;
	char* messageError;
	string sql = "DROP TABLE EXPENSES";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Delete " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Exepenses Table Deleted Successfully" << endl;
			createExpensesTable(s);
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
	sql = "DROP TABLE INCOME";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Delete " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Income Table Deleted Successfully" << endl;
			createIncomeTable(s);
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//sets placeholder values for categories that would return null, allowing for a breakdown to be printed
void DataBase::setPlaceHolderValues(const char* s) {
	sqlite3* DB;
	char* messageError;
	string sql = "INSERT INTO EXPENSES (AMOUNT, DESCRIPTION, CATEGORY) VALUES "
		"(0.0, \"Placeholder\", 0),"
		"(0.0, \"Placeholder\", 1),"
		"(0.0, \"Placeholder\", 2),"
		"(0.0, \"Placeholder\", 3),"
		"(0.0, \"Placeholder\", 4),"
		"(0.0, \"Placeholder\", 5),"
		"(0.0, \"Placeholder\", 6),"
		"(0.0, \"Placeholder\", 7)";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Temporary Expenses Records Created Successfully" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
	sql = "INSERT INTO INCOME (AMOUNT, DESCRIPTION) VALUES (0.0, \"Placeholder\");";

	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Temporary Income Records Created Successfully" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//deletes placeholders in the database to avoid overcrowding
void DataBase::deletePlaceHolderValues(const char* s) {
	sqlite3* DB;
	char* messageError;
	string sql = "DELETE FROM EXPENSES WHERE AMOUNT = 0;";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Deleting Placeholders " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Expenses Placeholders Deleted" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
	sql = "DELETE FROM INCOME WHERE AMOUNT = 0;";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Deleting Placeholders " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Income Placeholders Deleted" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//create expenses table 
void DataBase::createExpensesTable(const char* s) {
	sqlite3* DB;

	string sql = "CREATE TABLE IF NOT EXISTS EXPENSES("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"AMOUNT			DECIMAL NOT NULL, "
		"DESCRIPTION	TEXT NOT NULL, "
		"CATEGORY		INT NOT NULL);";
	try {
		int exit = 0;
		exit = sqlite3_open(s, &DB);

		char* messageError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			cerr << "Error Creating/Finding Table";
			sqlite3_free(messageError);
		}
		else {
			cout << "Expenses Table Found or Created\n";
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//create income table
void DataBase::createIncomeTable(const char* s) {
	sqlite3* DB;
	
	string sql = "CREATE TABLE IF NOT EXISTS INCOME("
		"ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"AMOUNT			DECIMAL NOT NULL, "
		"DESCRIPTION	TEXT NOT NULL); ";
	try {
		int exit = 0;
		exit = sqlite3_open(s, &DB);

		char* messageError;
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

		if (exit != SQLITE_OK) {
			cerr << "Error Creating Table";
			sqlite3_free(messageError);
		}
		else {
			cout << "Income Table Found or Created" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception & e) {
		cerr << e.what();
	}
}


//add income
void DataBase::insertIncome(const char* s, double amount, string source) {
	sqlite3* DB;
	char* messageError;
	string sql = "INSERT INTO INCOME (AMOUNT, DESCRIPTION) VALUES (" + to_string(amount) + ", \"" + source + "\");";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Records Created Successfully" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//add expense
void DataBase::insertExpense(const char* s, double amount, string source, int category) {
	sqlite3* DB;
	string sql = "INSERT INTO EXPENSES (AMOUNT, DESCRIPTION, CATEGORY) VALUES (" + to_string(amount) + ", \"" + source + "\", " + to_string(category) + "); ";
	try {
		char* messageError;
		int exit = sqlite3_open(s, &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Error Insert " << messageError << endl;
			sqlite3_free(messageError);
		}
		else {
			cout << "Records Created Successfully" << endl;
		}
		sqlite3_close(DB);
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}

//sum a column of the database. used to get totals 
double DataBase::sumOfColumn(const char* s, string tableName, string columnName) {
	sqlite3* DB;
	try {
		char* messageError = nullptr;
		double result = 0;

		int rc = sqlite3_open(s, &DB);
		if (rc != SQLITE_OK) {
			std::cerr << "Cannot open database: " << sqlite3_errmsg(DB) << std::endl;
			sqlite3_close(DB);
			return result;
		}

		std::string sql = "SELECT SUM(";
		sql += columnName;
		sql += ") FROM ";
		sql += tableName;

		// Execute the SQL statement
		rc = sqlite3_exec(DB, sql.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
			double* result = static_cast<double*>(data);
			*result = atof(argv[0]); // Convert the sum result to double and store it
			return 0;
			}, &result, &messageError);


		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << messageError << std::endl;
			sqlite3_free(messageError);
		}

		sqlite3_close(DB);

		return result;
	} 
	catch (const exception& e) {
		cerr << e.what();
	}
}

//sum of categories used to make breakdown
double DataBase::sumOfCategory(const char* s, string tableName, string columnName, string cat) {
	sqlite3* DB;
	try {
		char* messageError = nullptr;
		double result = 0;

		int rc = sqlite3_open(s, &DB);
		if (rc != SQLITE_OK) {
			std::cerr << "Cannot open database: " << sqlite3_errmsg(DB) << std::endl;
			sqlite3_close(DB);
			return result;
		}


		std::string sql = "SELECT SUM(" + columnName + ") FROM EXPENSES WHERE CATEGORY=" + cat + ";";

		// Execute the SQL statement
		rc = sqlite3_exec(DB, sql.c_str(), [](void* data, int argc, char** argv, char** azColName) -> int {
			double* result = static_cast<double*>(data);
			*result = atof(argv[0]); // Convert the sum result to double and store it
			return 0;
			}, &result, &messageError);


		if (rc != SQLITE_OK) {
			std::cerr << "SQL error: " << messageError << std::endl;
			sqlite3_free(messageError);
		}

		sqlite3_close(DB);

		return result;
	}
	catch (const exception& e) {
		cerr << e.what();
	}
}
