
#ifndef __HASHING_H__
#define __HASING_H__
#include <stddef.h> /* size_t */

typedef struct hash_table hash_t;
typedef size_t (*hash_func_t)(const void *data);
typedef int (*act_func_t)(void *data, void *param);

typedef int (*is_match_t)(const void *data1, const void *data2);

/* Returns a hash object on success and NULL on failure */
hash_t *HashCreate(size_t table_size, hash_func_t hash_func, is_match_t match_func);

/* may accept NULL */
void HashDestroy(hash_t *hash);

/* returns the data indexed with KEY if it exists or NULL otherwise */
void *HashSearch(const hash_t *hash, const void *data);

/* returns the data indexed with KEY after removal if it exists or NULL otherwise */
void *HashRemove(hash_t *hash, const void *data);

/* returns 0 on success and 1 on failure */
int HashInsert(hash_t *hash, const void *data);

/* iterates over all the elements and performs ACTION until a non-zero return value is registered or until iteration is complete */
int HashForEach(const hash_t *hash, act_func_t act_func, void *param);

/* returns the number of elements in the hash */
size_t HashSize(const hash_t *hash);

#endif
