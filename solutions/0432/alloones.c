// Problem 432 - All O`one Data Structure
// https://leetcode.com/problems/all-oone-data-structure/

/*
    It took me a couple of days to get this right, but I am glad that it is
    working and it is one of the few accepted C solutions for this problem!
*/

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define MAX_KEY_SIZE (15)
#define INITIAL_TABLE_SIZE (16384)

// Doubly linked list of keys for keeping track of the min and max counts
typedef struct KeyList
{
    struct KeyData* data;       // Pointer to the key's entry on the hash table
    struct KeyList* next;       // Next element on the list
    struct KeyList* prev;       // Previous element on the list
} KeyList;

// Entry for the hash table that stores the key counts
typedef struct KeyData
{
    char key[MAX_KEY_SIZE+1];   // Key string (if the first byte is zero, this entry is considered empty)
    uint64_t count;             // Value (count)
    uint64_t hash;              // Hashed key
    struct KeyList* list;       // Pointer to this key's position on the linked list
    struct KeyData* next;       // Pointer to the next entry in the same bucket of the table
} KeyData;

// Hash table with the key counts
typedef struct KeyTable
{
    uint64_t used;      // Amount of keys stored
    uint64_t capacity;  // Maximum amount of keys that the table can store
    KeyData* data;      // Pointer to the first bucket of the table
} KeyTable;

typedef struct KeyCache {
    char key[MAX_KEY_SIZE+1];
    KeyData* data;
} KeyCache;

typedef struct {
    struct KeyList* min;    // Head of the linked list (minimum count)
    struct KeyList* max;    // Tail of the linked list (maximum count)
    KeyCache last_inc;
    KeyCache last_dec;
    struct KeyTable* table; // Hash table for the key counts
} AllOne;

// Hash a string (algorithm: FNV-1a)
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function#FNV-1a_hash
static uint64_t hash(char* str)
{
    static const uint64_t FNV_prime = 0x100000001b3;
    static const uint64_t offset_basis = 0xcbf29ce484222325;

    uint64_t hash_val = offset_basis;
    uint64_t my_char = 0;
    while (my_char = *str++)
    {
        hash_val ^= my_char;
        hash_val *= FNV_prime;
    }
    
    return hash_val;
}

// Add a new element to the front of the list in the AllOne object
static void list_push(AllOne* obj, KeyData* data)
{
    // Create the new entry on the list
    KeyList* new_node = malloc(sizeof(*new_node));
    *new_node = (KeyList){
        .data = data,
        .next = obj->min,
        .prev = NULL,
    };
    data->list = new_node;

    // Update the pointers to the head and tail of the list
    if (obj->min) obj->min->prev = new_node;
    if (!obj->max) obj->max = new_node;
    obj->min = new_node;
}

// Remove the given element from the list in the AllOne object
static void list_pop(AllOne* obj, KeyList* node)
{
    // Link the previous and next elements to each other
    if (node->next) node->next->prev = node->prev;
    if (node->prev) node->prev->next = node->next;

    // Update the head and tail of the list, in case we are removing them
    if (obj->min == node) obj->min = node->next;
    if (obj->max == node) obj->max = node->prev;

    // Delete the element
    free(node);
}


// Swap two adjascent elements of a doubly linked list
static void list_swap_neighbors(AllOne* obj, KeyList* node1, KeyList* node2)
{
    // Ensure that 'node1' comes before 'node2'
    if (node2->next == node1)
    {
        KeyList* temp = node1;
        node1 = node2;
        node2 = temp;
    }
    
    // Remember the original pointers
    KeyList *const node1_prev = node1->prev;
    KeyList *const node1_next = node1->next;
    KeyList *const node2_prev = node2->prev;
    KeyList *const node2_next = node2->next;

    // Swap the positions of the elements
    node1->prev = node2;
    node1->next = node2_next;
    node2->prev = node1_prev;
    node2->next = node1;

    // Update the links of the elements around to the swapped elements
    if (node1->prev) node1->prev->next = node1;
    if (node1->next) node1->next->prev = node1;
    if (node2->prev) node2->prev->next = node2;
    if (node2->next) node2->next->prev = node2;

    // Update the head and tail of the list, if needed
    if (obj->min == node1) obj->min = node2;
    if (obj->max == node2) obj->max = node1;
}

// Move a list's element foward until its value is greater or equal than the next element's value
static void list_move_up(AllOne* obj, KeyList* node)
{
    // Do nothing if the list has only one element
    if (obj->max == obj->min) return;
    
    // Keep swapping the element with the next until the next value is not smaller
    while (node->next && node->next->data->count < node->data->count)
    {
        list_swap_neighbors(obj,node, node->next);
    }
}

