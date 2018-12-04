#ifndef UNTITLED_EXCEPTION_H
#define UNTITLED_EXCEPTION_H

#include <exception>


namespace dataStructure {

    // dataStructure::exception class
    class exception : public std::exception {};

    // Specific exceptions. Can be also caught as mtm::exceptions
    // or std::exceptions
    class INVALID_INPUT : public dataStructure::exception {};
    class ALLOCATION_ERROR : public dataStructure::exception {};
    class FAILURE : public dataStructure::exception {};
    class SUCCESS : public dataStructure::exception {};
}

#endif //UNTITLED_EXCEPTION_H
