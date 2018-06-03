#include "place.hpp"

place :: place(){
    sign = '.';
}

place :: place(char sign){
    if (sign != 'X' && sign != 'O' && sign != '.'){
        IllegalCharException ichar;
        ichar.set_illegal(sign);
        throw ichar; }
    this-> sign = sign;
}

place :: place(place& other){
    this-> sign = other.sign;
}
        
char place :: get_sign(void){
    return sign;
}
void place :: set_sign(char sign){
    if (sign != 'X' && sign != 'O' && sign != '.'){
        IllegalCharException ichar;
        ichar.set_illegal(sign);
        throw ichar; }
        this-> sign = sign;
}

place& place ::  operator= (char sign){
    this-> set_sign(sign);
    return *this;
}

place& place :: operator= (place& other){
    this->set_sign(other.get_sign());
    return *this;
}

bool place::operator==(place other) const{ return this-> sign == other.get_sign(); }
bool place::operator!=(place other) const{ return this-> sign != other.get_sign(); }
bool place::operator==(const char& ch) const{ return this-> sign == ch; }
bool place::operator!=(const char& ch) const{ return this-> sign != ch; }