// Move a list's element backward until its value is less or equal than the previous element's value
static void list_move_down(AllOne* obj, KeyList* node)
{
    // Do nothing if the list has only one element
    if (obj->max == obj->min) return;

    // Keep swapping the element with the previous until the previous value is not bigger
    while (node->prev && node->prev->data->count > node->data->count)
    {
        list_swap_neighbors(obj, node->prev, node);
    }
}

// Change the capacity of the hash table
static void table_resize(KeyTable* table, uint64_t new_size)
{
    if (new_size < INITIAL_TABLE_SIZE) return;
    
    // Old and new arrays for the data section of the hash table
    KeyData* old_data = table->data;
    KeyData* new_data = calloc(new_size, sizeof(*new_data));

    if (new_data)
    {
        // Update the capacity and point to the new data section
        table->capacity = new_size;
        table->data = new_data;
    }
    else
    {
        return;
    }
    
    bool is_first = true;       // First element of the linked list on each bucket of the old hash table
    uint64_t i = 0;             // Index on the old hash table
    KeyData* old_slot = NULL;   // An entry on the old hash table

    // Loop through all slots in the old table
    // and copy the elements from the old table to the new
    while (i < table->capacity)
    {
        // Check if there is a key stored in the current slot
        if (is_first)
        {
            old_slot = &old_data[i];
            if (!old_slot->key[0]) continue;
        }

        // Find the key's position on the new table
        const uint64_t new_i =  old_slot->hash % new_size;
        KeyData *new_slot = &new_data[new_i];
        while (new_slot->key[0] != 0)
        {
            if (!new_slot->next)
            {
                new_slot->next = calloc(1, sizeof(new_slot->next));
            }
            new_slot = new_slot->next;
        }
        
        // Copy the data to the new table and update the list to point to the new position
        memcpy(new_slot, old_slot, sizeof(old_slot));
        old_slot->list->data = new_slot;

        KeyData* next = old_slot->next; // Next element on the list
        if (!is_first) free(old_slot);  // Free the element's memory if it's not the first element of the list

        // Check if there are more items stored in the current bucket of the old table
        if (next)
        {
            // Move to the next element on the current bucket
            is_first = false;
            old_slot = next;
        }
        else // Last element on the linked list (old_slot->next == NULL)
        {
            // Move to the next bucket on the old table
            is_first = true;
            i++;
            continue;
        }
    }

    // Free the memory of the old table
    free(old_data);
}

AllOne* allOneCreate()
{
    // Create the hash table
    KeyData* counts = calloc(INITIAL_TABLE_SIZE, sizeof(*counts));
    KeyTable* table = malloc(sizeof(*table));
    *table = (KeyTable){
        .used = 0,
        .capacity = INITIAL_TABLE_SIZE,
        .data = counts,
    };
    
    // Create the main container and add the hash table to it
    AllOne* obj = malloc(sizeof(*obj));
    *obj = (AllOne){
        .min = NULL,
        .max = NULL,
        .last_inc = {.key = {0}, .data = NULL},
        .last_dec = {.key = {0}, .data = NULL},
        .table = table,
    };

    return obj;
}

void allOneInc(AllOne* obj, char* key)
{
    KeyData* slot = NULL;
    int compare = -1;
    uint64_t hash_val = 0;
    bool is_first = true;   // First element of the linked list on the table's bucket
    bool cache_hit = false; // If the searched key is cached
    
    if ( (compare = strncmp(key, obj->last_inc.key, MAX_KEY_SIZE)) == 0 )
    {
        // Avoid searching for the key if the same key is being incremented again
        slot = obj->last_inc.data;
        cache_hit = true;
    }
    else
    {
        // Find the key's bucket on the hash table
        hash_val = hash(key);
        const uint64_t pos = hash_val % obj->table->capacity;
        slot = &obj->table->data[pos];

        // Search for the key on the bucket
        while (
            ((compare = strncmp(key, slot->key, MAX_KEY_SIZE)) != 0)
            && slot->next
        )
        {
            slot = slot->next;
            is_first = false;
        }
    }

    if (compare == 0) // Key was found
    {
        // Increment the key's count and update its position on the list of min and max values
        slot->count += 1;
        if (obj->max != slot->list) list_move_up(obj, slot->list);
    }
    else // Key was not found
    {
        obj->table->used += 1;
        if (obj->table->used >= obj->table->capacity)
        {
            // Double the capacity of the hash table when at max capacity
            table_resize(obj->table, obj->table->capacity * 2);
        }
        
        // Check if a collision happened
        if (!is_first || slot->key[0] != 0)
        {
            // Add the new key to the linked list on the current position of the table
            KeyData* new_slot = calloc(1, sizeof(*new_slot));
            slot->next = new_slot;
            slot = slot->next;
        }
        
        // Store the key on the table
        strncpy(slot->key, key, MAX_KEY_SIZE);
        slot->count = 1;
        slot->hash = hash_val;

        // Add the key to the list of min and max values
        list_push(obj, slot);
    }

    // Cache the last searched key
    if (!cache_hit)
    {
        strncpy(obj->last_inc.key, slot->key, MAX_KEY_SIZE);
        obj->last_inc.data = slot;
    }
}

