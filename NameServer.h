/***
 This is a header file for NameServer.
 
 It contains a class called NameServer, storing information for a total number of vending
 machines on campus, a total number of students, the universal printer and a counter for 
 numeber of vending machine registed
 
 It also contains five attributes: a NameServer constructor, a destructor, VMregister,
 getMachine and getMachineList.
 
 They will be detailed coded in the NameServer.cc file.
 
 ***/
#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "PRNG.h"
#include "VendingMachine.h"
#include "Printer.h"

class VendingMachine;

class NameServer { 
protected:
    unsigned int numVM;
    unsigned int numSt;
    Printer* prtTmp;
    VendingMachine** vm;
    unsigned int numRegister;
public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ); 
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
    ~NameServer();
};

#endif