/***
This is a header file for Student.

It contains a class called Student, storing information for student id, favourite
flavour, the max number of purchased soda, the access of WATCardOffice, the access of
universal printer, the access of nameserver, the WATCard that the student have on
heap, and a vending machine that the student will be interacting with.

It also contains three attributes: Student constructor, action command and destructor.
They will be detailed coded in the Student.cc file.

***/

#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "PRNG.h"
#include"WATCardOffice.h"
#include "WATCard.h"
#include "Printer.h"
#include"VendingMachine.h"
#include "NameServer.h"

class Student { 
    unsigned int student_id;
    unsigned int tmpid;
    unsigned int favourite;
    unsigned int numPurchase;
    WATCardOffice* watcard_office;
    Printer* prtTmp;
    NameServer* ns;
    WATCard* watcard;
    VendingMachine* vm;
public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
    bool action();
    ~Student();
};

#endif