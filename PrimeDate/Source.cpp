#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include "PrimeUtils.h"

/**
 * Increment the provided date by one day.
 *
 * @param date - Reference to a std::tm object representing the current date.
 * @param end_date - Reference to a std::tm object representing the end date.
 *
 * @return - Returns true if the date is successfully incremented and remains within the given end date.
 *           Returns false once the date surpasses the end date.
 */
bool incrementDate(std::tm& date, const std::tm& end_date) {
    // An array storing the number of days in each month.
    static const int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    date.tm_mday++;  // Increment the day

    // Check if the day exceeds the maximum day of the month, considering leap years for February.
    if (date.tm_mday > daysInMonth[date.tm_mon] + ((date.tm_mon == 1 && date.tm_year % 4 == 0 && (date.tm_year % 100 != 0 || (date.tm_year + 1900) % 400 == 0)) ? 1 : 0)) {
        date.tm_mday = 1;  // Reset day to 1
        date.tm_mon++;     // Move to the next month

        // Check if the month goes beyond December.
        if (date.tm_mon > 11) {
            date.tm_mon = 0;       // Reset month to January
            date.tm_year++;        // Move to the next year
        }
    }

    // Check if the date surpasses the provided end date.
    if (date.tm_year > end_date.tm_year) return false;
    if (date.tm_year == end_date.tm_year && date.tm_mon > end_date.tm_mon) return false;
    if (date.tm_year == end_date.tm_year && date.tm_mon == end_date.tm_mon && date.tm_mday > end_date.tm_mday) return false;

    return true;
}

/**
 * Parse a date string in the format "YYYY-MM-DD" to a std::tm object.
 *
 * @param date_str - Date string in the format "YYYY-MM-DD".
 *
 * @return - Returns a std::tm object representing the parsed date.
 */
std::tm parseDate(const std::string& date_str) {
    std::tm date = {};
    std::stringstream ss(date_str);

    int year, month, day;
    char dash;

    ss >> year >> dash >> month >> dash >> day;

    date.tm_year = year - 1900;  // tm_year is the year since 1900
    date.tm_mon = month - 1;     // tm_mon uses a range of [0, 11]
    date.tm_mday = day;

    return date;
}

int main() {
    // Prompt user for the start date.
    std::cout << "Enter the start date in the format YYYY-MM-DD: ";
    std::string start_date_str;
    std::cin >> start_date_str;

    // Prompt user for the end date.
    std::cout << "Enter the end date in the format YYYY-MM-DD: ";
    std::string end_date_str;
    std::cin >> end_date_str;

    // Parse the provided start and end dates.
    std::tm start_date = parseDate(start_date_str);
    std::tm end_date = parseDate(end_date_str);

    // Loop from the start date to the end date.
    while (true) {
        // If the day is even, skip to the next iteration.
        if (start_date.tm_mday % 2 != 0) { // This line checks if the day is odd
            // Construct the number in the format YYYYMMDD.
            int number = (start_date.tm_year + 1900) * 10000 +
                (start_date.tm_mon + 1) * 100 +
                start_date.tm_mday;

            // Check if the constructed number is prime.
            if (isPrime(number)) {
                std::cout << start_date.tm_mday << "/" << start_date.tm_mon + 1 << "/" << start_date.tm_year + 1900 << " (" << number << ") is a prime date." << std::endl;
            }
        }

        if (!incrementDate(start_date, end_date)) {
            break; // Exit the loop if we've exceeded the end date
        }
    }


    return 0;  // Indicate successful completion.
}
