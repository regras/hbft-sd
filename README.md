# Repository Organization

This repository contains two branches:
- The main, which contains the original `HBFT-SD` implmentation.
- The `NCF-HBFT-SD` implementation, which is removes common blocks.

# HBFT-SD
This tool is an adaptation of `MRSH-HBFT`, a similarity search tool based on `MRSH-V2`. This implementation changes the feature extraction tool, which originally is `MRSH-V2`, to `sdhash`, aiming to improve its performance.

## Relevant Publications
```
- D. Lillis, F. Breitinger, M. Scanlon, Expediting MRSH-v2 Approximate Matching with Hierarchical Bloom Filter Trees. In: Matoušek P., Schmiedecker M. (eds) Digital Forensics and Cyber Crime. ICDF2C 2017. Lecture Notes of the Institute for Computer Sciences, Social Informatics and Telecommunications Engineer- ing, vol 216. Springer, Cham, 2018 (doi: [10.1007/978-3-319-73697-6_11](https://dx.doi.org/10.1007/978-3-319-73697-6_11)).

- D. Lillis, F. Breitinger and M. Scanlon. Hierarchical Bloom Filter Trees for Approximate Matching. Journal of Digital Forensics, Security and Law (JDFSL), 13(1), 2018.

- Velho, J. P. B., Moia, V. H. G., and Henriques, M. A. A. (2020). Entendendo e melhorando a capacidade de detecçao de estrategias de busca de similaridade em investigações forenses. XX Brazilian Symposium on information and computational systems security, Brazilian Computer Society (SB).
```
## Instructions

### Dependencies
- Boost
- OpenSSL (for sha1 hash)
- CMake

#### Boost
1. Extract the library folder onto `HBFT-SD`'s main folder
 
2. Inside boost folder Run:
```
$ ./bootstrap.sh --prefix = /usr/local/  
$ ./b2 install
```
3. The setup is complete!


### Compile and run:
1.  Makefile:
```  
$ cmake .
$ make
```
2. Run:
```  
$ ./hbft_sd
```

### Configs
There are four main parameters to configurate:

- The directory/file used to populate the tree: 
    File ./src/main.c
    ```
    char *tree_dirname = "<directory_or_file_path>";
    ```
- The directory/file the user wants to search in the tree:
   File ./src/main.c
   ```
   char *search_dirname = "./src/helper.c";
   ```
- The number of leaves used on the tree
   File ./src/main.c
   ```
   int leaf_num = <number>;
   ```
- Minimal number of consecutive features to consider a match:
  File ./src/main.c
  ```
  mode->min_run = <number>;
  ```
  File ./header/config.h
  ```
  #define MIN_RUN <number>
  ```
- The Root Bloom Filter Size:
  File ./header/config.h
  ```
  #define BF_SIZE <number>
  ```
 
  
 ### Observations
 - The original implementation used a memory threshold given by the user to calculate the root Bloom filter size. This implementation uses the size configured on `BF_SIZE`  (`config.h` file), which is enable by the `#define NEW_SIZE`. If `NEW_SIZE` is not enabled, the tool will use the memory threshold defined at `main.c` file with `unsigned long mem_upper_limit` variable, however this funcionality was not tested on `HBFT-SD` so be careful.
 - Originally, `MRSH-HBFT`, allowed multiple files inserted on a single leaf node, `HBFT-SD` allows only one file per leaf node. This was implemented aiming to improve the tool's performance.
 - Enable `#define LOGGING` (`config.h`) to print debbuging information when using this tool.
 
