#ifndef UTILS_H
#define UTILS_H

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