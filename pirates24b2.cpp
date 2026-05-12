#include <iostream>

#include"pirates24b2.h"


oceans_t::oceans_t(): pirates(), fleets(new UnionFind())
{
	// TODO: Your code goes here
}

oceans_t::~oceans_t() {

    delete fleets;

}

StatusType oceans_t::add_fleet(int fleetId)
{
	// TODO: Your code goes here
	if (fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }

    UnionNode* fleetNode = fleets->getFleet(fleetId);
    if (fleetNode) {
        return StatusType::FAILURE;
    }

    if (!fleets->addFleet(fleetId)) {
        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType oceans_t::add_pirate(int pirateId, int fleetId)
{
    // Check for invalid input
    if (pirateId <= 0 || fleetId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    // Check if the pirate is already in the system
    if (pirates.findPirate(pirateId) != nullptr) {
        return StatusType::FAILURE; // Pirate already exists
    }

    // Retrieve the fleet
    UnionNode* fleetNode = fleets->getFleet(fleetId);
    if (!fleetNode || fleets->find(fleetNode) != fleetNode) {
        return StatusType::FAILURE; // Fleet not found or Fleet has a parent
    }

    // Add the pirate to the fleet
    Fleet* fleet = fleetNode->m_fleet;
    Pirate* newPirate = new Pirate(pirateId, fleetNode);
    if (!pirates.insertToTable(newPirate)) {
        delete newPirate; // Avoid memory leak if insertion fails
        return StatusType::FAILURE;
    }
//    fleet->pirates_on_fleet.insertToTable(newPirate);
    fleet->set_number_of_pirates(fleet->get_number_of_pirates() + 1);
    newPirate->setRankPirate(fleet->get_number_of_pirates());

    return StatusType::SUCCESS;
}


StatusType oceans_t::pay_pirate(int pirateId, int salary)
{
	// TODO: Your code goes here
	if (pirateId <= 0 || salary <= 0) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate = pirates.findPirate(pirateId);
    if (!pirate){
         return StatusType::FAILURE;
        }
	(pirate)->setMoney(salary);
	return StatusType::SUCCESS;
}

output_t<int> oceans_t::num_ships_for_fleet(int fleetId)
{
    // Check for invalid input
    if (fleetId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }

    // Retrieve the fleet
    UnionNode* fleetNode = fleets->getFleet(fleetId);
    if (!fleetNode) {
        return output_t<int>(StatusType::FAILURE); // Fleet not found
    }

    // Check if the fleet is deleted
    if (fleetNode->m_fleet->isDeleted()) {
        return output_t<int>(StatusType::FAILURE); // Fleet is deleted
    }

    // Return the number of ships in the fleet
    return output_t<int>(fleetNode->m_fleet->get_number_of_ships());
}

output_t<int> oceans_t::get_pirate_money(int pirateId)
{
    // TODO: Your code goes here
    if (pirateId <= 0) {
        return output_t<int>(StatusType::INVALID_INPUT);
    }
    Pirate* pirate = pirates.findPirate(pirateId);
    if (!pirate) {
        return output_t<int>(StatusType::FAILURE);
    }
    return output_t<int>((pirate)->getMoney());
}

StatusType oceans_t::unite_fleets(int fleetId1, int fleetId2)
{
    // Validate the input
    if (fleetId1 <= 0 || fleetId2 <= 0 || fleetId1 == fleetId2) {
        return StatusType::INVALID_INPUT;
    }

    // Retrieve the fleets
    UnionNode* fleet1 = fleets->getFleet(fleetId1);
    UnionNode* fleet2 = fleets->getFleet(fleetId2);

    // Check if either fleet does not exist or is empty
    if (!fleet1 || !fleet2 || fleet1->m_fleet->get_number_of_pirates() == 0 || fleet2->m_fleet->get_number_of_pirates() == 0) {
        return StatusType::FAILURE;
    }

    // Check if either fleet is marked as deleted
    if (fleet1->m_fleet->isDeleted() || fleet2->m_fleet->isDeleted()) {
        return StatusType::FAILURE;
    }

    // Perform the union of the fleets
    fleets->unionFleets(fleetId1, fleetId2);
    return StatusType::SUCCESS;
}

StatusType oceans_t::pirate_argument(int pirateId1, int pirateId2)
{
    // TODO: Your code goes here
    if (pirateId1 <= 0 || pirateId2 <= 0 || pirateId1 == pirateId2) {
        return StatusType::INVALID_INPUT;
    }
    Pirate* pirate1 = pirates.findPirate(pirateId1);
    Pirate* pirate2 = pirates.findPirate(pirateId2);
    if (!pirate1 || !pirate2) {
        return StatusType::FAILURE;
    }

    UnionNode* fleet1 = static_cast<UnionNode*>((pirate1)->getFleetPtr());
    UnionNode* fleet2 = static_cast<UnionNode*>((pirate2)->getFleetPtr());
    if (!fleet1 || !fleet2) {
        return StatusType::FAILURE;
    }

    // Separate checks for the deleted flag
    if (fleet1->m_fleet->isDeleted()) {
        UnionNode *fleetNodeParent1 = fleets->find(fleet1);
        if (!fleetNodeParent1) {
            return StatusType::FAILURE;
        }
        if (fleetNodeParent1 != fleets->find(fleet2)) {
            return StatusType::FAILURE;
        }
    }

    if (fleet2->m_fleet->isDeleted()) {
        UnionNode *fleetNodeParent2 = fleets->find(fleet2);
        if (!fleetNodeParent2) {
            return StatusType::FAILURE;
        }
        if (fleetNodeParent2 != fleets->find(fleet1)) {
            return StatusType::FAILURE;
        }
    }

    // Check if both fleets are the same if neither is deleted
    if (!fleet1->m_fleet->isDeleted() && !fleet2->m_fleet->isDeleted()) {
        if (fleet1 != fleet2) {
            return StatusType::FAILURE;
        }
    }
     if ((pirate1->getRankPirate()) > (pirate2->getRankPirate())) {
        pirate1->setMoney(-((pirate1->getRankPirate()) - (pirate2->getRankPirate())));
        pirate2->setMoney(((pirate1->getRankPirate()) - (pirate2->getRankPirate())));
    } else {
        pirate1->setMoney(((pirate2->getRankPirate())-(pirate1->getRankPirate())));
        pirate2->setMoney(-((pirate2->getRankPirate())-(pirate1->getRankPirate())));
    }
    return StatusType::SUCCESS;
}

