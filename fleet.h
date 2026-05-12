#ifndef FLEET_H_
#define FLEET_H_


#include <iostream>
#include "pirate.h"
#include "DynamicArrayWithList.h"


class Fleet {
private:
    int m_fleetId;
    int m_number_of_pirates;
    int m_number_of_ships;
    bool deleted;
    int setted_rank;

public:
    //HashTablePirate pirates_on_fleet;
    // Constructor
    Fleet(int fleetId, int number_of_pirates = 0, int number_of_ships = 1, bool deleted = false,int setted_rank=0);

    // Destructor
    ~Fleet();

    // Copy Constructor
    Fleet(const Fleet &otherFleet);

    // Assignment operator
    Fleet &operator=(const Fleet &otherFleet);

    // Getters
    int get_fleetId() const;
    int get_number_of_pirates() const;
    int get_number_of_ships() const;
    bool isDeleted() const;
    int get_setted_rank() const; // Getter for setted_rank

    // Setters
    void set_fleetId(int fleetId);
    void set_number_of_pirates(int number_of_pirates);
    void set_number_of_ships(int number_of_ships);
    void set_isDeleted(bool condition);
    void set_setted_rank(int additional_rank); // Setter for setted_rank

    // Update method
    void updateFleetAttributes(int number_of_pirates, int number_of_ships);
};

class UnionNode {
public:
    Fleet* m_fleet;
    UnionNode* m_parent;

    UnionNode(Fleet* m_fleet, UnionNode* m_parent)
        : m_fleet(m_fleet), m_parent(m_parent) {}

    ~UnionNode() {
        delete m_fleet;
//        delete m_parent;
    }
};

class HashTable {
    DynamicArrayWithList<int, UnionNode*>* fleetsArray;

public:
    HashTable() : fleetsArray(new DynamicArrayWithList<int, UnionNode*>()) {}

    ~HashTable() {
        DestroyDataFinal();
        delete fleetsArray;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;
/////////////////////////////////////////////////////////////
    int hashFunction(UnionNode* element) {
        return (element->m_fleet->get_fleetId()) % (fleetsArray->m_arraySize);
    }

    DynamicArrayWithList<int, UnionNode*>* changeSizeAndCopy(int newSize) {
        DynamicArrayWithList<int, UnionNode*>* newArray = new DynamicArrayWithList<int, UnionNode*>(newSize);
        int oldSize = fleetsArray->m_arraySize;

        for (int i = 0; i < oldSize; ++i) {
            Element<int, UnionNode*>* currentNode = fleetsArray->m_array[i].getHead();
            while (currentNode != nullptr) {
                //int newIndex = hashFunction(currentNode->m_info);
                int newIndex = (currentNode->m_info->m_fleet->get_fleetId()) % (newSize);
                try {
                    newArray->insertData(currentNode->m_key, currentNode->m_info, newIndex);

                } catch (std::bad_alloc&) {
                    delete newArray;
                    throw;
                }
                //(newArray->m_size)++;
//                int oldIndex = currentNode->m_info->m_fleet->get_fleetId() % (fleetsArray->m_arraySize);
//                fleetsArray->removeData(currentNode->m_key,oldIndex);
                currentNode = currentNode->m_next;
            }
        }
        DestroyData();
        return newArray;
    }

    void DestroyData() {
        for (int i = 0; i < fleetsArray->m_arraySize; ++i) {
            fleetsArray->m_array[i].DestroyListData();
        }
    }
    void DestroyDataFinal() {
        for (int i = 0; i < fleetsArray->m_arraySize; ++i) {
            fleetsArray->m_array[i].DestroyListDataFinal();
        }
    }

    void expand() {
        int expandedSize = 2 * (fleetsArray->m_arraySize);
        DynamicArrayWithList<int, UnionNode*>* expandedArray = changeSizeAndCopy(expandedSize);
        //delete fleetsArray->m_array;
        delete fleetsArray;
        fleetsArray = expandedArray;
    }

    void shrink() {
        int shrinkedSize = (fleetsArray->m_arraySize) / 2;
        DynamicArrayWithList<int, UnionNode*>* shrinkedArray = changeSizeAndCopy(shrinkedSize);
        delete fleetsArray;
        fleetsArray = shrinkedArray;
    }

    bool insertToTable(UnionNode* info) {
        if (fleetsArray->m_size >= 3 * fleetsArray->m_arraySize) {
            expand();
        }
        if ((fleetsArray->m_size <= (0.25 * fleetsArray->m_arraySize)) && (fleetsArray->m_arraySize > INITIAL_SIZE)) {
            shrink();
        }
        int index = hashFunction(info);
        Element<int, UnionNode*>* insertion = fleetsArray->insertData(info->m_fleet->get_fleetId(), info, index);
        return insertion != nullptr;
    }

    UnionNode* findFleet(int playerID) {
        int index = playerID % (fleetsArray->m_arraySize);
        UnionNode* playerNode = fleetsArray->getData(playerID, index);
        return playerNode;
    }
};

#endif // FLEET_H_
