#include <iostream>
#include "graph.h"

/**
* @brief Funzione di test per l'iteratore
* 
* Funzione di test per l'iteratore. Itera i nodi del graph e stampa il name
* 
* @param gr Graph da iterare
*/
template <typename T>
void test_iterator(const graph<T> &gr)
{
    typename graph<T>::const_iterator it, ite;

    std::cout << "Iteratore: " << std::endl;
    for (it = gr.begin(), ite = gr.end(); it != ite; ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
}

struct obj_test
{
    int i;
    double d;
    friend std::ostream &operator<<(std::ostream &os, const obj_test &obj)
    {
        os << "obj test " << obj.i;
        return os;
    }
    bool operator==(const obj_test &obj2)
    {
        return i == obj2.i && d == obj2.d;
    }
};

int main()
{
    int *valori = new int[3];
    valori[0] = 7;
    valori[1] = 8;
    valori[2] = 9;
    graph<int> gr(3, valori);
    char c_valori[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    graph<char> cgr(6, c_valori);
    cgr.addEdge('a', 'f');
    cgr.addEdge('c', 'd');
    cgr.addEdge('e', 'a');
    graph<int> igr(cgr);
    graph<int> copy_gr(gr);
    obj_test obj1 = {160, 60};
    obj_test obj2 = {170, 70};
    obj_test obj3 = {180, 80};
    obj_test objs[3] = {obj1, obj2, obj3};
    graph<obj_test> tgr(3, objs);
    graph<int> gr2 = gr;

    std::cout << "Creato graph" << std::endl;
    std::cout << gr << std::endl;
    std::cout << "Creato graph di char" << std::endl;
    std::cout << cgr << std::endl;
    std::cout << "Creato graph di int da char" << std::endl;
    std::cout << igr << std::endl;
    std::cout << "Creato graph per copia" << std::endl;
    std::cout << copy_gr << std::endl;
    std::cout << "Creato graph da struct" << std::endl;
    std::cout << tgr << std::endl;
    std::cout << "Creato con assegnamento" << std::endl;
    std::cout << gr2 << std::endl;
    try
    {
        gr.addNode(7);
    }
    catch (...)
    {
        std::cout << "* errore nell'inserire nodo *" << std::endl;
    }
    graph<int> grAA;
    grAA.addNode(6);
    grAA.addNode(10);
    grAA.addEdge(6, 10);
    std::cout << "AAAAAAAAAAAAAAAAAAAAAAAA" << std::endl;
    std::cout << grAA << std::endl;

    gr.addEdge(7, 8);
    gr.addEdge(7, 9);
    gr.addEdge(8, 9);
    gr.addEdge(9, 8);
    gr.addEdge(8, 8);
    tgr.addEdge(obj1, obj2);
    tgr.addEdge(obj2, obj3);
    tgr.addEdge(obj2, obj1);
    tgr.addEdge(obj3, obj1);
    std::cout << "Aggiunti archi al primo graph" << std::endl;
    std::cout << gr << std::endl;
    std::cout << "Aggiunti archi al graph di struct" << std::endl;
    std::cout << tgr << std::endl;
    std::cout << "Creato con assegnamento dopo la modifica" << std::endl;
    std::cout << gr2 << std::endl;

    try
    {
        gr.addEdge(7, 1); // Errore
    }
    catch (...)
    {
        std::cout << "* Errore nell'aggiungere arco *" << std::endl
                  << std::endl;
    }
    gr.removeEdge(8, 9);
    tgr.removeEdge(obj1, obj2);
    std::cout << "Rimosso un arco" << std::endl;
    std::cout << gr << std::endl;
    std::cout << "Rimosso un arco al graph di struct" << std::endl;
    std::cout << tgr << std::endl;

    gr.addNode(6);
    obj_test tmp_obj = {175, 75};
    tgr.addNode(tmp_obj);
    std::cout << "Aggiunto nodo" << std::endl;
    std::cout << gr << std::endl;
    std::cout << "Aggiunto nodo al graph di struct" << std::endl;
    std::cout << tgr << std::endl;

    try
    {
        std::cout << "Rimuovo terzo nodo" << std::endl;
        gr.removeNode(9);
        tgr.removeNode(obj3);
    }
    catch (...)
    {
        std::cout << "* Errore nel rimuovere un nodo *" << std::endl
                  << std::endl;
    }
    std::cout << gr << std::endl;
    std::cout << tgr << std::endl;

    std::cout << "Esiste il nodo '6'? " << gr.exists(6) << std::endl;
    std::cout << "Esiste il nodo '15'? " << gr.exists(15) << std::endl;
    std::cout << "Esiste il nodo '7'? " << gr.exists(7) << std::endl;
    std::cout << "Esiste il nodo 'obj2'? " << tgr.exists(obj2) << std::endl;

    try
    {
        std::cout << "Esiste arco tra '7' e '8'? " << gr.hasEdge(7, 8) << std::endl;
        std::cout << "Esiste arco tra '6' e '8'? " << gr.hasEdge(6, 8) << std::endl;
        std::cout << "Esiste arco tra 'obj1' e 'obj2'? " << tgr.hasEdge(obj1, obj2) << std::endl;
        std::cout << "Esiste arco tra '10' e '8'? " << gr.hasEdge(10, 8) << std::endl;
    }
    catch (...)
    {
        std::cout << "* Errore arco non esistente *" << std::endl;
    }

    std::cout << std::endl;
    test_iterator(gr);
    test_iterator(cgr);

    delete[] valori;
    valori = nullptr;

    return 0;
}