/***
 This is a header file for BottlingPlant (abbr as BP later). 
 
 It contains a class called BP, storing information for the universal printer, the 
 nameserver, the truck using for delivery, a total number of vending machine,
 a maximum shipment per flavour, a maximum stock per flavour, a time that a
 truck need for shipping, the four flavours, total_amount of production and an access
 to the Truck::action().
 
 It also contains four attributes: a BP constructor, a destructor, getShipments and action.
 
 They will be detailed coded in the BottlingPlant.cc file.
 
 ***/
#ifndef __BOTTLINGPLANT_H__
#define __BOTTLINGPLANT_H__

#include "PRNG.h"
#include "Printer.h"
#include "NameServer.h"
#include "Truck.h"


class BottlingPlant {
protected:
    Printer* prtTmp;
    NameServer* ns;
    Truck* truck;
    unsigned int numVM;
    unsigned int maxShip;
    unsigned int maxStock;
    unsigned int time;
    unsigned int flavour[4];

    unsigned int total_amount;
    friend void Truck::action();
public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments );
    ~BottlingPlant();
    void getShipment( unsigned int cargo[] );
    void action(); 
};



#endif