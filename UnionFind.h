#ifndef UNIONFIND_H_
#define UNIONFIND_H_

class UnionFind {
private:
    HashTable fleetsTable;

public:
    UnionFind() : fleetsTable() {}
    ~UnionFind() {}

    // Find the root of the fleet with path compression
//UnionNode* find(UnionNode* node) {
//    if (node == nullptr) {
//        return nullptr;
//    }
//    if (node->m_parent != node) {
//        node->m_parent = find(node->m_parent);
//    }
//    return node->m_parent;
//}

//UnionNode* find(UnionNode* node) {
//    if (node->m_parent == nullptr) {
//        return node;
//    }
//    if (node->m_parent != nullptr) {
//
//        node->m_parent = find(node->m_parent);
//    }
//    return node->m_parent;
//}
    UnionNode* find(UnionNode* node) {
        if (node->m_parent == nullptr) {
            return node; // If the node is the root, return it
        }
        // Recursively find the root, compressing the path
        UnionNode* root = find(node->m_parent);
        // Update setted_rank for the current node based on its parent's setted_rank
        if (root != node->m_parent) {
            node->m_fleet->set_setted_rank(node->m_parent->m_fleet->get_setted_rank() );
           // node->m_fleet->set_setted_rank(node->m_parent->m_fleet->get_setted_rank() - node->m_fleet->get_setted_rank());
            node->m_parent = root; // Path compression: directly attach to the root
        }
        return root;
    }

//     void unionFleets(int fleetId1, int fleetId2) {
//        UnionNode* root1 = find(fleetsTable.findFleet(fleetId1));
//        UnionNode* root2 = find(fleetsTable.findFleet(fleetId2));
//
//        if (root1 == nullptr || root2 == nullptr) {
//            return;
//        }
//
//        if (root1 == root2) {
//            return;
//        }
//
//        // Union by number of pirates in the fleet
//        if (root1->m_fleet->get_number_of_pirates() < root2->m_fleet->get_number_of_pirates()) {
//            root1->m_parent = root2;
//            root1->m_fleet->set_isDeleted(true);
//            root2->m_fleet->updateFleetAttributes(root1->m_fleet->get_number_of_pirates(), root1->m_fleet->get_number_of_ships());
//
//        } else if (root1->m_fleet->get_number_of_pirates() > root2->m_fleet->get_number_of_pirates()) {
//            root2->m_parent = root1;
//            root2->m_fleet->set_isDeleted(true);
//            root1->m_fleet->updateFleetAttributes(root2->m_fleet->get_number_of_pirates(), root2->m_fleet->get_number_of_ships());
//        } else {
//            // If both fleets have the same number of pirates, fleetId1 becomes the parent
//            root2->m_parent = root1;
//            root2->m_fleet->set_isDeleted(true);
//            root1->m_fleet->updateFleetAttributes(root2->m_fleet->get_number_of_pirates(), root2->m_fleet->get_number_of_ships());
//        }
//    }
    void unionFleets(int fleetId1, int fleetId2) {
        UnionNode* root1 = find(fleetsTable.findFleet(fleetId1));
        UnionNode* root2 = find(fleetsTable.findFleet(fleetId2));

        if (root1 == nullptr || root2 == nullptr) {
            return;
        }

        if (root1 == root2) {
            return;
        }

        // Union by number of pirates in the fleet
        if (root1->m_fleet->get_number_of_pirates() < root2->m_fleet->get_number_of_pirates()) {
            root1->m_parent = root2;
            root1->m_fleet->set_isDeleted(true);
            root1->m_fleet->set_setted_rank(root2->m_fleet->get_number_of_pirates());
            root2->m_fleet->updateFleetAttributes(root1->m_fleet->get_number_of_pirates(), root1->m_fleet->get_number_of_ships());
        } else if (root1->m_fleet->get_number_of_pirates() > root2->m_fleet->get_number_of_pirates()) {
            root2->m_parent = root1;
            root2->m_fleet->set_isDeleted(true);
            root2->m_fleet->set_setted_rank(root1->m_fleet->get_number_of_pirates()); // Update setted_rank in the parent node
            root1->m_fleet->updateFleetAttributes(root2->m_fleet->get_number_of_pirates(), root2->m_fleet->get_number_of_ships());

        } else {
            // If both have the same number of pirates, fleetId1 becomes the parent
            root2->m_parent = root1;
            root2->m_fleet->set_isDeleted(true);
            root2->m_fleet->set_setted_rank(root1->m_fleet->get_number_of_pirates()); // Update setted_rank in the parent node
            root1->m_fleet->updateFleetAttributes(root2->m_fleet->get_number_of_pirates(), root2->m_fleet->get_number_of_ships());

        }
    }



    // Add a new fleet to the UnionFind structure
    bool addFleet(int fleetId) {
        Fleet* newFleet = new Fleet(fleetId);
        UnionNode* newNode = new UnionNode(newFleet, nullptr);
        return fleetsTable.insertToTable(newNode);
    }

    // Get the fleet for a given fleetId
    UnionNode* getFleet(int fleetId) {
        return fleetsTable.findFleet(fleetId);
    }
};

#endif // UNIONFIND_H_
