#ifndef FINTRACKER_H
#define FINTRACKER_H

#include <string>
#include <unordered_map>
#include "DataBase.h"

enum class ExpenseCategory {
    housing,
    utilities,
    transportation,
    food,
    medical,
    personal,
    entertainment,
    misc
};

class FinTracker: public DataBase {
public:
    FinTracker();
    void addExpense(const char* dir, double amount, const std::string& description, ExpenseCategory category);
    void addIncome(const char* dir, double amount, const std::string& source);
    double getTotalExpenses(const char* dir) const;
    double getTotalIncome(const char* dir) const;
    double getNetBalance(const char* dir) const;
    double getHousingTotal(const char* dir) const;
    double getUtilitiesTotal(const char* dir) const;
    double getTransportationTotal(const char* dir) const;
    double getFoodTotal(const char* dir) const;
    double getMedicalTotal(const char* dir) const;
    double getPersonalTotal(const char* dir) const;
    double getEntertainmentTotal(const char* dir) const;
    double getMiscTotal(const char* dir) const;
    void printSummary(const char* dir) const;
    void printCategoryBreakdown(const char* dir) const;
    void printInfo() const;

private:
    double totalExpenses;
    double totalIncome;
    std::unordered_map<ExpenseCategory, double> expenseCategories;
};

#endif  // FINTRACKER_H