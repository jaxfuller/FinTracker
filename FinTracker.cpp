#include "FinTracker.h"
#include <iostream>
#include <iomanip> // For std::setprecision

FinTracker::FinTracker() : totalExpenses(0.0), totalIncome(0.0) {
    // Initialize expenseCategories with 0 for each category
    for (int i = static_cast<int>(ExpenseCategory::housing); i <= static_cast<int>(ExpenseCategory::misc); i++) {
        ExpenseCategory category = static_cast<ExpenseCategory>(i);
        expenseCategories[category] = 0.0;
    }
}

//add expense
void FinTracker::addExpense(const char* dir, double amount, const std::string& source, ExpenseCategory category) {
    insertExpense(dir, amount, source, static_cast<int>(category));
    std::cout << "Expense added: $" << amount << " - " << source << " (Category: " << static_cast<int>(category) << ")" << std::endl;
}

//add income
void FinTracker::addIncome(const char* dir, double amount, const std::string& source) {
    insertIncome(dir, amount, source);
    std::cout << "Income added: $" << amount << " - " << source << std::endl;
}

//get total expenses 
double FinTracker::getTotalExpenses(const char* dir) const {
    return sumOfColumn(dir, "EXPENSES", "AMOUNT");
}

//get total income
double FinTracker::getTotalIncome(const char* dir) const {
    return sumOfColumn(dir, "INCOME", "AMOUNT");
}

//get net balance
double FinTracker::getNetBalance(const char* dir) const {
    return getTotalIncome(dir) - getTotalExpenses(dir);
}

//get housing total
double FinTracker::getHousingTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "0");
}

//get utilities total
double FinTracker::getUtilitiesTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "1");
}

//get Transportation Total
double FinTracker::getTransportationTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "2");
}

//get Food Total
double FinTracker::getFoodTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "3");
}
double FinTracker::getMedicalTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "4");
}

//get personal total
double FinTracker::getPersonalTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "5");
}

//get entertainment total
double FinTracker::getEntertainmentTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "6");
}

//get misc total
double FinTracker::getMiscTotal(const char* dir) const {
    return sumOfCategory(dir, "EXPENSES", "AMOUNT", "7");
}

//print summary of income and expenses, including net
void FinTracker::printSummary(const char* dir) const {
    std::cout << "Financial Summary" << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Total Income: $" << getTotalIncome(dir) << std::endl;
    std::cout << "Total Expenses: $" << getTotalExpenses(dir) << std::endl;
    std::cout << "Net Balance: $" << getNetBalance(dir) << std::endl;
}


//expense category breakdown (expense - $amount - percentage of total)
void FinTracker::printCategoryBreakdown(const char* dir) const {
    std::cout << "Expense Category Breakdown" << std::endl;
    std::cout << "-------------------------" << std::endl;
    double percentage = getHousingTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Housing:\t " << getHousingTotal(dir) << " - " << percentage << "%\n";
    percentage = getUtilitiesTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Utilities:\t " << getUtilitiesTotal(dir) << " - " << percentage << "%\n";
    percentage = getTransportationTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Transportation:\t " << getTransportationTotal(dir) << " - " << percentage << "%\n";
    percentage = getFoodTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Food:\t\t " << getFoodTotal(dir) << " - " << percentage << "%\n";
    percentage = getMedicalTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Medical:\t " << getMedicalTotal(dir) << " - " << percentage << "%\n";
    percentage = getPersonalTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Personal:\t " << getPersonalTotal(dir) << " - " << percentage << "%\n";
    percentage = getEntertainmentTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Entertainment:\t " << getEntertainmentTotal(dir) << " - " << percentage << "%\n";
    percentage = getMiscTotal(dir) / getTotalExpenses(dir) * 100;
    std::cout << "Misc:\t\t " << getMiscTotal(dir) << " - " << percentage << "%\n";
}

//prints program information
void FinTracker::printInfo() const {
    std::cout << "\nPersonal Finance Tracker Version 0.1";
    std::cout << "\nBuilt by Jackson Fuller for CSC1061\n";
}