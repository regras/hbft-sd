#include "../header/hashing.h"
#include "../header/config.h"
#include "../header/helper.h"
#include "../header/bloomfilter.h"
#include "../header/filehash.h"
#include <stdio.h>
#include <math.h>
//extern "C" void add_hash_to_bloomfilter(BLOOMFILTER *bf, uint256 hash_val)

void add_file_hash_to_bf(BLOOMFILTER *bf, FILE_HASH *fh) {
    HASH_ENTRY *he = fh->first_hash;

    while ( he != NULL ) {
      //printf("No add file::");
        //for(int i = 0; i < 5; i++)printf("%X",(he->value)[i]);
        //printf("\n");
        add_hash_to_bloomfilter(bf, (he->value));
        he = he->next_entry;
    }
    bf->number_of_files++;
    bf->bytes += fh->filesize;
}

