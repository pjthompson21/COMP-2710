/**
 * Parker Thompson
 * project1_Thompson_pjt0012.cpp
 * compilation instructions: g++ -o project1_Thompson_pjt0012.cpp
 * Program that calculates the amount of months it will take for a
 * user inputted loan to be payed off. 
 * 
 * REFERENCES:
 * I utilized the project hints provided in the files section
 * on Canvas to help me complete this project.  
 * I searched on Stack Overflow how to handle incorrect data type
 * inputs (https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input).
 **/

#include <iostream>
#include <iomanip>
using namespace std; 

int main() {

    //instance variables
    float loanAmount = 0;
    float monthlyPay = 0;
    float interestRate = 0;
    float interestRateP = 0;
    float interest = 0;
    float interestTotal = 0;
    float principal;
    int currentMonth = 0;
    

    //decimal format
    cout << fixed << showpoint << setprecision(2);
    

    //user input
    cout << "\n";
    bool validLoan = false;
    while (!validLoan) {
        
        validLoan = true; 
        cout << "Loan Amount: ";
        cin >> loanAmount;

        if (loanAmount < 0) {
            cin.clear();
            cin.ignore();
            cout << "(Invalid loan) ";
            validLoan = false;
        }
        else if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "(Invalid loan) ";
            validLoan = false; 
        }
    }
    

    bool validItrRte = false;
    while (!validItrRte) {
        validItrRte = true;
        cout << "Interest Rate (% per year): ";
        cin >> interestRate;

        if (interestRate < 0) {
            cin.clear();
            cin.ignore();
            cout << "(Invalid interest rate) ";
            validItrRte = false;
        }
        else if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "(Invalid interest rate) ";
            validItrRte = false; 
        }
    }


    interestRate /= 12;
    interestRateP = interestRate / 100;
    interest = loanAmount * interestRateP;

    bool validMthPay = false; 
    while (!validMthPay) {
        validMthPay = true; 
        cout << "Monthly Payments: ";
        cin >> monthlyPay;

        if (monthlyPay < 0) {
            cin.clear();
            cin.ignore();
            cout << "(Invalid payment) ";
            validMthPay = false; 
        }
        else if (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "(Invalid payment) ";
            validMthPay = false;
        }
        else if (monthlyPay <= interest) {
            cin.clear();
            cin.ignore();
            cout << "(Enter a larger monthly payment amount) ";
            validMthPay = false;
        }
        
    }


    //amortization table 
    cout << "*****************************************************************\n"
         << "\tAmortization Table\n"
         << "*****************************************************************\n"
         << "Month\tBalance\t\tPayment\tRate\tInterest\tPrincipal\n"
         << currentMonth << "\t$" << loanAmount << "\tN/A\tN/A\tN/A\t\tN/A\n";666
    

    while (loanAmount > 0) {

        currentMonth++;
        interest = loanAmount * interestRateP;
        interestTotal += interest;

        if (monthlyPay > (loanAmount + interest)) {
            monthlyPay = loanAmount + interest;
        }

        principal = monthlyPay - interest;
        loanAmount -= principal;

        //formats amortization table when loans are greater than $1000.
        if (loanAmount >= 1000) {
            cout << currentMonth << "\t$" << loanAmount << "\t$"
                 << monthlyPay << "\t" << interestRate << "\t$"
                 << interest << "\t\t$" << principal << "\n";
        }
        else {
            cout << currentMonth << "\t$" << loanAmount << "\t\t$"
                 << monthlyPay << "\t" << interestRate << "\t$"
                 << interest << "\t\t$" << principal << "\n";
        }
    }


    cout << "****************************************************************\n"
        << "\nIt takes " << currentMonth << " months to pay off the loan.\n"
        << "Total interest paid is: $" << interestTotal;
    cout << endl << endl;
    return 0;
}