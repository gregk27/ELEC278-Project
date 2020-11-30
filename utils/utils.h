/**
 * utils.cpp/h
 * These files contain a few random utilities that did not belong elsewhere, but were too small for own files
 */

#ifndef UTILS_H
#define UTILS_H

/**
 * Print the binary representation of a number
 * - i:      The number to print
 * - length: The number of binary digits to use
*/
void print_bin(int i, int length);

// Base class to simplify custom exceptions
struct ExceptionBase : public std::exception {
    private:
        // The exception's message
        std::string msg;
    public:
        // Create a new exception with the specified message
        ExceptionBase(const std::string msg);
        const char * what () const throw ();
};


#endif // !UTILS_H