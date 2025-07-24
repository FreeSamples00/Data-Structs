# Data Structures in C

This is a repo for my implementations of various data structures i’ve encountered during my studies. They are not used anywhere, I just found it a fun challenge to implement in C.



## Linked Hash Table

A hash table that stores key-value records

- **key**: a string (`char*`)
- **value**: an `int`



Hash collisions are handled with a linked list in each bucket.

When a duplicate key is set, the value is replaced.

### Methods

- `dict* HT_init(void)`
    - initializes a hash table
- `void HT_set(dict* ht, char* key, int value)`
    - inserts a record with key and value
- `void HT_remove(dict* ht, char* key)`
    - removes a record with passed key
- `int HT_get(dict* ht, char* key)`
    - finds and returns the value of requested record
- `int HT_contains(dict* ht, char* key)`
    - returns a boolean on if the record is present
- `node** HT_getpairs(dict* ht)`
    - returns a null terminated array of all records in hash table
- `void HT_free(dict* ht)`
    - frees hash table and all records within


## Skip List *planned*

A skip list with a variable number of express lists.

Added nodes are elevated to express nodes based on random chance.

Duplicate keys are replaced



### Methods

…
