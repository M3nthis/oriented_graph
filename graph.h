#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <cassert>
#include <algorithm> // std::swap
#include <stddef.h>  // ptrdiff_t

/**
 * @file graph.h
 * @brief Dichiarazioned della classe graph
 */

/**
 * @brief Grafo orientato
 * 
 * Classe che rappresenta un Grafo orientato
 */
template <typename T>
class graph
{
public:
    struct node
    {
        T name;
        bool *matrixRowPtr;
    };

private:
    node *_nodes;       ///< Puntatore all'array dinamico di nodi
    unsigned int _size; ///< Numero di nodi
    bool **_matrix;     ///< Puntatore alla matrice dinamica di bool

public:
    /**
    * @brief Costruttore di default (METODO FONDAMENTALE 1)
    * 
    * Costruttore di default per istanziare un graph vuoto
    * 
    * @post _nodes == nullptr
    * @post _size == 0
    * @post _matrix == nullptr
    */
    graph() : _nodes(nullptr), _size(0), _matrix(nullptr){};

    /**
    * @brief Costruttore secondario 
    * 
    * Costruttore secondario che crea un graph con un numero di nodi della dimensione data
    * e inizializza i valori dei nodi e della matrice di adiacenza
    * 
    * @pre Gli elementi di tipo T devono essere tutti diversi
    * 
    * @param size Numero di nodi da creare
    * @param values Nomi dei nodi
    */
    graph(unsigned int size, const T *values) : _nodes(nullptr), _size(0), _matrix(nullptr)
    {
        try
        {
            _size = size;
            _nodes = new node[_size];
            // _nodes->matrixRowPtr = nullptr;
            (*_nodes).matrixRowPtr = nullptr;
            _matrix = new bool *[_size];
            for (unsigned int i = 0; i < _size; i++)
            {
                _matrix[i] = new bool[_size];
                node nd = {values[i], _matrix[i]};
                for (unsigned int k = 0; k < i; k++)
                {
                    // Se esiste già un nodo con lo stesso nome
                    if (_nodes[k].name == nd.name)
                    {
                        throw 1;
                    }
                }
                _nodes[i] = nd;
                for (unsigned int j = 0; j < _size; j++)
                {
                    _matrix[i][j] = false;
                }
            }
        }
        catch (int e)
        {
            delete[] _nodes;
            for (int i = 0; i < _size; i++)
            {
                delete[] _matrix[i];
            }
            delete[] _matrix;
            _nodes = nullptr;
            _matrix = nullptr;
            _size = 0;
            throw;
        }
        catch (...)
        {
            delete[] _nodes;
            for (int i = 0; i < _size; i++)
            {
                delete[] _matrix[i];
            }
            delete[] _matrix;
            _nodes = nullptr;
            _matrix = nullptr;
            _size = 0;
            throw;
        }
    };

    /**
    * @brief Copy constructor (METODO FONDAMENTALE 3)
     * 
     * Costruttore di copia tra un graph e un altro
     * 
     * @param other altro graph da copiare
     */
    graph(const graph &other)
    {
        try
        {
            _size = other._size;
            _nodes = new node[_size];
            // _nodes->matrixRowPtr = nullptr;
            (*_nodes).matrixRowPtr = nullptr;
            _matrix = new bool *[_size];
            for (unsigned int i = 0; i < _size; i++)
            {
                _matrix[i] = new bool[_size];
                T otherName = other.nodeFromIndex(i).name;
                node nd = {otherName, _matrix[i]};
                _nodes[i] = nd;
                for (unsigned int j = 0; j < _size; j++)
                {
                    _matrix[i][j] = other._matrix[i][j];
                }
            }
        }
        catch (...)
        {
            delete[] _nodes;
            for (int i = 0; i < _size; i++)
            {
                delete[] _matrix[i];
            }
            delete[] _matrix;
            _nodes = nullptr;
            _matrix = nullptr;
            _size = 0;
            throw;
        };
    }

