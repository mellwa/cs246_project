/***
 This is a header file for Truck.
 
 It contains a class called Truck, storing information for the universal printer
 the nameserver, the BottlingPlant, the total number of vending machine, the maximum
 stock per flavour, an array for shipping for each flavour and a total shipments
 on truck.
 
 It also contains three attributes: a Truck constructor, a destructor and action.

 They will be detailed coded in the Truck.cc file.
 
 ***/
#ifndef __TRUCK_H__
#define __TRUCK_H__

#include "PRNG.h"

#include "Printer.h"
#include "NameServer.h"

class BottlingPlant;

class Truck {
protected:
    Printer* prtTmp;
    NameServer* ns;
    BottlingPlant* bPlant;
    unsigned int numVM;
    unsigned int maxStock;
    unsigned int Cargo[4];
    unsigned int total_cargo;
public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
          unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    void action(); 
    ~Truck();
};

#endif