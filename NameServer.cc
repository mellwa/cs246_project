/****************************************************
 This is a source file for NameServer.
 
 It contains five functions: a constructor, a destructor, VMregister, getMachine
 and getMachineList.
 
 1. NameServer constructor will create a nameserver with initialization for all the fields.
    Also, it will print out state "S" via printer.
 2. ~NameServer is a destructor, ending NameServer, deleting VMs in array,  and printing "F" 
    state to printer
 3. VMregister consumes a vending machine pointer and produces void. It will adding the
    input into array (all the registed vending machine).
 4. getMachine will consume an id, and returns a pointer to vending machine. If the id is
    smaller than numRegister, it will get the VM from the array using index. Otherwise,
    we need to take the remainder to loop around the array.
 5. getMachinelist consumes nothing, but return the array that stores all the vending machines
    that are registed.
***/

#include <iostream>
#include "NameServer.h"


// NameServer constructor will create a nameserver with initialization for all the fields.
// Also, it will print out state "S" via printer.
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ){
    prt.print(Printer::NameServer,'S');
    prtTmp = &prt;
    numVM = numVendingMachines;
    numSt = numStudents;
    // creating an array on heap storing all the pointers to vending machine
    vm = new VendingMachine*[numVendingMachines];
    numRegister = 0;
}

// VMregister consumes a vending machine pointer and produces void. It will adding the
// input into array (all the registed vending machine).
void NameServer::VMregister( VendingMachine *vendingmachine ){
    prtTmp->print(Printer::NameServer,'R',vendingmachine->getId());
    vm[numRegister] = vendingmachine;// adding the current vending machine into our array
    numRegister++;
}


// getMachine will consume an id, and returns a pointer to vending machine. If the id is
// smaller than numRegister, it will get the VM from the array using index. Otherwise,
// we need to take the remainder to loop around the array.
VendingMachine* NameServer::getMachine(unsigned int id){
    if(id>=numRegister){
        id = id % numRegister; // reduce id after taking mod
    }
    return vm[id];
}


// getMachinelist consumes nothing, but return the array that stores all the vending machines
// that are registed.
VendingMachine** NameServer::getMachineList(){
    return vm;
}


// ~NameServer is a destructor, ending NameServer, deleting VMs in array,  and printting "F" 
// state to printer
NameServer::~NameServer(){
    delete []vm;// delete the array on heap, using [] for deleting array
    prtTmp->print(Printer::NameServer,'F');
}