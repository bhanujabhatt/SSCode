#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <time.h>  // For the time_t type

// Structure to store customer feedback information
struct Feedback {
    int feedbackID;              // Unique ID for feedback
    int customerID;              // Reference to customer
    char feedbackText[500];      // Feedback message
    time_t date;                 // Date and time of feedback submission
};
