#ifndef PIRATE_H
#define PIRATE_H

#include"wet2util.h"
#include "DynamicArrayWithList.h"


class Pirate {
private:
    int m_pirate_id;
    void* m_fleet_pointer;
    int m_rankPirate;
    int m_money;

public:
    // Constructor
    Pirate(int pirate_id, void* fleet_pointer = nullptr, int rankPirate = 0, int money = 0);

    // Destructor
    ~Pirate();

    // Copy Constructor
    Pirate(const Pirate& otherPirate);

    // Assignment operator
    Pirate& operator=(const Pirate& otherPirate);

    // Getters
    int getPirateId() const;
    void* getFleetPtr() const;
    int getRankPirate() const;
    int getMoney() const;

    // Setters
    StatusType setPirateId(int pirate_id);
    StatusType setFleetPtr(void* fleet_pointer);
    StatusType setRankPirate(int rankPirate);
    StatusType setMoney(int money);
};


class HashTablePirate{
    DynamicArrayWithList<int, Pirate*>* piratesArray;

public:
    HashTablePirate() : piratesArray(new DynamicArrayWithList<int, Pirate*>()) {}

    ~HashTablePirate() {

        DestroyDataFinal();
        delete piratesArray;
    }

    HashTablePirate(const HashTablePirate&) = delete;
    HashTablePirate& operator=(const HashTablePirate&) = delete;

    int hashFunction(Pirate* element) {
        return (element->getPirateId()) % (piratesArray->m_arraySize);
    }

    DynamicArrayWithList<int, Pirate*>* changeSizeAndCopy(int newSize) {
        DynamicArrayWithList<int, Pirate*>* newArray = new DynamicArrayWithList<int, Pirate*>(newSize);
        int oldSize = piratesArray->m_arraySize;
        for (int i = 0; i < oldSize; ++i) {
            Element<int, Pirate*>* currentNode = piratesArray->m_array[i].getHead();
            while (currentNode != nullptr) {
                //int newIndex = hashFunction(currentNode->m_info);
//////////////////////////////////////////////////////////////////////////////////////
                int newIndex = (currentNode->m_info->getPirateId()) % (newSize);
                try {
                    newArray->insertData(currentNode->m_key, currentNode->m_info, newIndex);
                } catch (std::bad_alloc&) {
                    delete newArray;
                    throw;
                }
                //(newArray->m_size)++;
                currentNode = currentNode->m_next;
            }
        }
        DestroyData();
        return newArray;
    }



    void DestroyData() {
        for (int i = 0; i < piratesArray->m_arraySize; ++i) {
            piratesArray->m_array[i].DestroyListData();
        }
    }
    void DestroyDataFinal() {
        for (int i = 0; i < piratesArray->m_arraySize; ++i) {
            piratesArray->m_array[i].DestroyListDataFinal();
        }
    }

    void expand() {
        int expandedSize = 2 * (piratesArray->m_arraySize);
        DynamicArrayWithList<int, Pirate*>* expandedArray = changeSizeAndCopy(expandedSize);
        delete piratesArray;
        piratesArray = expandedArray;
    }

    void shrink() {
        int shrinkedSize = (piratesArray->m_arraySize) / 2;
        DynamicArrayWithList<int, Pirate*>* shrinkedArray = changeSizeAndCopy(shrinkedSize);
        delete piratesArray;
        piratesArray = shrinkedArray;
    }

    bool insertToTable(Pirate* info) {
        if (piratesArray->m_size >= 3 * piratesArray->m_arraySize) {
            expand();
        }
        if ((piratesArray->m_size <= (0.25 * piratesArray->m_arraySize)) && (piratesArray->m_arraySize > INITIAL_SIZE)) {
            shrink();
        }
        int index = hashFunction(info);
        Element<int, Pirate*>* insertion = piratesArray->insertData(info->getPirateId(), info, index);
        return insertion != nullptr;
    }

    Pirate* findPirate(int playerID) {
        int index = playerID % (piratesArray->m_arraySize);
        Pirate* playerNode = piratesArray->getData(playerID, index);
        return playerNode;
    }
};


#endif // PIRATE_H