    /**
     * @brief Costruttore di conversione
     * 
     * Costruttore di conversione da un graph di tipo O a un graph di tipo T
     * 
     * @param other graph da copiare di tipo O 
     */
    template <typename O>
    graph(const graph<O> &other) : _nodes(nullptr), _size(0), _matrix(nullptr)
    {
        try
        {
            _size = other.size();
            _nodes = new node[size()];
            // _nodes->matrixRowPtr = nullptr;
            (*_nodes).matrixRowPtr = nullptr;
            _matrix = new bool *[size()];
            for (unsigned int i = 0; i < _size; i++)
            {
                _matrix[i] = new bool[_size];
                O otherName = other.nodeFromIndex(i).name;
                node nd = {static_cast<T>(otherName), _matrix[i]};
                _nodes[i] = nd;
                for (unsigned int j = 0; j < _size; j++)
                {
                    _matrix[i][j] = other.matrix()[i][j];
                }
            }
        }
        catch (...)
        {
            delete[] _nodes;
            for (int i = 0; i < _size; i++)
            {
                delete[] _matrix[i];
            }
            delete[] _matrix;
            _nodes = nullptr;
            _matrix = nullptr;
            _size = 0;
            throw;
        };
    };

    /**
     * @brief Operatore di assegnamento (METODO FONDAMENTALE 4)
     * 
     * Operatore di assegnamento che serve per copiare il contenuto di other
     * in *this
     * 
     * @param other graph da copiare
     * 
     * @return reference a graph
     */
    graph &operator=(const graph &other)
    {
        if (this != &other)
        {
            graph tmp_gr(other);

            tmp_gr.swap(*this);
        }

        return *this;
    };

    /**
     * @brief methodo Swap che scambia i dati interni con un altro graph
     * 
     * Funzione che scambia gli stati interni tra i due graph
     * 
     * @param other graph sorgente
     */
    void swap(graph &other)
    {
        std::swap(this->_nodes, other._nodes);
        std::swap(this->_size, other._size);
        std::swap(this->_matrix, other._matrix);
    };

    /**
     * @brief Distruttore della classe (METODO FONDAMENTALE 2)
     * 
     * Distruttore della classe. Rimuove dallo Heap gli array dinamici
     * allocati in precedenza.
     */
    ~graph()
    {
        delete[] _nodes;
        std::cout << "Distruttore, _size: " << _size << std::endl;
        for (int i = 0; i < _size; i++)
        {
            delete[] _matrix[i];
        }
        delete[] _matrix;
        _nodes = nullptr;
        _matrix = nullptr;
        _size = 0;
    };

    /**
     *  * @brief Getter del nodo index-esimo
     * 
     * Funzione che permette di leggere  il nodo index-esimo
     * 
     * @param indice del nodo da leggere
     * 
     * @pre index < _size
     * 
     * @return reference al nodo index-esimo
     */
    const node &nodeFromIndex(unsigned int index) const
    {
        assert(index < _size);

        return _nodes[index];
    };

    /**
     * @brief Getter della size 
     * 
     * Funzione che permette di leggere la dimensione dei nodi
     * 
     * @return Size di Graph
     */
    const unsigned int &size() const
    {
        return _size;
    };

    /**
     * @brief Getter della matrice di adiacenza 
     * 
     * Funzione che permette di leggere matrice di adiacenza
     * 
     * @return Puntatore alla matrice
     */
    bool **matrix() const
    {
        return _matrix;
    }

