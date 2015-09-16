#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "uthash.h"
#include <errno.h> 
#include "search.h"

#define BUFFER_SIZE 2048

struct tokenRecord *indexs = NULL;
FILE *fp;

int sort_by_token(struct tokenRecord *a, struct tokenRecord *b) {
  return strcmp(a->token,b->token);
}

void hashsort() {
    HASH_SORT(indexs, sort_by_token);
}

void print_disc(char *filename) {
		struct tokenRecord *t;
		struct fileRecord *p;
		fp = fopen(filename, "w+");
		for(t=indexs; t != NULL; t=(struct tokenRecord*)(t->hh.next)) {
			int i = 0;
			fprintf(fp, "%s\n", t->token);
			for(p=t->files; p != NULL; p=(struct fileRecord*)(p->hh.next)) {	
				fprintf(fp, "%s\n", p->file);
				i++;
				if(i % 5 == 0)
					fprintf(fp, "\n");
			}
		}
		fclose(fp);
}

void indexer(char* token, char* key) {
	struct tokenRecord *s;
	struct fileRecord *f;
	
	HASH_FIND_STR(indexs, key, s);
	if(!s) { 
		s = (struct tokenRecord*)malloc(sizeof(struct tokenRecord));
		strncpy(s->token, key, 124);
		HASH_ADD_STR(indexs, token, s); 
		s->files = NULL;
	} 
	
	HASH_FIND_STR(s->files, token, f);
	if(!f)
	{
		f = (struct fileRecord*)malloc(sizeof(struct fileRecord));
		strncpy(f->file, token, 124);
		HASH_ADD_STR(s->files, file, f); 
	}

}

void free_delete() {
  struct tokenRecord *tmp, *user;
  HASH_ITER(hh, indexs, user, tmp) {
    HASH_DEL(indexs,user); /* delete it (users advances to next) */
    free(user);            /* free it */
  }
}



