#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/resource.h"

size_t get_file(const char *file_path, struct dict **dicts)
{
	char *token, buffer[1024];
	size_t size = 0, alloc = 1;
	struct dict *d = malloc(sizeof(struct dict));
	FILE *f = fopen(file_path, "r");
	while (fgets(buffer, sizeof(buffer), f) != NULL) {
		if ((token = strchr(buffer, '#')) != NULL)
			*token = '\0';
		if ((token = strchr(buffer, '=')) == NULL)
			continue;
		if (size == alloc) {
			alloc *= 2;
			d = realloc(d, alloc * sizeof(struct dict));
		}
		*token++ = '\0';
		while (*token == ' ' || *token == '\t')
			token++;
		dict_create(d + size++, buffer, strlen(buffer), token, strlen(token));
	}
	fclose(f);
	return size;
}
int dict_create(struct dict *d, const char *key, int kl, const char *value, int vl)
{
	d->key = malloc(kl + 1);
	d->value = malloc(vl + 1);
	d->val_l = vl;
	d->key_l = kl;
	memcpy(d->key, key, kl + 1);
	memcpy(d->value, value, vl + 1);
	return (d != NULL) - 1;
}
int dict_destroy(struct dict *d)
{
	free(d->key);
	free(d->value);
	return 0;
}
int dict_destroy_all(struct dict *p)
{
	while (p) {
		if (p->key)
			free(p->key);
		if (p->value)
			free(p->value);
		free(p);
		p++;
	}
	return 0;
}

struct dict *dict_get(const char *key, const struct dict *dicts)
{
	struct dict *d = dicts;
	while (d) {
		if (!strstr(d->key, key))
			return d;
		d++;
	}
	return NULL;

}
long get_data(const char *file_path, char **data)
{
	char buffer[256];
	FILE *f = fopen(file_path, "r");
	long len;
	if (f == NULL)
		return -1;
	fseek(f, 0, SEEK_END);
	length = ftell(f);
	fseek(f, 0, SEEK_SET);
	*data = malloc(len);
	fread(*data, 1, len, f);
	fclose(f);
	return len;
}
