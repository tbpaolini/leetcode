/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

// FNV-1a hash function
uint64_t hash(const uint8_t *data, size_t size){
    uint64_t my_hash = 0xcbf29ce484222325;
    size_t pos = 0;
    while (pos < size){
        my_hash ^= data[pos++];
        my_hash *= 0x00000100000001B3;
    }
    return my_hash;
}

// Hash an integer value
uint64_t hash_int(int n){
    const uint8_t *bytes = (uint8_t*)(&n);
    return hash(bytes, sizeof(int));
}

// An entry of the hash table (key/value pair)
typedef struct TableNode {
    int key;
    int val;
    bool used;  // If there is an entry stored here
} TableNode;

// The hash table
typedef struct HashTable {
    size_t size;
    size_t max_size;
    struct TableNode data[];
} HashTable;

// Add a key/value pair to the hash table
bool ht_add(HashTable *table, int key, int val){
    
    if (table->size >= table->max_size) return false;
    
    // Get the tentative index
    size_t i = hash_int(key) % table->max_size;
    
    // Look for the next expty spot, or a spot with the same key
    while(table->data[i].used && table->data[i].key != key){
        i++;
        if (i == table->max_size) i = 0;
    }
    
    // Add the entry
    table->data[i] = (struct TableNode){key, val, true};
    table->size++;
    
    return true;
}

// Retrieve the value from a key on the hash table
bool ht_get(HashTable *table, int key, int *val){
    
    // Get the tentative index
    size_t i = hash_int(key) % table->max_size;
    
    // Search for the key or an empty spot
    while(table->data[i].used && table->data[i].key != key){
        i++;
        if (i == table->max_size) i = 0;
    }
    
    if (!table->data[i].used || table->data[i].key != key){
        // Key not found
        return false;
    }
    else {
        // Key found
        *val = table->data[i].val;
        return true;
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize){
    
    // Allocate the hash table and the output array
    HashTable *table = calloc(1, sizeof(HashTable) + (sizeof(TableNode) * 20000));
    table->max_size = 20000;
    int *array = malloc(sizeof(int) * 2);
    
    // Iterate over the input array
    for (size_t i = 0; i < numsSize; i++){
        
        // Current value
        const int num = nums[i];
        
        // The complement of the current value
        const int comp = target - num;
        
        // Check if the complement is on the hash table
        int j;
        if (ht_get(table, comp, &j) && i != j){
            // Return the indexes of the values whose the sum is the target value
            array[0] = i;
            array[1] = j;
            *returnSize = 2;
            free(table);
            return array;
        }
        
        // Add the current value with its index to the hash table
        ht_add(table, num, i);
    }
    
    // When it failed to find the values
    *returnSize = 0;
    free(table);
    return NULL;
}