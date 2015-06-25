#ifndef RESOURCE_H
#define RESOURCE_H

#include <stddef.h>

struct dict {
	char *key, *value;
	int key_l, val_l;
};

/*
 * Gets a list of dictionaries which contain all key-value pairs
 * in the file defined by file_path.
 * Returns the number of 'struct dict' structures filled.
 */
size_t get_file(const char *file_path, struct dict **dicts);

/*
 * A function (mostly used internally) to create a dictionary with these parameters.
 */
int dict_create(struct dict *d, const char *key, int kl, const char *value, int vl);

/*
 * Frees the data *in* one dictionary entry
 */
int dict_destroy(struct dict *d);

/*
 * Frees all the data and the dictionaries themselves in an array.
 */
int dict_destroy_all(struct dict *d);

/*
 * Searches for 'key' in the array 'dicts', and returns the dict
 * which contains key, or NULL if it is not found.
 */
struct dict * dict_get(const char *key, const struct dict *dicts);
#endif
