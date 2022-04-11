//
// Created by Ethan Yackulic on 4/8/22.
//

#ifndef HW4_BLAST_DB_H
#define HW4_BLAST_DB_H
#include <iostream>
#include <fstream>
#include <stdlib.h>


#include "FASTAreadset_HT.h"
#include "FASTAreadset_LL.h"

class BLAST_DB {
private:
    FASTAreadset_LL query_stack;
    int array_size =10;
    int ** score_matrix = nullptr;
public:
    char * query;
    FASTAreadset_HT * hashtable;
    BLAST_DB();
    //custom constructor
    BLAST_DB(const char *filename, int m, int seq_size);

    ~BLAST_DB();
    void splitQuery(int seq_size, int query_size, const char * subset);
    int NW(const char * seq1,const char * seq2, int array_size);
    void print_score_matrix(int array_size, int** score_matrix);
    int ScoreFinder(int i, int j,const char * seq1, const char * seq2, int array_size,int **score_matrix);


        };


#endif //HW4_BLAST_DB_H
