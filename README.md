# Libreria stati
Questa libreria semplifica il programmatore nella scrittura di logiche a stati, andando a sostituire la classica switch case nel loop.

Per poterla usare si deve:
  - Importare la libreria:
  	```#define <stati>```
  - definire l'oggetto stati:
        ```stati nomeOggetto;```
  - definire le funzion che verranno richiamate come stati. Queste funzioni devono avere la seguente firma:
        ```void funzione(bool firstRun){....}```
  - adesso dentro al ***setup*** bisogna:
    * inizializzare l'oggetto nomeOggetto creato al secondo punto:
        ```nomeOggetto.begin();```
    * passare le funzioni create in precedenza all'oggetto nomeOggetto, tramite il metodo add. in caso di insuccesso restituisce -1 altimenti 1
        ```nomeOggetto.add(funzione);```
    * ad ogni funzione che viene inserita, l'oggetto nomeOggetto punterà a questa, per cui se vogliamo settaro lo stato attivo alla prima funzione
      si deve utilizzare il metodo gotoFirst():
        ```nomeOggetto.gotoFirst();```
      
      In alternativa se volgiamo che l'oggetto punti ad un unaltra funzione bisogna utilizzare:
        + ```goTo(uint8_t item)```  per puntare ad una funzione dell'intervallo
        + ```next()``` per scorrele la lista delle funzioni passate come argomento di 1
        + ```back()``` per scorrerla indietro di 1
  - al fine di poter eseguire le funzioni puntate dall'oggetto stati bisogna utilizzare il metodo ```execProcess();``` scrivendolo nel ***loop***.
    Questo infatti eseguirà ad ogni ciclo, la funzione relativa allo stato corrente.
    La firma delle funzioni impone il parametro booleano *firstRun* perche se true se al ciclo di loop precedente la funzione puntata era differente,
    mentre sarà false se la funzione del ciclo di loop precedente era la stessa.
  
Inoltre la libreria ha anche delle porprietà:
  - ```uint8_t ProcessCurr();```  che restituisce il processo corrente (l'item relativo alla funzione che in quel momento è puntata)
  - ```uint8_t ProcessOld();```   questa restituisce invece l'item della funzione precedentemente puntata
  - ```uint8_t ProcessMax();```   quante funzioni sono state passatein totale

Come si sarà intuito la classe si basa su un puntatore alla seguente struttura:
        
	struct processes{
	   uint8_t id;
	   functionState fun;
	   processes *after;
	   processes *previous;
	};

```functionState``` è il nome del puntatore a funzione ```typedef void(*functionState)(bool firstRun);```

