/***
 This file contains the source code of Truck.
 
 It constains three functions: a constructor, a destructor and action.
 
 1. Truck constructor will build a truck with with initialization for all the
    fields. Also, it will print out state "S" via printer. It will initialize
    cargo for all four flavour as zero and totoal_cargo as zero.
 2. ~Truck is a destructor, ending Truck, and printing "F" state to printer.
 3. action will consume nothing and produce nothing. Action is called by Bottling
    Plant. Before delivering bottles, truck will check if the total_cargo is zero.
    If yes, it will do nothing; otherwise, it will distribute bottles for
    registered vending machines (every flavour). Once the bottles could not fill
    up a vending machine, truck will print "U" via printer, and go back to
    BottlingPlant.

***/

#include <iostream>
#include "Truck.h"
#include "BottlingPlant.h"
using namespace std;


// Truck constructor will build a truck with with initialization for all the
// fields. Also, it will print out state "S" via printer. It will initialize
// cargo for all four flavour as zero and totoal_cargo as zero.
Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,unsigned int numVendingMachines, unsigned int maxStockPerFlavour ){
    // initializing everything
    prtTmp = &prt;
    ns = &nameServer;
    bPlant = &plant;
    numVM = numVendingMachines;
    maxStock = maxStockPerFlavour;
    prtTmp->print(Printer::Truck,'S');
    Cargo[0] = 0;
    Cargo[1] = 0;
    Cargo[2] = 0;
    Cargo[3] = 0;
    total_cargo = 0;
}


// action will consume nothing and produce nothing. Action is called by Bottling
// Plant. Before delivering bottles, truck will check if the total_cargo is zero.
// If yes, it will do nothing; otherwise, it will distribute bottles for
// registered vending machines (every flavour). Once the bottles could not fill
// up a vending machine, truck will print "U" via printer, and go back to
// BottlingPlant.
void Truck::action(){
	// local variables needed for complete action
    unsigned int* tmpFlavours;
    int sum;
    unsigned int i,j;
    VendingMachine** tmpVM = ns->getMachineList();
    
        bPlant->getShipment(Cargo);
        total_cargo = Cargo[0]+Cargo[1]+Cargo[2]+Cargo[3];
		// if total_cargo is zero still, no need to start delivering
        if(total_cargo == 0){
            return;// does nothing and ends the function
        }
        for(i = 0;i<numVM;i++){
            tmpFlavours = tmpVM[i]->inventory();
            prtTmp->print(Printer::Vending,tmpVM[i]->getId(),'r');
            prtTmp->print(Printer::Truck,'d',tmpVM[i]->getId(),total_cargo);
			// amount that the vending machine needs
            sum = 4*maxStock-tmpFlavours[0]-tmpFlavours[1]-tmpFlavours[2]-tmpFlavours[3];
            for(j = 0; j < 4; j++){
				// delivering for each flavour
                while(Cargo[j]>0 && tmpFlavours[j]<maxStock){
                    tmpFlavours[j]++;
                    Cargo[j]--;
                    total_cargo--;
                    sum--;
                }
                if(total_cargo == 0){
                    break; // no more on Truck
                }
            }
			// the current vending machine is not full
            if(sum != 0){
				// unsuccessful
                prtTmp->print(Printer::Truck,'U',tmpVM[i]->getId(),sum);
            }
			// finish delivering to vending machine
            prtTmp->print(Printer::Truck,'D',tmpVM[i]->getId(),total_cargo);
            prtTmp->print(Printer::Vending,tmpVM[i]->getId(),'R');
            if(total_cargo == 0){
                break;
            }
        } 
        
}


// ~Truck is a destructor, ending Truck, and printing "F" state to printer.
Truck::~Truck(){
    prtTmp->print(Printer::Truck,'F');
}















