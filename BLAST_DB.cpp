//
// Created by Ethan Yackulic on 4/8/22.
//
#include <iostream>
#include <fstream>
#include <cstring>
#include "BLAST_DB.h"
#include <stdlib.h>


BLAST_DB::BLAST_DB(){};
BLAST_DB::BLAST_DB(const char *filename, int m, int seq_size) {
    cout <<"constructor ran"<<endl;
    hashtable = new FASTAreadset_HT{filename, m, seq_size};
    cout <<"constructor ran"<<endl;
}
BLAST_DB::~BLAST_DB(){

    cout << "destructor ran" << endl;
//    delete hashtable;

}

const char * BLAST_DB::splitQuery(int seed_size, int query_size,float p) {
   //
    int g_index = hashtable->generateRandom(seed_size, query_size);
   const char * rand_query = hashtable->generateFalseSequences(g_index, query_size,p);
    Node * search_result;
    int g_loc;
    char *queryMers = new char[query_size + 1];


    for (int i = 0; i < seq_size - query_size - 1; i++) {
        for (int j = 0; j < query_size; j++) {
            queryMers[i] = subset[i + j];
        }

        queryMers[seed_size] = '\0';
        search_result = hashtable->radixSearch(queryMers, seed_size, true);
        if (search_result != nullptr) {
            query_queue->addNode(queryMers, i);
        }
    }
    return rand_query;
}
            // Needleman-Wunsch

//      char * seq1;
//      for (int k = 0; k < i; k++) {
//          seq1[k] = subset[k];
//      }
//      char * seq2;
//          for (int q = 0; q <i ; q++){
//              seq2[q] = hashtable->genome_array[seed_size-i+q];
//            }
//



int BLAST_DB::ScoreFinder(int i, int j,const char * seq1, const char * seq2, int array_size, int ** score_matrix) {

    int current_max = 0;

    int gap1 = score_matrix[i-1][j] - 1;
    int gap2 = score_matrix[i][j-1] - 1;

    if (seq1[i-1] == seq2[j-1]) {
        current_max = score_matrix[i-1][j-1] + 2;
    }else{
        current_max = score_matrix[i-1][j-1] -1;
    }
    if(gap1 > gap2 && gap1 > current_max){
        return gap1;
    }
    if(gap2 > gap1 && gap2 > current_max){
        return gap2;
    }
    return current_max;
}

void BLAST_DB::print_score_matrix(int array_size, int** score_matrix){
    for(int i = 0; i < array_size + 1; i++){
        for (int j=0; j< array_size + 1 ; j++){
            cout << score_matrix[i][j] << '\t';
        }
        cout << endl;
    }
}

int BLAST_DB::NW(const char * seq1, const char * seq2, int seq_size){
    int array_size = seq_size;
    score_matrix = new int *[array_size+1];

    for (int k = 0; k < array_size + 1; k++){
        score_matrix[k] = new int[array_size + 1];
    }

    for (int i=0; i< array_size + 1 ; i++){
        score_matrix[i][0] = 0 - i;
    }
    for (int j=0; j< array_size + 1 ; j++){
        score_matrix[0][j] = 0 - j;
    }

    for(int i = 1; i < array_size + 1; i++){
        for (int j=1; j< array_size + 1 ; j++){
            score_matrix[i][j] = ScoreFinder(i, j, seq1, seq2,array_size,score_matrix);
        }
    }
    print_score_matrix(array_size,score_matrix);
    return 0;
}


