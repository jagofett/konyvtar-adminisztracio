#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <sstream>
//#include "Members.h"
using namespace std;
class MyDate{
private:
int napok;
int _ev, _hnap, _nap;
public:
enum Exception {BAD_DATE_FORMAT};
int getEv(){return _ev;}
int getHnap(){return _hnap;}
int getNap(){return _nap;}
int getNapok(){return napok;}

MyDate(int ev, int hnap, int nap): _ev(ev), _hnap(hnap), _nap(nap)
{

const int daysInYear [] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
napok = 0;
this->napok = ev*365  + daysInYear[hnap-1] + nap ;

}

MyDate(string td) //EEEE.HH.NN formatumu stringbol datumot keszit
{
   // napok = napok;
   // cout << td << endl;
int ev, hnap, nap;
    if (td.size()!=10) {cout << "hossz!";throw BAD_DATE_FORMAT;} else {
    _ev = atoi(td.substr(0,4).c_str());
    _hnap = atoi(td.substr(5,2).c_str());
    _nap = atoi(td.substr(8,2).c_str());
    ev = _ev; hnap = _hnap; nap = _nap;
    if (!checkDate(ev, hnap, nap))
        {throw BAD_DATE_FORMAT;}
            //cout << ev << endl;    cout << hnap << endl;    cout << nap << endl;
    *this = MyDate(ev,hnap,nap);

    }
}
bool checkDate(int ev, int hnap, int nap){ //adott év, hónap nap megfelelõ formájú.e?
    if ((ev==0 || hnap==0 || nap==0) ||
            (hnap==2 && nap>28) ||
            ((hnap==4 || hnap==6 || hnap==9 || hnap==11) && nap>30) ||
            ((hnap==1 || hnap==3 || hnap==5 || hnap==7 || hnap==8 || hnap==10 || hnap==12) && nap>31))
    {return false;}
    else {return true;}
}

string toDate(const int napszam)const{
int ev, hnap, nap, hnapszam, maradek;
const int daysInYear [] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

ev = napszam/365;
int i = 0;
maradek = ((napszam%365)-daysInYear[i]);
while (maradek>daysInYear[i+1]){i++;maradek = (maradek-daysInYear[i]);}
hnap = i;
if(hnap==4 || hnap==6 || hnap==9 || hnap==11) {hnapszam = 30;}
if(hnap==1 || hnap==3 || hnap==5 || hnap==7 || hnap==8 || hnap==10 || hnap==12) {hnapszam = 31;}
if(hnap==2) {hnapszam = 28;}

hnap = (napszam%365)/hnapszam +1;
nap = (napszam%365)%hnapszam;
stringstream sor;
string hkoz = (hnap < 10) ? "0":"";
sor <<ev <<"." << hkoz << hnap <<".";
hkoz = (nap < 10) ? "0":"";
sor << hkoz << nap;
return sor.str();

}
std::string getDate(){
stringstream sor;
string hkoz = (_hnap < 10) ? "0":"";
sor <<_ev <<"." << hkoz << _hnap <<".";
hkoz = (_nap < 10) ? "0":"";
sor << hkoz << _nap;
return sor.str();

}

 int maiDatum() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y.%m.%d", &tstruct);
    MyDate tmp(buf);
    return tmp.napok;
}
int maElter(){
    int ma = maiDatum();
   return ((napok-ma)>0) ? napok-ma:ma-napok;
}

void addMonth(){
if (_hnap != 12){*this = MyDate(_ev,_hnap+1, _nap );}
else {*this = MyDate(_ev +1,1, _nap );}

}

MyDate operator+(int a)
{
//cout << napok << endl;
napok += a;
//cout << napok << endl;

*this = MyDate(toDate(napok));
return *this;
}

MyDate operator-(int a)
{
napok -= a;
*this = MyDate(toDate(napok));
return *this;
}

friend ostream& operator<<(ostream &os,const MyDate &b)
{
    string h1, h2;
    h1 = (b._hnap < 10) ? "0":""; //kitöltõ 0-ák
    h2 = (b._nap < 10) ? "0":"";
    return os << b._ev << "." << h1 << b._hnap << "." << h2 << b._nap;
}
};






#endif // DATE_H
