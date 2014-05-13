/****************************************************
This is a source file for WATCard.

It contains four functions: a constructor, two field-selectors
and a balance mutator.
1. WATCard constructor build a watcard that stores id as uwid.
   Balance always start with zero.
2. getID returns uwid
3. getBalance returns 
4. setBalance consumes a new_amount and mutate the
   balance as new_amount (no +/-, just reset)

***/


#include <iostream>
#include "WATCard.h"

// WATCard constructor build a watcard that stores id as
// uwid. Balance always start with zero.
WATCard::WATCard(unsigned int id){
    uwid = id;
    balance = 0;
}


// getID returns uwid
unsigned int WATCard::getID() const{
    return uwid;
}


// getBalance returns balance
unsigned int WATCard::getBalance() const{
    return balance;
}


// setBalance consumes a new_amount and mutate the
// balance as new_amount (no +/-, just reset)
void WATCard::setBalance(unsigned int new_amount){
	balance = new_amount;
}
