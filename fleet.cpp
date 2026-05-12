#include <iostream>

#include "fleet.h"



// Constructor
Fleet::Fleet(int fleetId, int number_of_pirates, int number_of_ships, bool deleted, int setted_rank)
    : m_fleetId(fleetId), m_number_of_pirates(number_of_pirates), m_number_of_ships(number_of_ships), deleted(deleted),setted_rank(setted_rank) {}

// Destructor
Fleet::~Fleet() {}


// Copy Constructor
Fleet::Fleet(const Fleet &otherFleet)
    : m_fleetId(otherFleet.m_fleetId), m_number_of_pirates(otherFleet.m_number_of_pirates), m_number_of_ships(otherFleet.m_number_of_ships), deleted(otherFleet.deleted),setted_rank(otherFleet.setted_rank) {}

// Assignment operator
Fleet &Fleet::operator=(const Fleet &otherFleet) {
    if (this != &otherFleet) {
        m_fleetId = otherFleet.m_fleetId;
        m_number_of_pirates = otherFleet.m_number_of_pirates;
        m_number_of_ships = otherFleet.m_number_of_ships;
        deleted = otherFleet.deleted;
        setted_rank= otherFleet.setted_rank;
    }
    return *this;
}

// Getters
int Fleet::get_fleetId() const {
    return m_fleetId;
}

int Fleet::get_number_of_pirates() const {
    return m_number_of_pirates;
}

int Fleet::get_number_of_ships() const {
    return m_number_of_ships;
}

bool Fleet::isDeleted() const {
    return deleted;
}

// Setters
void Fleet::set_fleetId(int fleetId) {
    m_fleetId = fleetId;
}

void Fleet::set_number_of_pirates(int number_of_pirates) {
    m_number_of_pirates = number_of_pirates;
}

void Fleet::set_number_of_ships(int number_of_ships) {
    m_number_of_ships = number_of_ships;
}

void Fleet::set_isDeleted(bool condition) {
    deleted = condition;
}

// Update method
void Fleet::updateFleetAttributes(int number_of_pirates, int number_of_ships) {
    m_number_of_pirates += number_of_pirates;
    m_number_of_ships += number_of_ships;
}
int Fleet::get_setted_rank() const {
    return setted_rank;
}
void Fleet::set_setted_rank(int additional_rank) {
    setted_rank += additional_rank; // Add the provided value to the current setted_rank
}