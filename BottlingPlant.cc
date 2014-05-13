/***
 This file contains the source code of BottlingPlant.
 
 It contains four functions: a constructor, a destructor, getShipments and action.
 
 1. BottlingPlant constructor will create a truck on heap, performing a production
    run, and distributing these bottles to initialize the registered vending machines
    using the truck. The BottlingPlant produces random new quantities of each flavour
    of soda, [0, MaxShippedPerFlavour], per flavour.
 2. ~BottlingPlant is a destructor, ending BottlingPlant, deleting truck on heap,
    and printing "F" state to the printer.
 3. getShipment obtains a shipment from the production run, and the shipment is
    copied into the cargo arry passed by the truck.
 4. action consumes nothing and produces nothing. There is a 1/5 chance the Bottling
    Plant is on strike. If on strike, the BP returns without continuing any work;
    otherwise, the bottling plant will check whether the truck has came back from the
    last delivery. There is 1/TimeBetwwenShipments chance that truck has return.
    If the truck has not came back, then BP will do nothing. If the truck has came
    back, it will perform a new producetion run and then call the truck's action to 
    deliver bottles to vending machines.
 
***/

#include <iostream>
#include "BottlingPlant.h"
using namespace std;

// extern PRNG: allowing to use seed and prng
extern PRNG prng;


// BottlingPlant constructor will create a truck on heap, performing a production
// run, and distributing these bottles to initialize the registered vending machines
// using the truck. The BottlingPlant produces random new quantities of each flavour
// of soda, [0, MaxShippedPerFlavour], per flavour.
BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines, unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ){
    prtTmp = &prt;
    prtTmp->print(Printer::BottlingPlant,'S');
    ns = &nameServer;
    numVM = numVendingMachines;
    maxShip = maxShippedPerFlavour;
    maxStock = maxStockPerFlavour;
    time = timeBetweenShipments;
    // creating a truck on heap
    truck = new Truck(prt,nameServer,*this,numVendingMachines,maxStockPerFlavour);
	// initializing all the flavours as zero stock
    flavour[0] = 0;
    flavour[1] = 0;
    flavour[2] = 0;
    flavour[3] = 0;
    total_amount = 0;
	// randomly producing flavours
    flavour[0] = prng(0,maxShip);
    flavour[1] = prng(0,maxShip);
    flavour[2] = prng(0,maxShip);
    flavour[3] = prng(0,maxShip);
	// total production
    total_amount = flavour[0]+flavour[1]+flavour[2]+flavour[3];
    prtTmp->print(Printer::BottlingPlant,'G',total_amount);
	// call truck: start delivering
    truck->action();
}


// getShipment obtains a shipment from the production run, and the shipment is
// copied into the cargo arry passed by the truck.
void BottlingPlant::getShipment(unsigned int cargo[]){
	// total shipment 
    int totalsum;
    cargo[0] = flavour[0];
    cargo[1] = flavour[1];
    cargo[2] = flavour[2];
    cargo[3] = flavour[3];
    totalsum = cargo[0]+cargo[1]+cargo[2]+cargo[3];
	// resetting to zero for the next production
    flavour[0] = 0;
    flavour[1] = 0;
    flavour[2] = 0;
    flavour[3] = 0;
    prtTmp->print(Printer::BottlingPlant,'P');
    prtTmp->print(Printer::Truck,'P',totalsum);
}



// action consumes nothing and produces nothing. There is a 1/5 chance the Bottling
// Plant is on strike. If on strike, the BP returns without continuing any work;
// otherwise, the bottling plant will check whether the truck has came back from the
// last delivery. There is 1/TimeBetwwenShipments chance that truck has return.
// If the truck has not came back, then BP will do nothing. If the truck has came
// back, it will perform a new producetion run and then call the truck's action to 
// deliver bottles to vending machines.
void BottlingPlant::action(){
	// 1 in 5 chance that BottlingPlant is on a strike
    if(prng(0,4) == 0){
        prtTmp->print(Printer::BottlingPlant,'X');
        return;//on strike
    }
	// checking whether the truck is coming back
    else if(prng(time - 1)==0){
		// re-fill all the flavours
        flavour[0] = flavour[0]+prng(0,maxShip);
        flavour[1] = flavour[1]+prng(0,maxShip);
        flavour[2] = flavour[2]+prng(0,maxShip);
        flavour[3] = flavour[3]+prng(0,maxShip);
		// calculating the new totoal amount
        total_amount = flavour[0]+flavour[1]+flavour[2]+flavour[3];
        prtTmp->print(Printer::BottlingPlant,'G',total_amount);
        // call truck: start delivering
        truck->action();
        return;
    }
    else{
        return;
    }
}


// ~BottlingPlant is a destructor, ending BottlingPlant, deleting truck on heap,
// and printing "F" state to the printer.
BottlingPlant::~BottlingPlant(){
    prtTmp->print(Printer::BottlingPlant,'F');
	// delete the truck that is created on heap
    delete truck;
}

