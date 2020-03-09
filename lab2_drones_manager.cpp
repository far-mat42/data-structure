#include "lab2_drones_manager.hpp"
#include <iostream>

// TODO: Implement all of the listed functions below

DronesManager::DronesManager() {
    size = 0;
    first = NULL;
    last = NULL;
}

DronesManager::~DronesManager() {
	DroneRecord* begin = first;
    while (begin) {
        begin = begin -> next;
        delete first;
        first = begin;
    }
	first = last = NULL;
    size = 0;
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
    if (lhs.droneID == rhs.droneID) {
        return true;
    }
    
	return false;
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
	return (size == 0);
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
	if (empty())
	    return DroneRecord(0);
	if (index > size-1)
	    return *last;
	
    DroneRecord* selection = first;
    
    for (int i = 0; i < index; i++) {
        selection = selection->next;
    }
    return *selection;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (empty())
	   return 0;
	DroneRecord* selection = first;
	unsigned int location = 0;
	while (!(*selection == value) && selection->next) {
	    selection = selection->next;
	    location++;
    }
    if (*selection == value)
        return location;
    return size;
}

void DronesManager::print() const {
    DroneRecord* index = first;
    int counter = 1; 
    while(index -> next){
        cout << "Drone ID " << counter << ": " << index->droneID << endl;
        index = index -> next;
        counter++;
    } 
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
	if (empty()) {
	    if (index == 0)
	        return insert_front(value);
        return false;
    }
    else if (index == 0)
        return insert_front(value);
    else if (index >= size)
        return false;
    else if (index == size-1)
        return insert_back(value);
	
    DroneRecord* insertArea = first;
    for (int i = 0; i < index-1; i++) {
        insertArea = insertArea -> next;
    }
    DroneRecord* node = new DroneRecord(value);
    node -> next = insertArea -> next;
    node -> prev = insertArea;
    insertArea -> next -> prev = node;
    insertArea -> next = node;
    size++;
	
    return true;
}

bool DronesManager::insert_front(DroneRecord value) {
    if (empty()) {
        first = new DroneRecord(value);
        last = first;
        size++;
        return true;
    }
    if (size == 1) {
    	DroneRecord* oldFirst = first;
    	first = new DroneRecord(value);
    	first -> next = oldFirst;
    	last = oldFirst;
    	oldFirst -> prev = first;
    	oldFirst -> next = NULL;
    	size++;
    	return true;
	}
    DroneRecord* oldFirst = first;
    first = new DroneRecord(value);
    first -> next = oldFirst;
    oldFirst -> prev = first;
    oldFirst -> next -> prev = oldFirst;
    size++;
    return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	if (empty()) {
	    insert_front(value);
	    return true;
    }
    if (size == 1){
    	last = new DroneRecord(value);
    	last -> prev = first;
    	++size;
		return true;
	}
    DroneRecord* oldLast = last;
    last = new DroneRecord(value);
    last -> prev = oldLast;
    oldLast -> prev -> next = oldLast;
    oldLast -> next = last;
    size++;
    return true;
}

bool DronesManager::remove(unsigned int index) {
	if (empty() || index >= size)
	   return false;
	if (index == 0)
	   return remove_front();
	if (index == size-1)
	   return remove_back();
	
	DroneRecord* removeArea = first;
	for (int i = 0; i < index; i++) {
	    removeArea = removeArea->next;
    }
    removeArea->prev->next = removeArea->next;
    removeArea->next->prev = removeArea->prev;
    delete removeArea;
	
}

bool DronesManager::remove_front() {
	if (empty())
	   return false;
	if (size == 1) {
	    delete first;
	    last = NULL;
	    first = NULL;
	    size--;
	    return true;
    }
    delete first;
    first = first->next;
    first->prev = NULL;
    size--;
    return true;
}

bool DronesManager::remove_back() {
	if (empty())
	   return false;
	if (size == 1)
		return remove_front();
	
	DroneRecord* newLast = last->prev;
	delete last;
	last = newLast;
	last->next = NULL;
	size--;
	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
	if (empty() || index >= size)
	   return false;
	
	if (index == size-1) {
		remove_back();
		return insert_back(value);
	}
	
	remove(index);
	if (index == size)
		return insert_back(value);
	
	return insert(value, index);
	
}

bool DronesManager::reverse_list() {
	if (empty())
	   return false;
	if (size == 1)
	   return true;
	DroneRecord* temp = NULL;
	DroneRecord* current = first;
	DroneRecord* temp2 = first;
	
	while (current){
		temp = current -> prev;
		current -> prev = current -> next;
		current -> next = temp;
		current = current -> prev;
	}
	
    first = temp -> prev;
    last = temp2;
    return true;
}

