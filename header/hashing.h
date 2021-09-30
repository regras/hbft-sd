/*
 * File:   hashing.h
 *
 * Created on 5. Juni 2012, 13:22
 */

#ifndef HASHING_H
#define	HASHING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "bloomfilter.h"
#include "helper.h"
#include "filehash.h"
#endif	/* HASHING_H */

void add_file_hash_to_bf(BLOOMFILTER *, FILE_HASH *);