void allOneDec(AllOne* obj, char* key)
{
    KeyData* slot = NULL;
    KeyData* previous_slot = NULL;
    int compare = -1;
    bool is_first = true;   // First element of the linked list on the table's bucket
    bool cache_hit = false; // If the searched key is cached
    
    if ( (compare = strncmp(key, obj->last_dec.key, MAX_KEY_SIZE)) == 0 )
    {
        // Avoid searching for the key if the same key is being incremented again
        slot = obj->last_dec.data;
        cache_hit = true;
    }
    else
    {
        // Find the key's bucket on the hash table
        const uint64_t pos = hash(key) % obj->table->capacity;
        slot = &obj->table->data[pos];

        // Search for the key on the bucket
        // Note: the problem ensures that the key exists when this function is called
        while (compare = strncmp(key, slot->key, MAX_KEY_SIZE) != 0)
        {
            previous_slot = slot;
            if (!slot->next) return;
            slot = slot->next;
            is_first = false;
        }
    }

    if (compare != 0) return;
    
    // Decrement the key's count and remove the key if its count reaches zero
    slot->count -= 1;
    if (slot->count == 0)
    {
        // Remove the key from the list of min and max values
        list_pop(obj, slot->list);

        // Remove from the key from the caches
        if (cache_hit) obj->last_dec.key[0] = 0;
        if ((strncmp(key, obj->last_inc.key, MAX_KEY_SIZE)) == 0)
        {
            obj->last_inc.key[0] = 0;
        }
        
        if (is_first) // The key is stored directly on the table
        {
            if (slot->next)
            {
                // If there's another key on the bucket, copy that other key to the table
                KeyData* next_slot = slot->next;
                *slot = *next_slot;
                free(next_slot);    // Free the old memory of the other key
            }
            else
            {
                // If this is the only key on the bucket, just mark the bucket as "unused"
                slot->key[0] = 0;
            }
        }
        else // // The key is NOT stored directly on the table
        {
            // Link the previous key to the next, then remove the old key
            previous_slot->next = slot->next;
            free(slot);
        }
    }
    else // if (slot->count > 0)
    {
        // Update the key's position on the list of min and max values
        if (obj->min != slot->list) list_move_down(obj, slot->list);
    }

    // Cache the last searched key
    if (!cache_hit)
    {
        strncpy(obj->last_dec.key, slot->key, MAX_KEY_SIZE);
        obj->last_dec.data = slot;
    }
}

char* allOneGetMaxKey(AllOne* obj)
{
    if (obj->max)
    {
        return obj->max->data->key;
    }
    else
    {
        return "";
    }
}

char* allOneGetMinKey(AllOne* obj)
{
    if (obj->min)
    {
        return obj->min->data->key;
    }
    else
    {
        return "";
    }
}

void allOneFree(AllOne* obj)
{
    // Free the hash table
    for (size_t i = 0; i < obj->table->capacity; i++)
    {
        KeyData* node = obj->table->data[i].next;
        while (node)
        {
            KeyData* next_node = node->next;
            free(node);
            node = next_node;
        }
    }
    free(obj->table->data);
    free(obj->table);

    // Free the list of min and max values
    while (obj->min)
    {
        KeyList* next = obj->min->next;
        free(obj->min);
        obj->min = next;
    }
    
    // Free the main container
    free(obj);
}

/**
 * Your AllOne struct will be instantiated and called as such:
 * AllOne* obj = allOneCreate();
 * allOneInc(obj, key);
 
 * allOneDec(obj, key);
 
 * char* param_3 = allOneGetMaxKey(obj);
 
 * char* param_4 = allOneGetMinKey(obj);
 
 * allOneFree(obj);
*/