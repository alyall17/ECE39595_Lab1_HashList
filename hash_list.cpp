#include "hash_list.h"

// Default constructor: empty list
hash_list::hash_list() {
    head = nullptr;
    size = 0;
    iter_ptr = nullptr;
}

/**-----------------------------------------------------------------------------------
 * START Part 1
 *------------------------------------------------------------------------------------*/

// Insert (key, value) pair into the list or update if key exists
void hash_list::insert(int key, float value) {
    node* current = head;

    while (current != nullptr) {
        if (current->key == key) {
            current->value = value; // Update existing key
            return;
        }
        current = current->next;
    }

    // Key not found, insert new node at the head
    node* newNode = new node{key, value, head};
    head = newNode;
    size++;
}

// Return value for key, or empty optional if key not found
std::optional<float> hash_list::get_value(int key) const { 
    node* current = head;

    while (current != nullptr) {
        if (current->key == key) {
            return current->value; // Key found
        }
        current = current->next;
    }

    return std::nullopt;
}

// Remove node with key, return true if removed, false if not found
bool hash_list::remove(int key) {
    node* current = head;
    node* previous = nullptr;

    while(current != nullptr) {
        if (current->key == key) {
            if (previous == nullptr) {
                head = current->next; // Remove head
            }
            else {
                previous->next = current->next; // Bypass current node
            }
            delete current;
            size--;
            return true; // Key found and removed
        }
        previous = current;
        current = current->next;
    }
    
    return false;
}

//  Return the number of nodes in the list
size_t hash_list::get_size() const {
    return size;
}

hash_list::~hash_list() {
    node* current = head;
    while (current != nullptr) {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    size = 0;
    iter_ptr = nullptr;
}

/**-----------------------------------------------------------------------------------
 * END Part 1
 *------------------------------------------------------------------------------------*/


/**-----------------------------------------------------------------------------------
 * START Part 2
 *------------------------------------------------------------------------------------*/

 // Copy constructor: deep copy from other list
hash_list::hash_list(const hash_list &other) {
    head = nullptr;
    iter_ptr = nullptr;
    size = 0;

    if(!other.head) return; // Other list is empty

    // Copy first node
    head = new node{other.head->key, other.head->value, nullptr};
    node* currentNew = head;
    node* currentOther = other.head->next;

    // Copy rest of the nodes
    while(currentOther != nullptr) {
        currentNew->next = new node{currentOther->key, currentOther->value, nullptr};
        currentNew = currentNew->next;
        currentOther = currentOther->next;
    }

    size = other.size;

    // Copy first node
    /*node* current = other.head;
    node* last = nullptr;

    while (current != nullptr) {
        node* newNode = new node{current->key, current->value, nullptr};
        if (head == nullptr) {
            head = newNode; // First node
        } else {
            last->next = newNode; // Link previous node
        }
        last = newNode;
        current = current->next;
        size++;
    }*/
}

// Assignment operator: clear old list, deep copy from other list
hash_list &hash_list::operator=(const hash_list &other) {
    if (this == &other) return *this; // Self-assignment check

    // Free current nodes
    node* current = head;
    while (current != nullptr) {
        node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    iter_ptr = nullptr;
    size = 0;

    if(!other.head) return *this; // Other list is empty

    // Copy first node
    head = new node{other.head->key, other.head->value, nullptr};
    node* currentNew = head;
    node* currentOther = other.head->next;

    // Copy rest of the nodes
    while(currentOther != nullptr) {
        currentNew->next = new node{currentOther->key, currentOther->value, nullptr};
        currentNew = currentNew->next;
        currentOther = currentOther->next;
    }

    size = other.size;
    return *this;
}

// Reset iterator to the start of the list
void hash_list::reset_iter() {
    iter_ptr = head;
}

// Move iterator to the next node
void hash_list::increment_iter() {
    if (iter_ptr) iter_ptr = iter_ptr->next;
}

// Return current key/value pointers or nullopt if iterator is null
std::optional<std::pair<const int *, float *>> hash_list::get_iter_value() { 
    if(!iter_ptr) return std::nullopt;
    return std::pair<const int*, float*>{&(iter_ptr->key), &(iter_ptr->value)};
}


bool hash_list::iter_at_end() {
    return iter_ptr == nullptr;
}
/**-----------------------------------------------------------------------------------
 * END Part 2
 *------------------------------------------------------------------------------------*/
