#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "Members.h"
class Members;
class MyDate{
private:
int napok;
int _ev, _hnap, _nap;
public:
enum Exception {BAD_DATE_FORMAT};
int getEv(){return _ev;}
int gethnap(){return _hnap;}
int getNap(){return _nap;}
MyDate(int ev, int hnap, int nap): _ev(ev), _hnap(hnap), _nap(nap)
{
const int daysInYear [] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
const int daysInLeapYear [] = {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366};
napok = 0;
//const int daysInMonth [] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
//const int DaysInMonthLeap [] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ( ev%4 == 0 && (ev%100!=0 || ev%400==0) && ev !=0 ) //szokoev
    {
        this->napok = ev*366  + daysInLeapYear[hnap] + nap ;
    }
    else  // nem szoko ev
    {
            this->napok = ev*365  + daysInYear[hnap] + nap ;
    }
}
MyDate(std::string td)
{
   // napok = napok;
    //std::cout << td << std::endl;
int ev, hnap, nap;
    if (td.size()!=8) throw BAD_DATE_FORMAT; else {
    _ev = atoi(td.substr(0,4).c_str());
    _hnap = atoi(td.substr(4,2).c_str());
    _nap = atoi(td.substr(6,2).c_str());
    ev = _ev; hnap = _hnap; nap = _nap;
    if ((ev==0 || hnap==0 || nap==0) ||
            (ev%4!=0 && hnap==2 && nap>28) ||
            (ev%4==0 && hnap==2 && nap>29) ||
            ((hnap==4 || hnap==6 || hnap==9 || hnap==11) && nap>30) ||
            ((hnap==1 || hnap==3 || hnap==5 || hnap==7 || hnap==8 || hnap==10 || hnap==12) && nap>31))
        {throw BAD_DATE_FORMAT;}
            //std::cout << ev << std::endl;    std::cout << hnap << std::endl;    std::cout << nap << std::endl;
    *this = MyDate(ev,hnap,nap);

    }
}
 int maiDatum() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y%m%d", &tstruct);
    MyDate tmp(buf);
    return tmp.napok;
}
int maElter(){
    int ma = maiDatum();
   return ((napok-ma)>0) ? napok-ma:ma-napok;
}
int operator+(MyDate &a){
return (a.napok + napok);
}

int operator-(MyDate &a){
return (((a.napok - napok)<0) ? napok-a.napok:a.napok-napok);
}
friend std::ostream& operator<<(std::ostream&,const MyDate&);
};

std::ostream& operator<<(std::ostream &os,const MyDate &b)
{
    return os << b._ev << "." << b._hnap << "." << b._nap << std::endl;
}




#endif // DATE_H
