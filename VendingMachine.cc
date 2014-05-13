/****************************************************
 This is a source file for VendingMachine. (VM refers to VendingMachine)
 
 %%%%%%%%%%%%%%%%%%
 Class vm contains 7 functions: a constructor, a virtual destructor, virtual buy,
 virtual inventory, virtual restocked, virtual cost, and virtual getId.
 
 1. VM constructor will create a regular VM with initialization for all the fields.
    Also, it will print out state "S" via printer.
 2. ~VM is a destructor, ending VM and printting out state "F" via printer.
 3. buy will be implemented in the two derived classes.
 4. inventory() will consume nothing and return its own soda_flavour stock.
 5. restocked() will consume nothing but will be called by Truck to indicating delivery
    completed.
 6. cost() will consume nothing and return its own flavour_cost, which is the
    regular soda cost.
 7. getId() will consume nothing and return its own idnum that associated with this VM.
 %%%%%%%%%%%%%%%%%%%
 Derived class: VMCardEaster
 1. VMCardEaster constructor will create a CardEater VM with initialization for all the fields.
    Also, it will print out state "S" via printer.
    It has 1 in 10 chance of eating a student's WATCard.
 2. buy will consumes a flavour and WATCard and return either BUY if student buys one, STOCK if
    out of stock, or FUNDS if WATCard has insufficient funds.
 %%%%%%%%%%%%%%%%%%%
 Derived class: VMOverCharger
 1. VMOverCharger constructor will create a OverCharger VM with initialization for all the fields.
    Also, it will print out state "S" via printer.
    It always over charge students with 2*sodaCost.
 2. buy will consumes a flavour and WATCard and return either BUY if student buys one, STOCK if
    out of stock, or FUNDS if WATCard has insufficient funds.
 ***/

#include <iostream>
#include<cstdlib>
#include "VendingMachine.h"

// extern PRNG allows us to using prng and the seed
extern PRNG prng;
 
// VM constructor will create a regular VM with initialization for all the fields.
// Also, it will print out state "S" via printer.
VendingMachine::VendingMachine(Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour){
    maxStock = maxStockPerFlavour;
    soda_flavour[0] = 0;
    soda_flavour[1] = 0;
    soda_flavour[2] = 0;
    soda_flavour[3] = 0;
    flavour_cost = sodaCost;
    idnum = id;
    prtTmp = &prt;
    ns = &nameServer;
}

// ~VM is a destructor, ending VM and printting out state "F" via printer.
VendingMachine::~VendingMachine(){
    prtTmp->print(Printer::Vending,idnum,'F');
}

//buy will be implemented in the two derived classes.
VendingMachine::Status VendingMachine::buy(VendingMachine::Flavours flavour, WATCard *&card){
}

//inventory() will consume nothing and return its own soda_flavour stock.
unsigned int* VendingMachine::inventory(){
    return soda_flavour;
}


// restocked() will consume nothing but will be called by Truck to indicating delivery
// completed.
void VendingMachine::restocked(){
}

// cost() will consume nothing and return its own flavour_cost, which is the
// regular soda cost.
unsigned int VendingMachine::cost(){
    return flavour_cost;
}

// getId() will consume nothing and return its own idnum that associated with this VM.
unsigned int VendingMachine::getId(){
    return idnum;
}


// Derived class:
// VMCardEaster constructor will create a CardEater VM with initialization for all the fields.
// Also, it will print out state "S" via printer.
// It has 1 in 10 chance of eating a student's WATCard.
VendingMachineCardEater::VendingMachineCardEater( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ):VendingMachine(prt, nameServer, id, sodaCost, maxStockPerFlavour){
    prtTmp = &prt;
    prtTmp->print(Printer::Vending,id,'S',sodaCost);
    ns->VMregister(this);
    
}


// buy will consumes a flavour and WATCard and return either BUY if student buys one, STOCK if
// out of stock, or FUNDS if WATCard has insufficient funds.
// It has 1 in 10 chance of eating a student's WATCard.
VendingMachine::Status VendingMachineCardEater::buy(Flavours flavour, WATCard *&card){
    bool empty = false; // assume student could buy a soda
    if(soda_flavour[flavour] == 0){
        empty = true;// no stock anymore
    }
    if((card->getBalance() >= flavour_cost) && (empty == false)){
        // if VM has stock and student has enough money, VM will select student's
        // favouriate one.
        switch (flavour) {
            case BLACK_CHERRY:
                soda_flavour[0]--;
                prtTmp->print(Printer::Vending,idnum,'B',0,soda_flavour[0]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case CREAM_SODA:
                soda_flavour[1]--;
                prtTmp->print(Printer::Vending,idnum,'B',1,soda_flavour[1]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case ROOT_BEER:
                soda_flavour[2]--;
                prtTmp->print(Printer::Vending,idnum,'B',2,soda_flavour[2]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case LIME:
                soda_flavour[3]--;
                prtTmp->print(Printer::Vending,idnum,'B',3,soda_flavour[3]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            default:
                break;
        }
        if(prng(0,9) == 0){
            // 1 in 10 chance to eat a student's card
            delete card;
            card = NULL;// setting card as NULL
        }
        return BUY;
    }
    else{
        if(prng(0,9) == 0){
            // if no stock, still 1 in 10 chance to eat a students's card
            delete card;
            card = NULL;// setting card as NULL
        }
        if(empty == true){
            return STOCK;// no stock left
        }
        else{
            return FUNDS;// insufficient funds
        }
    }
}


// VMOverCharger constructor will create a OverCharger VM with initialization for all the fields.
// Also, it will print out state "S" via printer.
// It always over charge students with 2*sodaCost.
VendingMachineOverCharger::VendingMachineOverCharger( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost, unsigned int maxStockPerFlavour ):VendingMachine(prt, nameServer, id, sodaCost*2, maxStockPerFlavour){
    // setting sodaCost as 2*(regular price)
    prtTmp = &prt;
    prtTmp->print(Printer::Vending,id,'S',sodaCost*2);
    ns->VMregister(this);
    
}




// buy will consumes a flavour and WATCard and return either BUY if student buys one, STOCK if
// out of stock, or FUNDS if WATCard has insufficient funds.
VendingMachine::Status VendingMachineOverCharger::buy(Flavours flavour, WATCard *&card){
    bool empty = false;// assume student could buy a soda
    if(soda_flavour[flavour] == 0){
        empty = true;// no stock anymore
    }
    if((card->getBalance() >= flavour_cost) && (empty == false)){
        // if VM has stock and student has enough money, VM will select student's
        // favouriate one.
        switch (flavour) {
            case BLACK_CHERRY:
                soda_flavour[0]--;
                prtTmp->print(Printer::Vending,idnum,'B',0,soda_flavour[0]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case CREAM_SODA:
                soda_flavour[1]--;
                prtTmp->print(Printer::Vending,idnum,'B',1,soda_flavour[1]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case ROOT_BEER:
                soda_flavour[2]--;
                prtTmp->print(Printer::Vending,idnum,'B',2,soda_flavour[2]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            case LIME:
                soda_flavour[3]--;
                prtTmp->print(Printer::Vending,idnum,'B',3,soda_flavour[3]);
                card->setBalance(card->getBalance()-flavour_cost);
                break;
            default:
                break;
        }
        return BUY;
    }
    else{
        if(empty == true){
            return STOCK;// no stock left
        }
        else{
            return FUNDS;// insufficient funds
        }
    }
}