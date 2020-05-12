#include "Laptime.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE 
*/

Laptime::Laptime(int laptime){
    setLaptime(laptime);
    setNext(NULL);
}
Laptime::Laptime(const Laptime& rhs){
    *this = rhs;
}
Laptime::~Laptime(){ //TODO:baska bir sey gerekli mi?
    setNext(NULL);
}
void Laptime::addLaptime(Laptime *next){ //FIXME:duzenleme yapilabilir
    setNext(next);
}
bool Laptime::operator<(const Laptime& rhs) const {
    return getLaptime() < rhs.getLaptime();
}
bool Laptime::operator>(const Laptime& rhs) const{
    return getLaptime() > rhs.getLaptime();
}
Laptime& Laptime::operator+(const Laptime& rhs){
    setLaptime( getLaptime() + rhs.getLaptime() );
    return *this;   
}
std::ostream& operator<<(std::ostream& os, const Laptime& laptime){
    int min, s, s1, s2, sTemp, ms, msTemp, ms1, ms2, ms3, rawLaptime;
    rawLaptime = laptime.getLaptime();
    s = rawLaptime / 1000;
    ms = rawLaptime % 1000;
    min = s / 60;
    sTemp = s % 60;
    s1 = sTemp / 10;
    s2 = sTemp % 10;
    ms1 = ms / 100;
    msTemp = ms % 100;
    ms2 = msTemp / 10;
    ms3 = msTemp % 10;
    os << min << ':' << s1 << s2 << '.' << ms1 << ms2 << ms3;
    return os;
}

///////////////////////////////////////////////////////////////////////////////
void Laptime::setLaptime(int newLaptime){
    laptime = newLaptime;
}
int Laptime::getLaptime() const{
    return laptime;
}
void Laptime::setNext(Laptime * newNext){
    next = newNext;
}
Laptime * Laptime::getNext() const{
    return next;
}
Laptime::Laptime() {
    setLaptime(0);
    setNext(NULL);
}
Laptime& Laptime::operator=(const Laptime& rhs){
    if(this != &rhs){
        setLaptime(rhs.getLaptime());
        setNext(rhs.getNext());
    }
    return *this;
}