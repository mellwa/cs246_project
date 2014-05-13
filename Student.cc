/****************************************************
This is a source file for Student.

It contains three functions: a constructor, action and a destructor.
1. Student constructor will create a student with initialization for all the fields.
2. ~Student is a destructor, ending Student, deleting WATCard on heap
   and printting "F" state to printer
3. action() will return a bool.
   It will return false when numPurchases is zero
   It will return true when:
      a. If the vending machine delivered a bottle of soda and the student drink it.
      b. If there is insufficient funds, students need to transfer $3 via office
         until they have enough to buy a soda.
      c. If students use the new money to buy a soda.
      d. If the vending machine is out of stock of the students' favourite flavour,
         then student obtain a new vending machine via nameserver
      e. students try to buy a soda using the new vending machine

***/
#include <iostream>
#include "Student.h"

// extern to PRNG in order to get seed and function.
extern PRNG prng;

//Student constructor will create a student with initialization for all the fields.
Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases ){
    unsigned int money = 5;
    student_id = id;
    tmpid = id+1;
    numPurchase = prng(1,maxPurchases);
    favourite = prng(0,3);
    watcard_office = &cardOffice;
    prtTmp = &prt;
    ns = &nameServer;
    
    prtTmp->print(Printer::Student,student_id,'S',favourite,numPurchase);
    watcard = watcard_office->create(student_id,money);//get watcard
    vm = ns->getMachine(id);
    prtTmp->print(Printer::NameServer,'N',student_id,vm->getId());
    prtTmp->print(Printer::Student,student_id,'V',vm->getId());
}

// ~Student is a destructor, ending Student, deleting WATCard on heap
// and printting "F" state to printer
Student::~Student(){
    delete watcard;
    prtTmp->print(Printer::Student,student_id,'F');
}


// action() will return a bool.
// It will return false when numPurchases is zero
// It will return true when:
//   a. If the vending machine delivered a bottle of soda and the student drink it.
//   b. If there is insufficient funds, students need to transfer $3 via office
//      until they have enough to buy a soda.
//   c. If students use the new money to buy a soda.
//   d. If the vending machine is out of stock of the students' favourite flavour,
//      then student obtain a new vending machine via nameserver
//   e. students try to buy a soda using the new vending machine
bool Student::action(){
    VendingMachine::Flavours F;
    if(numPurchase == 0){
        return false;//out of stock
    }
    // according to the favourite, we update their favourite flavour in words so that
    // matching the names in vending machine
    switch (favourite) {
        case 0:
            F = VendingMachine::BLACK_CHERRY;
            break;
        case 1:
            F = VendingMachine::CREAM_SODA;
            break;
        case 2:
            F = VendingMachine::ROOT_BEER;
            break;
        case 3:
            F = VendingMachine::LIME;
            break;
        default:
            break;
    }
    // getting the vending machine status
    VendingMachine::Status t = vm->buy(F,watcard);
    // checking whether the watcard is eaten by vending machine
    if(watcard == NULL){
        prtTmp->print(Printer::Student,student_id,'D');
        // create a new watcard via watcardoffice
        watcard = watcard_office->create(student_id,5);
    }
    unsigned int transfer_money = 3;

    if(t == VendingMachine::STOCK){
        // When the current vending machine does not have stock anymore
        // obtain a new vending machine via nameserver
        vm = ns->getMachine(tmpid);
        tmpid++;
        prtTmp->print(Printer::NameServer,'N',student_id,vm->getId());
        prtTmp->print(Printer::Student,student_id,'V',vm->getId());
        return true;
    }
    else if(t == VendingMachine::FUNDS){
        // if insufficient fund, transfer $3 to watcard each time until
        // student can buy at least one soda
        do{
            watcard_office->transfer(student_id,transfer_money,*watcard);
        }while(watcard->getBalance() < vm->cost());
        return true;
    }
    else; // else do nothing
    
    // actual purchasing here
    numPurchase--;
    prtTmp->print(Printer::Student,student_id,'B',watcard->getBalance());
    return true;
}


















