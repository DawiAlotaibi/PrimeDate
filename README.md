## PrimeDate

This program allows users to input a range of dates and determine which dates within that range are prime when formatted as `YYYY-MM-DD`.

### Prerequisites

- A C++ compiler that supports C++11 or higher (e.g., GCC, Clang, or MSVC).
- The `PrimeUtils.h` file which contains the utility functions.

### Usage

1. Compile the source code.
2. Run the program.
3. When prompted, enter the start and end dates in the `YYYY-MM-DD` format.
4. The program will then display any prime dates within the specified range.
5. To exit the program, simply enter `quit` or `q` or just an empty string ` ` when prompted.

### Features

- Robust input error handling: The program will catch and inform you of any input format errors.
- Efficient prime checking algorithm.

### How It Works

The program prompts the user for a start and end date, then iterates through each date in that range. It then checks whether the date, when formatted as `YYYY-MM-DD`, is a prime number. If it is, it displays the date and the corresponding number to the user.

### Known Issues

- Leap years are accounted for, but there may be discrepancies in very distant future years.
- The program assumes the Gregorian calendar.
