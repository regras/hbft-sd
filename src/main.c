//
// Created by David Lillis on 08/09/2016.
//

#include "../header/bloomfilter.h"
#include "../header/bloomfiltertree.h"
#include "../header/helper.h"
#include "../header/hashing.h"
#include "../header/fingerprintList.h"
#include "../header/fingerprint.h"
#include "../header/config.h"
#include <unistd.h> // change: adicionei para não dar conflito com o getcwd, cuidado
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <math.h>
MODES *mode; // chamando novamente a variável global declarada em config.h

static void initalizeDefaultModes(int block_size, int min_run){
	mode = malloc(sizeof(MODES));
  mode->block_size = block_size;
  mode->min_run = min_run;
}

/*
CHANGE: Acrescentei a variável global mode para o resto dos arquivos terem acesso, retirando o antigo arquivo main, essa variável sumia!
Além disto, coloquei também as declarações de block_size e min_run em uma função, teoricamente não muda nada.
A variável global não estava sendo alterada então coloquei um define pra isso
*/


int main(int argc, char *argv[]){
  	mode = malloc(sizeof(MODES));


    //char *tree_dirname = "../../../Databases/cb_known_set";
    //char *search_dirname = "../../../Databases/cb_target_set";
    char *tree_dirname = "./src/helper.c";
    char *search_dirname = "./src/helper.c";

    // 4: leaves
    int leaf_num = 16;
    mode->min_run = 6;
    mode->block_size = 64;
    unsigned long mem_upper_limit = 1024ul * 1024ul * 1024ul * 2; // default to 10GiB

// Change: para o novo tamanho de filtro com base no tamanho da base
#ifdef NEW_SIZE
    unsigned long filter_size = BF_SIZE;
    unsigned long root_bf_size = (unsigned long) pow(2, (unsigned long) log2(filter_size));
    BLOOMFILTER_TREE *tree = init_variable_bf_tree(leaf_num, root_bf_size);
#else

#ifdef FIXED_TREE
    unsigned long max_mem = mem_upper_limit / (leaf_num * 2 - 1);
    unsigned long root_bf_size = (unsigned long) pow(2, (unsigned long) log2(max_mem));
    BLOOMFILTER_TREE *tree = init_fixed_bf_tree(leaf_num, root_bf_size);
    mode->fixed = true;
#else
    unsigned long max_mem = mem_upper_limit / ( log2(leaf_num) + 1 );
    unsigned long root_bf_size = (unsigned long) pow(2, (unsigned long) log2(max_mem));
		//    if ( root_bf_size > MAX_BF_SIZE_IN_BYTES )
		//        root_bf_size = MAX_BF_SIZE_IN_BYTES;
    BLOOMFILTER_TREE *tree = init_variable_bf_tree(leaf_num, root_bf_size);
#endif
#endif

#ifdef LOGGING
    printf("Upper memory limit: %lu\n", mem_upper_limit);
    printf("Config BLOCK_SIZE %d\nConfig MIN_RUN %d\nConfig LEAF_NUM %d\nConfig BF_SIZE %lu\nConfig FIXED %s\n", mode->block_size, mode->min_run, leaf_num, root_bf_size, mode->fixed ? "true" : "false");
    // start timing
    clock_t build_tic = clock();
#endif

    add_path_to_bf_tree(tree, tree_dirname);

#ifdef FIXED_TREE
    build_bf_tree(tree);
#endif

#ifdef LOGGING
    clock_t build_toc = clock();
    for ( int i = 1; i < tree->size; i++ ) {
        printf("Fullness %d %f\n", i, fullness(tree->data[i]));
        printf("Files %d (%lu bytes)\n", tree->data[i]->number_of_files, tree->data[i]->bytes);
    }
    clock_t search_tic = clock();
#endif

    search_path_in_bf_tree(tree, search_dirname);

#ifdef LOGGING
    clock_t search_toc = clock();
    printf("Build Time: %f seconds\nSearch Time: %f seconds\n", (double) (build_toc - build_tic) / CLOCKS_PER_SEC,(double) (search_toc - search_tic) / CLOCKS_PER_SEC);
#endif

    destroy_bf_tree(tree);
    return 0;
}
