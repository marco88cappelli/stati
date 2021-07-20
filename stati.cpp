#include "stati.h"  

void stati::begin()
{
    
    process = NULL;
    oldProcess = 0;
    maxProcess = 0;
}

void stati:: back(){
    if (process->id > 1) goTo(process->id - 1);
}

void stati::next(){

    if (process->id < maxProcess) goTo(process->id + 1);
}

void stati:: execProcess(){
    process->fun(process->id==oldProcess?false:true);
    oldProcess= process->id;
}

int stati::add(functionState funzioneDiStato=NULL){
    if (funzioneDiStato==NULL) return -1;

    processes *process1 = new processes;

    bool firstAdd = maxProcess==0?true:false;
    if (!firstAdd) gotoLast();
    

    maxProcess ++;

    process1->id = maxProcess;
    process1->fun = funzioneDiStato;
    process1->previous = process;
    process1->after = NULL;
    if (!firstAdd) process->after = process1;
    process = process1;

    return 1;
}

void stati::goTo(uint8_t position)
{
    if (process != NULL)
    {
        if (process->id != position)
        {
            if (position <= maxProcess)
            {
                if (position >= 1)
                {

                    processes *process1 = NULL;

                    while (process->id != position)
                    {
                        if (process->id > position)
                            process1 = process->previous;
                        else
                            process1 = process->after;
                        process = process1;
                    }
                }
            }
        }
    }
}

void stati::gotoFirst(){
    goTo(1);
}

void stati::gotoLast(){
    goTo(maxProcess);
}

uint8_t stati::ProcessCurr(){
    if (process==NULL) return 0;
    return process->id;
}