    /**
     * @brief Funzione per aggiungere archi
     * 
     * Funzione che permette di aggiungere un arco tra due nodi
     * 
     * @param origin_node Reference al primo nodo
     * @param destination_node Reference al secondo nodo
     */
    void addEdge(const T &origin_node, const T &destination_node)
    {
        int origin_index = -1;
        int destination_index = -1;
        try
        {

            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == origin_node)
                {
                    origin_index = i;
                }
            }
            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == destination_node)
                {
                    destination_index = i;
                }
            }
            // Se non sono stati trovati nodi corrispondenti lancio un errore
            if (origin_index == -1 || destination_index == -1)
            {
                throw 1;
            };
        }
        catch (int e)
        {
            throw;
        };

        _matrix[origin_index][destination_index] = true;
    };

    /**
     * @brief Funzione per rimuovere archi
     * 
     * Funzione che permette di rimuovere un arco tra due nodi
     * 
     * @param origin_node Reference al primo nodo
     * @param destination_node Reference al secondo nodo
     */
    void removeEdge(const T &origin_node, const T &destination_node)
    {
        int origin_index = -1;
        int destination_index = -1;
        try
        {

            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == origin_node)
                {
                    origin_index = i;
                }
            }
            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == destination_node)
                {
                    destination_index = i;
                }
            }
            // Se non sono stati trovati nodi corrispondenti lancio un errore
            if (origin_index == -1 || destination_index == -1)
            {
                throw 1;
            };
        }
        catch (int e)
        {
            throw;
        };

        _matrix[origin_index][destination_index] = false;
    };

    /**
     * @brief Funzione per aggiungere un nodo
     * 
     * Funzione che permette di aggiungere un nodo
     * 
     * @pre Gli elementi di tipo T devono essere tutti diversi
     * 
     * @param node_name Nodo da aggiungere
     */
    void addNode(const T &node_name)
    {
        bool **tmp;
        node *tmp_nodes;
        try
        {
            tmp = new bool *[_size + 1];
            tmp_nodes = new node[_size + 1];
            // tmp_nodes->matrixRowPtr = nullptr;
            (*tmp_nodes).matrixRowPtr = nullptr;

            for (unsigned int i = 0; i < _size; i++)
            {
                tmp[i] = new bool[_size + 1];
                node nd = {_nodes[i].name, tmp[i]};
                tmp_nodes[i] = nd;
                for (unsigned int j = 0; j < _size; j++)
                    tmp[i][j] = _matrix[i][j];
                tmp[i][_size] = false; // Setto false all'ultima colonna di ogni riga
            };
            // Aggiungo ultima riga
            tmp[_size] = new bool[_size + 1];
            node nd = {node_name, tmp[_size]};
            if (exists(nd.name))
            {
                // Se esiste già un nodo con lo stesso nome
                throw 1;
            }
            tmp_nodes[_size] = nd;
            for (unsigned int i = 0; i < _size + 1; i++)
            {
                tmp[_size][i] = false; // Setto a false tutta la nuova riga
            };
        }
        catch (int e)
        {
            for (int i = 0; i < _size + 1; i++)
                delete[] tmp[i];
            delete[] tmp;
            delete[] tmp_nodes;
            throw;
        }
        catch (...)
        {
            for (int i = 0; i < _size + 1; i++)
                delete[] tmp[i];
            delete[] tmp;
            delete[] tmp_nodes;
            throw;
        }

        std::swap(tmp, _matrix);
        std::swap(tmp_nodes, _nodes);

        // Pulisco memoria heap
        for (int i = 0; i < _size; i++)
            delete[] tmp[i];
        delete[] tmp;
        delete[] tmp_nodes;
        tmp = nullptr;
        tmp_nodes = nullptr;

        // Aggiorno _size
        _size++;
    };

    /**
     * @brief Funzione per rimuovere un nodo
     * 
     * Funzione che permette di rimuovere un nodo
     * 
     * @param node_name Nodo da rimuovere
     */
    void removeNode(const T &node_name)
    {
        int rowToDelete = -1;

        // Controllo se il nodo è valido
        try
        {
            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == node_name)
                    rowToDelete = i;
            };

            if (rowToDelete == -1)
            {
                throw 1;
            }
        }
        catch (int e)
        {
            throw;
        };

        bool **tmp;
        node *tmp_nodes;
        try
        {
            int columnToDelete = rowToDelete;
            tmp = new bool *[_size - 1];
            tmp_nodes = new node[_size - 1];
            // tmp_nodes->matrixRowPtr = nullptr;
            (*tmp_nodes).matrixRowPtr = nullptr;
            // creo nuove righe (escludendo quella da togliere)
            unsigned int rowCount = 0;
            for (unsigned int i = 0; i < _size; i++)
            {
                if (i != rowToDelete)
                {
                    tmp[rowCount] = new bool[_size - 1];
                    node nd = {_nodes[i].name, tmp[rowCount]};
                    tmp_nodes[rowCount] = nd;
                    // creo nuove colonne (escludendo quella da togliere)
                    unsigned int columnCount = 0;
                    for (unsigned int j = 0; j < _size; j++)
                    {
                        if (j != columnToDelete)
                        {
                            tmp[rowCount][columnCount] = _matrix[i][j];
                            columnCount++;
                        }
                    };

                    rowCount++;
                }
            }
        }
        catch (...)
        {
            for (int i = 0; i < _size - 1; i++)
                delete[] tmp[i];
            delete[] tmp;
            delete[] tmp_nodes;
            throw;
        }

        std::swap(tmp, _matrix);
        std::swap(tmp_nodes, _nodes);

        // Pulisco memoria heap
        for (int i = 0; i < _size; i++)
            delete[] tmp[i];
        delete[] tmp;
        delete[] tmp_nodes;
        tmp = nullptr;
        tmp_nodes = nullptr;

        // Aggiorno _size
        _size--;
    }

    /**
     * @brief Funzione per verificare l'esistenza di un nodo
     * 
     * Funzione che permette di verificare l'esistenza di un nodo
     * 
     * @param nodeName Nome del nodo da verificare
     * 
     * @return bool per l'esistenza del nodo
     */
    bool exists(const T &nodeName)
    {
        bool nodeExists = false;
        for (unsigned int i = 0; i < _size; i++)
        {
            if (_nodes[i].name == nodeName)
            {
                nodeExists = true;
                break;
            };
        }
        return nodeExists;
    }

    /**
     * @brief Funzione per verificare l'esistenza di un arco tra due nodi
     * 
     * Funzione che permette di verificare l'esistenza di un arco tra due nodi
     * 
     * @param origin_node Reference al primo nodo
     * @param destination_node Reference al secondo nodo
     * 
     * @return bool per l'esistenza dell'arco
     */
    bool hasEdge(const T &origin_node, const T &destination_node)
    {
        int origin_index = -1;
        int destination_index = -1;
        try
        {

            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == origin_node)
                {
                    origin_index = i;
                }
            }
            for (unsigned int i = 0; i < _size; i++)
            {
                if (_nodes[i].name == destination_node)
                {
                    destination_index = i;
                }
            }
            // Se non sono stati trovati nodi corrispondenti lancio un errore
            if (origin_index == -1 || destination_index == -1)
            {
                throw 1;
            };
        }
        catch (int e)
        {
            throw;
        };

        return _matrix[origin_index][destination_index];
    }

    // ITERATORI //////////////////////////////////////////////////////////////////

    class const_iterator
    {
        const node *_ptr;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef node value_type;
        typedef ptrdiff_t difference_type;
        typedef const node *pointer;
        typedef const node &reference;

        /**
        * @brief Costruttore di default
        * 
        * Costruttore di default per istanziare un const iterator
        * 
        * @post _ptr == nullptr
        */
        const_iterator() : _ptr(nullptr){};

        /**
        * @brief Copy constructor
        * 
        * Costruttore di copia tra un graph e un altro
        * 
        * @param other altro const iterator da copiare
        */
        const_iterator(const const_iterator &other) : _ptr(nullptr){};

        /**
        * @brief Operatore di assegnamento 
        * 
        * Operatore di assegnamento che serve per copiare il contenuto di other
        * in *this
        * 
        * @param other const iterator da copiare
        * 
        * @return reference al const iterator
        */
        const_iterator &operator=(const const_iterator &other)
        {
            _ptr = other._ptr;

            return *this;
        };

        /**
        * @brief Distruttore della classe 
        * 
        * Distruttore della classe.
        */
        ~const_iterator(){};

        /**
        * @brief operator*
        * 
        * operator*.
        * 
        * @return Ritorna il dato riferito dall'iteratore (dereferenziamento)
        */
        reference operator*() const
        {
            return *_ptr;
        }

        /**
        * @brief operator->
        * 
        * operator->.
        * 
        * @return Ritorna il puntatore al dato riferito dall'iteratore)
        */
        pointer operator->() const
        {
            return _ptr;
        }

        /**
        * @brief operator++ post-incremento
        * 
        * operator++. Operatore di iterazione post-incremento.
        * creo una copia attuale così posso incrementare ptr e restituire questa
        * 
        * @return Ritorna la copia attuale
        */
        const_iterator operator++(int)
        {
            const_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        /**
        * @brief operator++ pre-incremento
        * 
        * operator++. Operatore di iterazione pre-incremento.
        * 
        * @return dato puntato da this
        */
        const_iterator &operator++()
        {
            ++_ptr;
            return *this;
        }

        /**
        * @brief operator== operatore di ugualianza
        * 
        * operator==, operatore di ugualianza
        * 
        * @return se i due puntatori hanno lo stesso indirizzo
        */
        bool operator==(const const_iterator &other) const
        {
            return _ptr == other._ptr;
        }

        /**
        * @brief operator!= operatore di diversità
        * 
        * operator!=, operatore di diversità
        * 
        * @return se i due puntatori hanno un indirizzo diverso
        */
        bool operator!=(const const_iterator &other) const
        {
            return _ptr != other._ptr;
        }

    private:
        //Dati membro

        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class graph;

        /**
        * @brief Costruttore privato di inizializzazione
        * 
        * Costruttore privato di inizializzazione usato dalla classe container
        * tipicamente nei metodi begin e end
        */
        const_iterator(const node *p) : _ptr(p) {}

    }; // FINE classe const_iterator

    /**
     * @brief Inizio Iteratore
     * 
     * Funzione che ritorna l'iteratore all'inizio della sequenza dati
     * 
     * @return Const iterator
     */
    const_iterator begin() const
    {
        return const_iterator(_nodes);
    }

    /**
     * @brief Fine Iteratore
     * 
     * Funzione che ritorna la fine della sequenza dati
     * 
     * @return Const iterator
     */
    const_iterator end() const
    {
        return const_iterator(_nodes + _size);
    }

    /**
    * Funzione usata su operatore << per mandare un oggetto node
    * su uno stream di dati di output
    */
    friend std::ostream &operator<<(std::ostream &os, const typename graph<T>::node &nd)
    {
        os << nd.name;
        return os;
    }

    /**
    * Funzione usata su operatore << per mandare un iteratore di graph
    * su uno stream di dati di output
    */
    friend std::ostream &operator<<(std::ostream &os, typename graph::const_iterator &it)
    {
        os << "ITERATORE" << std::endl;
        return os;
    }
}; // FINE CLASSE;

/**
* Funzione usata su operatore << per mandare un oggetto graph
* su uno stream di dati di output
*/
template <typename T>
std::ostream &operator<<(std::ostream &os, const graph<T> &gr)
{
    for (unsigned int i = 0; i < gr.size(); i++)
    {
        os << gr.nodeFromIndex(i).name << ": ";
        for (unsigned int j = 0; j < gr.size(); j++)
            os << gr.matrix()[i][j] << " ";
        os << std::endl;
    }

    return os;
}

#endif