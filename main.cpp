#include <iostream>
#include <fstream>
#include <cstring>
#include "BLAST_DB.h"
#include <stdlib.h>

using namespace std;

const char *seq1 = "ATGT";
const char *seq2 = "AGCT";

int array_size = 4;


int ScoreFinder(int i, int j, int ** score_matrix) {
    int current_max;
    int gap1 = score_matrix[i-1][j] - 1;
    int gap2 = score_matrix[i][j-1] - 1;

    if (seq1[i-1] == seq2[j-1]) {
        current_max = score_matrix[i-1][j-1] + 2;
    }else{
        current_max = score_matrix[i-1][j-1] -1;
    }
    if(gap1 >= gap2 && gap1 > current_max){
        return gap1;
    }
    if(gap2 >= gap1 && gap2 > current_max){
        return gap2;
    }
    return current_max;
}
void print_score_matrix(int** score_matrix){
    for(int i = 0; i < array_size + 1; i++){
        for (int j=0; j< array_size + 1 ; j++){
            cout << score_matrix[i][j] << '\t';
        }
        cout << endl;
    }
}


int NW(const char * seq1, const char * seq2, int array_size){
    int **score_matrix = new int *[array_size+1]; //
    for (int k = 0; k < array_size + 1; k++){
        score_matrix[k] = new int[array_size + 1];
    }

    for (int i=0; i< array_size + 1 ; i++){
        score_matrix[i][0] = 0 - i;
        score_matrix[0][i] = 0 - i;
    }

//    for (int i=0; i< array_size + 1 ; i++){
//        score_matrix[i][0] = 0 - i;
//    }
//
//    for (int j=0; j< array_size + 1 ; j++){
//        score_matrix[0][j] = 0 - j;
//    }

    for(int i = 1; i < array_size + 1; i++){
        for (int j=1; j< array_size + 1 ; j++){
            score_matrix[i][j] = ScoreFinder(i, j, score_matrix);
        }
    }

    print_score_matrix(score_matrix);
return 0;
}

int main(int argc, char ** argv) {
    NW(seq1, seq2,array_size);
    FASTAreadset_HT hashtable("/Users/ethanyackulic/CLionProjects/HW4/data/test2.fasta", 10, 4);
    //    BLAST_DB hashtable(argv[2], atoi(argv[3]), 11);
//    BLAST_DB blast("AAAAAA",3,2);
//    BLAST_DB blast("../data/test2.fasta", 10, 4);
 //   blast.splitQuery(11,11,seq1);
 //   blast.NW(seq1,seq2,11);
//    blast.hashtable->print_hashtable();



return 0;

}
//
