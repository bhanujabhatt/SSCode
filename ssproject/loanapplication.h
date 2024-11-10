#ifndef LOAN_H
#define LOAN_H

// Structure to store loan application information
struct LoanApplication {
    int loanID;                 // Unique ID for each loan application
    int customerID;             // Reference to the customer applying for the loan
    float loanAmount;           // Requested loan amount
    char status[20];            // Loan status: Pending, Approved, Rejected
};
