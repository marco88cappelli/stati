
/*
	LIBRERIA STATI

	Questa libreria semplifica la programmazione a stati da parte dell'operatore.
	
	Struttura libreria:

		STATI:
			|_processo 1 -> esegue funzione 1
			|_processo 2 -> esegue funzione 2
			|_.......
		
	I processi sono gestiti tramite una lista bidirezionale nella quale viene registrato:
		a) id del processo
		b) puntatore alla funzione che deve essere eseguita
		c) puntatore al processo successivo
		d) puntatore a processo precedente

	Questa lista viene scorsa avanti e indietro tramite i metodi next e back, i quali vanno ad incrementare o decrementare la variabile protetta currentState
	ma la funzione puntata da quello stato viene eseguita soltanto quando nel loop del programma viene richiamato il metodo execProcess, infatti questo richiama
	la funzione puntata dallo stato attuale e setta il parametro firstRun true se oldPorcess è diverso da currentProcess, altrimenti lo setta a false. Questo serve
	se si deve eseguire determinate istruzioni nella funzione puntata alla sua prima esecuzone allo scattare dello stato oppure no, infatti ogni volta che viene richimato
	il metodo execProcess viene eseguita anche la funzione puntata.

	bisogna prestare attenzione, perchè questa classe ad ogni processo crato istanzia un processes struct che se infinito potrebbe saturare la RAM del microcontrollore

*/

#ifndef STATI.h
#define STATI.h

#include "arduino.h"

typedef void(*functionState)(bool firstRun);
struct processes{
			uint8_t id;
			functionState fun;
			processes *after;
			processes *previous;
		};
class stati  
{
	private:
		processes *process;
		uint8_t oldProcess;
		uint8_t maxProcess;
	public:
		void begin();
		void execProcess();
		int add(functionState funzioneDiStato=NULL);
		void next();
		void back();
		void goTo(uint8_t position);
		void gotoFirst();
		void gotoLast();
		uint8_t ProcessCurr();
		uint8_t ProcessOld(){return oldProcess;};
		uint8_t ProcessMax(){return maxProcess;};
};
#endif
