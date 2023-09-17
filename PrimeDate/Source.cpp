#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include "PrimeUtils.h"

/**
 * Increment the date by one day.
 * @param date - The current date which will be incremented.
 * @param end_date - The end date to check if the incremented date hasn't exceeded it.
 * @return true if the incremented date is before or on the end_date, otherwise false.
 */
bool incrementDate(std::tm& date, const std::tm& end_date) {
    // Days in each month.
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Increment the day.
    date.tm_mday++;

    // If day exceeds the month's days, reset day to 1 and move to next month.
    // Also handle leap year for February.
    if (date.tm_mday > daysInMonth[date.tm_mon] + ((date.tm_mon == 1 && date.tm_year % 4 == 0 && (date.tm_year % 100 != 0 || (date.tm_year + 1900) % 400 == 0)) ? 1 : 0)) {
        date.tm_mday = 1;
        date.tm_mon++;

        // If month exceeds 11 (December), reset month to 0 (January) and move to next year.
        if (date.tm_mon > 11) {
            date.tm_mon = 0;
            date.tm_year++;
        }
    }

    // Check if the current date exceeds the end date.
    return !(date.tm_year > end_date.tm_year ||
        (date.tm_year == end_date.tm_year && date.tm_mon > end_date.tm_mon) ||
        (date.tm_year == end_date.tm_year && date.tm_mon == end_date.tm_mon && date.tm_mday > end_date.tm_mday));
}

/**
 * Parse the date from a string.
 * @param input - The input string in format YYYY-MM-DD.
 * @param date - The parsed date will be stored in this variable.
 * @return true if parsing was successful, otherwise false.
 */
bool parseDate(const std::string& input, std::tm& date) {
    std::istringstream ss(input);
    char delimiter;
    return (ss >> date.tm_year >> delimiter >> date.tm_mon >> delimiter >> date.tm_mday) && delimiter == '-' && !ss.fail();
}

int main() {
    while (true) {
        std::string startStr, endStr;

        // Prompt user to enter a start date or exit the program.
        std::cout << "Enter the start date in the format YYYY-MM-DD or type 'quit' or 'q' or an empty string to exit: ";
        std::getline(std::cin, startStr);
        if (startStr == "quit" || startStr == "q" || startStr == "") {
            break;
        }

        // Prompt user to enter an end date.
        std::cout << "Enter the end date in the format YYYY-MM-DD or type 'quit' or 'q' or an empty string to exit: ";
        std::getline(std::cin, endStr);
        if (endStr == "quit" || endStr == "q" || endStr == "") {
            break;
        }
        // Parse the start and end dates.
        std::tm startDate = {}, endDate = {};
        if (!parseDate(startStr, startDate) || !parseDate(endStr, endDate)) {
            std::cout << "Invalid date format. Please try again." << std::endl;
            continue;
        }

        // Adjust year values (tm_year is years since 1900).
        startDate.tm_year -= 1900;
        endDate.tm_year -= 1900;

        // Adjust month values (tm_mon is 0-11).
        startDate.tm_mon--;
        endDate.tm_mon--;

        // Loop through each date between start and end dates and check for prime dates.
        while (incrementDate(startDate, endDate)) {
            // Calculate the numeric representation of the date.
            int number = (startDate.tm_year + 1900) * 10000 + (startDate.tm_mon + 1) * 100 + startDate.tm_mday;

            // Check if the date is prime and display it.
            if (isPrime(number))
                std::cout << startDate.tm_mday << "/" << startDate.tm_mon + 1 << "/" << startDate.tm_year + 1900 << " (" << number << ") is a prime date." << std::endl;
        }
    }

    return 0;
}
