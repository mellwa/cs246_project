/***
This is a header file for WATCardOffice.

It contains a class called WATCardOffice, storing information for universal printer.

WATCardOffice constructor, WATCard creator, fund transfer and destructor will be coded
in WATCardOffice.cc

***/

#ifndef __WATCARDOFFICE_H__
#define __WATCARDOFFICE_H__

#include "WATCard.h"
#include "Printer.h"
#include "PRNG.h"

class WATCardOffice{
	Printer *prtTmp;
public:
    WATCardOffice(Printer &prt);
    WATCard *create(unsigned int id, unsigned int amount);
    void transfer(unsigned int id, unsigned int amount, WATCard &card);
	~WATCardOffice();
};

#endif
