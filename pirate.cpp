#include <iostream>

#include "pirate.h"
#include "fleet.h"


// Constructor
Pirate::Pirate(int pirate_id, void* fleet_pointer, int rankPirate, int money)
    : m_pirate_id(pirate_id), m_fleet_pointer(fleet_pointer), m_rankPirate(rankPirate), m_money(money) {}

// Destructor
Pirate::~Pirate() {}

// Copy Constructor
Pirate::Pirate(const Pirate& otherPirate)
    : m_pirate_id(otherPirate.m_pirate_id), m_fleet_pointer(otherPirate.m_fleet_pointer), 
      m_rankPirate(otherPirate.m_rankPirate), m_money(otherPirate.m_money) {}

// Assignment Operator
Pirate& Pirate::operator=(const Pirate& otherPirate) {
    if (this == &otherPirate) {
        return *this;
    }
    m_pirate_id = otherPirate.m_pirate_id;
    m_fleet_pointer = otherPirate.m_fleet_pointer;
    m_rankPirate = otherPirate.m_rankPirate;
    m_money = otherPirate.m_money;
    return *this;
}

// Getters
int Pirate::getPirateId() const {
    return m_pirate_id;
}

void* Pirate::getFleetPtr() const {
    return m_fleet_pointer;
}

//int Pirate::getRankPirate() const {
//
//    return (m_rankPirate);
//}

//int Pirate::getRankPirate() const {
//    // Cast the void* m_fleet_pointer to UnionNode* before accessing the Fleet
//    UnionNode* fleetNode = static_cast<UnionNode*>(m_fleet_pointer);
//    // Ensure the cast was successful and that the fleet pointer is valid
//    if (fleetNode && fleetNode->m_fleet) {
//        // Return the rank of the pirate plus the setted_rank from the fleet
//        return m_rankPirate + fleetNode->m_fleet->get_setted_rank();
//    }
//    // If the fleet pointer is invalid, just return the pirate's rank
//    return m_rankPirate;
//}
int accumulateSettedRank(const UnionNode* node) {
    if (node == nullptr || node->m_parent == nullptr) {
        return 0; // Base case: If there's no parent, stop recursion
    }
    return node->m_fleet->get_setted_rank() + accumulateSettedRank(node->m_parent);
}

int Pirate::getRankPirate() const {
    // Cast the void* m_fleet_pointer to UnionNode* before accessing the Fleet
    UnionNode* fleetNode = static_cast<UnionNode*>(m_fleet_pointer);
    // Ensure the cast was successful and that the fleet pointer is valid
    if (fleetNode && fleetNode->m_fleet) {
        // Accumulate the setted_rank recursively through the fleet hierarchy
        int totalSettedRank = accumulateSettedRank(fleetNode);
        // Return the rank of the pirate plus the accumulated setted_rank
        return m_rankPirate + totalSettedRank;
    }

    // If the fleet pointer is invalid, just return the pirate's rank
    return m_rankPirate;
}




int Pirate::getMoney() const {
    return m_money;
}

// Setters
StatusType Pirate::setPirateId(int pirate_id) {
    m_pirate_id = pirate_id;
    return StatusType::SUCCESS; // Assuming StatusType::SUCCESS exists
}

StatusType Pirate::setFleetPtr(void* fleet_pointer) {
    m_fleet_pointer = fleet_pointer;
    return StatusType::SUCCESS;
}

StatusType Pirate::setRankPirate(int rankPirate) {
    m_rankPirate = rankPirate;
    return StatusType::SUCCESS;
}

StatusType Pirate::setMoney(int money) {
    m_money += money;
    return StatusType::SUCCESS;
}
