#pragma once
#include <exception>
#include <string>
#include <iostream>
using namespace std;


class IllegalCoordinateException : public exception {
    int first;
    int second;
    public:
        const char* theCoordinate() const throw ();
        void set_first(int first);
        void set_second(int second);
};

class IllegalCharException : public exception {
    char illegal;
    public:
        const char* theChar() const throw ();
        void set_illegal(char illegal);
};