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

struct prettyAlign{
    char * seq1;
    char * seq2;
    char * seq3;
};



class BLAST_DB {
private:
    FASTAreadset_LL * query_queue;
    int ** score_matrix = nullptr;
    char ** query_array;
    int num_of_lines_read;
public:
    char * query;
    FASTAreadset_HT * hashtable;
    BLAST_DB();
    //custom constructor
    BLAST_DB(const char *filename, int m, int seq_size);

    ~BLAST_DB();
    const char* splitQuery(int seed_size, int query_size, float p);
    int NW(const char * seq1,const char * seq2, int array_size);
    void print_score_matrix(int array_size, int** score_matrix);
    int ScoreFinder(int i, int j,const char * seq1, const char * seq2, int array_size,int **score_matrix);


    void BLAST(int number_of_queries, int seed_size, int query_size, int n, float p);
    int getLength(const char *filename);
    void readFile(const char * filename, int lines_to_read);
    void queryBuilder(char * query,int query_size, int seed_size);
    void BLASTfile(int seed_size, int query_size, int n);
    void BLASTfile(char * filename, int lines_to_read, int seed_size, int query_size, int n);
};


#endif //HW4_BLAST_DB_H
