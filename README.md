# Oriented Graph

La prima parte consiste nella creazione di una classe templata che rappresenti un Grafo
orientato.
Come membri della classe abbiamo un puntatore a uno o più Node, struct interna costituita da
un name di tipo generico e un puntatore a una riga di Matrix (puntatore implementato
inizialmente ma poi non utilizzato nel progetto) e Size, int che rappresenta il numero di nodi
presenti.
Come altro membro abbiamo Matrix, la Matrice di adiacenza vera e propria che rappresenta i
collegamenti - archi - tra un nodo e l’altro. La matrice avrà grandezza pari a Size x Size, con
righe e colonne che rappresentano i vari nodi.
Per inizializzare un oggetto bisogna passare come parametri un int che rappresenta la size e un
puntatore a uno o più elementi di tipo generico.

Dopo i metodi fondamentali della classe (costruttore che inizializza i membri, distruttore, copy
constructor e operatore di assegnamento) sono presenti i quattro metodi per
aggiungere/rimuovere rispettivamente un nodo e un arco.

Per aggiungere un nodo il metodo addNode crea un oggetto node a partire dal parametro di tipo
generico e aggiunge una riga e una colonna alla matrice di adiacenza. Viene infine anche
aggiornato Size. Nel caso esistesse già un nodo con lo stesso nome viene lanciato un errore.
Per rimuoverne uno, invece, removeNode cerca il nodo con lo stesso nome del parametro
generico passato e, in caso questo esista, rimuove il node dall’array membro della classe ed
elimina le rispettive riga e colonna - tramite indice.
Per fare ciò viene creata una matrice temporanea (con un size di più o meno uno in base al
metodo chiamato) con i dati presi dell’originale più quelli del node da aggiungere o meno quello
del node da rimuovere.

Per aggiungere un arco vengono passati il nome del nodo d’origine e quello di destinazione,
vengono cercati nell’array membro della classe e, se trovati, viene posto il rispettivo bool nella
matrice di adiacenza a true. La ricerca avviene tramite indice preso dall’array.
Per rimuovere un arco il procedimento è simile, con la sola differenza che il valore della matrice
di adiacenza viene posto a false.
Nel caso aggiungendo/rimuovendo archi e nodi vengano passati come parametri nodi non
esistenti o già esistenti vengono lanciati errori tramite l’espressione throw.

Abbiamo poi i metodi exist e hasEdge per sapere se, rispettivamente, un nodo esiste e se un
arco tra due nodi esiste (e quindi il rispettivo valore nella matrice è posto a true).
Per la prima funzione viene cercato il nodo nell’array membro e, se esiste, viene restituito true.
Per cercare l’arco vengono cercati i nodi di origine e destinazione e, se esistono, viene
controllato il valore nella matrice di adiacenza, altrimenti viene lanciato un errore.

I metodi begin e end servono per istanziare un const Iterator, classe implementata dentro graph.

Ci sono, infine, metodi di supporto come Swap o overload di operatori.
Nel file main.cpp, oltre a vari test con tipi base, è presente una struct custom chiamata obj_test
per testare la classe con dei tipi custom.
Il file inoltre contiene la funzione test_iterator per testare un iteratore di graph.
