#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager ourManager;
		ASSERT_TRUE(ourManager.get_size() == 0)
		ASSERT_TRUE(ourManager.empty() == true)
		ASSERT_TRUE(ourManager.first == NULL)
		ASSERT_TRUE(ourManager.last == NULL)
		
		return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))
		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
	    DronesManager manager, emptyManager;
	    manager.insert_front(DronesManager::DroneRecord(5));
	    manager.insert_front(DronesManager::DroneRecord(4));
	    manager.insert_front(DronesManager::DroneRecord(3));
	    manager.insert_front(DronesManager::DroneRecord(2));
	    manager.insert_front(DronesManager::DroneRecord(1));
	    
	    ASSERT_TRUE(manager.select(0).droneID == 1 && manager.select(5).droneID == 5 && manager.select(4).droneID == 5
                    && manager.select(2).droneID == 3 && emptyManager.select(100).droneID == 0)
        
        DronesManager::DroneRecord rec1 = DronesManager::DroneRecord(10);
        DronesManager::DroneRecord rec2 = DronesManager::DroneRecord(20);
        
        ASSERT_TRUE(manager.search(manager.select(0)) == 0 && manager.search(rec1) == 5 && manager.search(rec2) == 5 
                    && emptyManager.search(rec1) == 0);
	    
	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
	    DronesManager manager1, manager2;
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    manager2.insert_front(DronesManager::DroneRecord(2));
	    
	    ASSERT_TRUE(manager1.remove_front());
	    ASSERT_TRUE(manager2.remove_back());
	    
	    ASSERT_TRUE(manager1.empty() && manager1.first==NULL && manager1.last==NULL);
	    ASSERT_TRUE(manager2.empty() && manager2.first==NULL && manager2.last==NULL);
	    
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
	    DronesManager manager1, manager2, emptyManager;
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    manager1.insert_front(DronesManager::DroneRecord(2));
	    manager1.insert_front(DronesManager::DroneRecord(3));
	    manager1.insert_front(DronesManager::DroneRecord(4));
	    manager2.insert_front(DronesManager::DroneRecord(10));
	    
	    ASSERT_TRUE(manager1.reverse_list());
	    
	    ASSERT_TRUE(manager1.select(0).droneID == 1 && 
					manager1.select(1).droneID == 2 && 
					manager1.select(2).droneID == 3 && 
					manager1.select(3).droneID == 4);
	    
	    ASSERT_TRUE(manager2.reverse_list());
	    ASSERT_TRUE(manager2.select(0).droneID==10);
	    ASSERT_TRUE(!(emptyManager.reverse_list()));
	    ASSERT_TRUE(!(emptyManager.replace(1,manager1.select(0))));
	    ASSERT_FALSE(manager2.replace(10,manager1.select(0)));
	    ASSERT_TRUE(manager1.replace(3,manager2.select(0)));
		ASSERT_TRUE(manager1.select(3).droneID==10);
	    
	    return true;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
	    DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(5));
	    manager1.insert_front(DronesManager::DroneRecord(10));
	    
	    ASSERT_TRUE(manager1.select(1).droneID==5);
	    
	    manager1.insert_front(DronesManager::DroneRecord(200));
	    ASSERT_TRUE(manager1.select(2).droneID==5 && manager1.select(1).droneID==10);
	    
	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
	    DronesManager manager1, emptyManager;
	    manager1.insert_front(DronesManager::DroneRecord(4));
	    manager1.insert_front(DronesManager::DroneRecord(3));
	    manager1.insert_front(DronesManager::DroneRecord(2));
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    
	    DronesManager::DroneRecord d1 = DronesManager::DroneRecord(5);
	    
	    ASSERT_TRUE(!(emptyManager.insert(manager1.select(0),10)));
	    ASSERT_TRUE(!(manager1.insert(manager1.select(0),10)));
	    
	    ASSERT_TRUE(emptyManager.insert(d1,0) && emptyManager.select(0).droneID==5);
	    
	    ASSERT_TRUE(manager1.insert(manager1.select(0),2) && manager1.select(2).droneID==1 && *(manager1.select(1).next)==manager1.select(2) 
                    && *(manager1.select(3).prev)==manager1.select(2) && *(manager1.select(2).next)==manager1.select(3) 
                    && *(manager1.select(2).prev)==manager1.select(1));
        
	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
	    DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    ASSERT_TRUE(manager1.remove_front() && !(manager1.remove_front()));
	    ASSERT_TRUE(manager1.insert_front(DronesManager::DroneRecord(17)));
		ASSERT_TRUE(manager1.insert_back(DronesManager::DroneRecord(16)));
	    
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager1, emptyManager;
	    manager1.insert_front(DronesManager::DroneRecord(4));
	    manager1.insert_front(DronesManager::DroneRecord(3));
	    manager1.insert_front(DronesManager::DroneRecord(2));
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    
	    DronesManager::DroneRecord d1 = DronesManager::DroneRecord(5);
		
		ASSERT_TRUE(!(emptyManager.insert(manager1.select(0),10)));
	    ASSERT_TRUE(!(manager1.insert(manager1.select(0),10)));
	    
	    ASSERT_TRUE(emptyManager.insert(d1,0) && emptyManager.select(0).droneID==5);
	    
	    ASSERT_TRUE(manager1.insert(manager1.select(0),2) && manager1.select(2).droneID==1 && *(manager1.select(1).next)==manager1.select(2) 
                    && *(manager1.select(3).prev)==manager1.select(2) && *(manager1.select(2).next)==manager1.select(3) 
                    && *(manager1.select(2).prev)==manager1.select(1));
        
        ASSERT_TRUE(!(emptyManager.remove(1)) && !(manager1.remove(1254)));
        
        ASSERT_TRUE(manager1.remove(1) && manager1.select(1).droneID==1 && *(manager1.select(0).next)==manager1.select(1)
                    && *(manager1.select(1).prev)==manager1.select(0));
		
		return true;
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
		DronesManager manager1;
	    manager1.insert_front(DronesManager::DroneRecord(4));
	    manager1.insert_front(DronesManager::DroneRecord(3));
	    manager1.insert_front(DronesManager::DroneRecord(2));
	    manager1.insert_front(DronesManager::DroneRecord(1));
	    
	    ASSERT_TRUE(manager1.insert(manager1.select(0),2) && manager1.select(2).droneID==1 && *(manager1.select(1).next)==manager1.select(2) 
                    && *(manager1.select(3).prev)==manager1.select(2) && *(manager1.select(2).next)==manager1.select(3) 
                    && *(manager1.select(2).prev)==manager1.select(1));
		ASSERT_TRUE(manager1.insert(manager1.select(4),1) && manager1.select(1).droneID==4 && *(manager1.select(0).next)==manager1.select(1) 
                    && *(manager1.select(2).prev)==manager1.select(1) && *(manager1.select(1).next)==manager1.select(2) 
                    && *(manager1.select(1).prev)==manager1.select(0));
        
        ASSERT_TRUE(manager1.reverse_list());
        
        return true;
	} 
};

#endif
