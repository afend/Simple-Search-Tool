#ifndef SEARCH_H
#define SEARCH_H
#include "uthash.h"

struct fileRecord {
	char file[124];
	UT_hash_handle hh;
};

struct tokenRecord {
    char token[124];
    UT_hash_handle hh;
    struct fileRecord* files;
}; 

struct saStruct {
	char filename[124];
	UT_hash_handle hh;

void print_disc(char *filename);

void indexer(char* token, char* key);

int sort_by_token(struct tokenRecord *a, struct tokenRecord *b);

void hashsort();

void free_delete();
#endif
