#include "exceptions.hpp"

const char* IllegalCoordinateException :: theCoordinate() const throw (){ return (to_string(first) + ',' +to_string(second) + '\n').c_str(); }
void IllegalCoordinateException :: set_first(int first){ this-> first = first; }
void IllegalCoordinateException :: set_second(int second){ this-> second = second; }



const char* IllegalCharException :: theChar() const throw (){
    const char* c = &illegal;
    return c;
}
void IllegalCharException :: set_illegal(char illegal){ this-> illegal = illegal; }