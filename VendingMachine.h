/****************************************************
 This is a header file for VendingMachine.

 It contains a class called VendingMachine, storing information for the id of vending
 machine, cost of each soda, maximum stock in vending machine per flavour, sdoa flavours,
 the universal printer, and the access to the nameserver.

 It also contains two derived classes from VendingMachine, called VendingMachineCardEater
 and VendingMachineOverCharger.
 
 
 VendingMachine has 7 attributes. 6 of them are virtual. But only function "buy" will be
 implemented in derived classes.
 
 All three vending machine has their own constructor.

 They will be detailed coded in the VendingMachine.cc file.
***/

#ifndef __VENDINGMACHINE_H__
#define __VENDINGMACHINE_H__

#include "PRNG.h"
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

class NameServer;

class VendingMachine{
// adding protected member in order to benefit from inheritance.
protected:
    unsigned int idnum;
    unsigned int flavour_cost;
    unsigned int maxStock;
    unsigned int soda_flavour[4];
    Printer* prtTmp;
    NameServer* ns;
public:
    enum Status{BUY, STOCK, FUNDS};
    enum Flavours{BLACK_CHERRY,CREAM_SODA,ROOT_BEER,LIME};
    VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour);
    virtual ~VendingMachine(); // necessary to trigger destructors in inherited classes
    virtual Status buy( Flavours flavour, WATCard *&card ); // YOU DEFINE FLAVOURS
    virtual unsigned int *inventory();
    virtual void restocked();
    virtual unsigned int cost();
    virtual unsigned int getId();
};

class VendingMachineCardEater : public VendingMachine {
public:
    VendingMachineCardEater( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour );
    // member routines from VendingMachine
    Status buy( Flavours flavour, WATCard *&card );
};
class VendingMachineOverCharger : public VendingMachine {
public:
    VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ); // member routines from VendingMachine
    Status buy( Flavours flavour, WATCard *&card );
};

#endif