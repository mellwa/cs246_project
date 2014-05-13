/***
This is a header file for WATCard.

It contains a class called WATCard, storing information for a student's
ID number and the balance on the card.

WATCard constructor, field-selectors, and balance mutator will be coded
in WATCard.cc.
***/


#ifndef __WATCARD_H__
#define __WATCARD_H__


class WATCard{
    unsigned int uwid;
    unsigned int balance;
public:
    WATCard(unsigned int id);
    unsigned int getID() const; // return uwid
    unsigned int getBalance() const; // return balance
    void setBalance(unsigned int new_amount); // reset balance as new_amount
};

#endif
