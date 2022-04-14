#include <iostream>
#include <fstream>
#include <cstring>
#include "BLAST_DB.h"
#include <stdlib.h>

using namespace std;

//
////
//int array_size = 4;
////
//const char *seq1 = "TAGT";
//const char *seq2 = "AGCG";
////
//int ScoreFinder(int i, int j, int ** score_matrix) {
//    int current_max;
//    int gap1 = score_matrix[i-1][j] - 1;
//    int gap2 = score_matrix[i][j-1] - 1;
//
//    if (seq1[i-1] == seq2[j-1]) {
//        current_max = score_matrix[i-1][j-1] + 2;
//    }else{
//        current_max = score_matrix[i-1][j-1] -1;
//    }
//    if(gap1 >= gap2 && gap1 > current_max){
//        return gap1;
//    }
//    if(gap2 >= gap1 && gap2 > current_max){
//        return gap2;
//    }
//    return current_max;
//}
//void print_score_matrix(int** score_matrix){
//    for(int i = 0; i < array_size + 1; i++){
//        for (int j=0; j< array_size + 1 ; j++){
//            cout << score_matrix[i][j] << '\t';
//        }
//        cout << endl;
//    }
//}
//void print_codes(char * char1, char * char2, char * char_code){
//    for ( int i = 0; i < array_size+1;i++){
//        cout << char1[i] <<" ";
//    }
//    cout << endl;
//    for ( int i = 0; i < array_size+1;i++){
//        cout << char_code[i] <<" ";
//    }
//    cout << endl;
//    for ( int i = 0; i < array_size+1;i++){
//        cout << char2[i] <<" ";
//    }
//    cout << endl;
//}
//
//
//void debug(int ** score_matrix, int array_size) {
//    int current_max;
//    int i = array_size;
//    int j = i;
//    char *char1;
//    char *char2;
//    char *char_code;
//    char1 = new char[array_size + 1];
//    char2 = new char[array_size + 1];
//    char_code = new char[array_size + 1];
//    while (i >= 0 && j >= 0) {
//        while (j > 0) {
//            int up = score_matrix[i - 1][j];
//            int left = score_matrix[i][j - 1];
//            int diag = score_matrix[i - 1][j - 1];
//            // char1[i] = ;
//            if (up >= left && up > diag) {
//                current_max = up;
//                i = i - 1;
//                j = j;
//                cout << "current_max is " << current_max << " going up" << endl;
//                char1[i] = '-';
//                char2[j] = seq2[j];
//                char_code[i] = '_';
//            } else if (left >= up && left > diag) {
//                current_max = left;
//                j = j - 1;
//                i = i;
//                cout << "current_max is " << current_max << " going left" << endl;
//                char1[i] = seq1[i];
//                char2[j] = '-';
//                char_code[i] = '_';
//            } else {
//                current_max = diag;
//                j = j - 1;
//                i = i - 1;
//                cout << "current_max is " << current_max << " going diag" << endl;
//                if (seq1[i] == seq2[j]) {
//                    char_code[i] = '|';
//                } else {
//                    char_code[i] = 'X';
//                }
//                char1[i + 1] = seq1[i];
//                char2[j + 1] = seq2[j];
//
//                //         }
//                //  cout << current_max << endl;
//            }
//        }
//        print_codes(char1, char2, char_code);
//    }

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
    debug(score_matrix,array_size);

return 0;
}

int main(int argc, char ** argv) {

   if (strcmp(argv[1], "1a") == 0) {
        time_t begin;
        time_t end;
        // FASTAreadset_HT hashtable("/Users/ethanyackulic/CLionProjects/HW4/data/test2.fasta", 10, 4);
        //    BLAST_DB hashtable(argv[2], atoi(argv[3]), 11);
        //   BLAST_DB blast();
        BLAST_DB blast(argv[2], 10000000, 11);
        //  BLAST_DB blast2("../data/sample_hw_dataset.fa", 10000000, 11);
//   blast.hashtable->print_hashtable();
        //  const char * rand_query = blast.splitQuery(11, 50, 0);
//  const char * =
        time(&begin);
        blast.BLAST(10000, 11, 50, 100, 0);
        time(&end);
        cout << "time of genome search :\t" << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 10000 << "\t error rate: \t" << 0 << endl;
        time(&begin);
  //      blast.BLAST(100000, 11, 50, 100, 0);
        time(&end);
        cout << "time of genome search : " << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 100000 << "\t error rate: \t" << 0 << endl;
        time(&begin);
   //     blast.BLAST(1000000, 11, 50, 100, 0);
        time(&end);
        cout << "time of genome search : " << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 1000000 << "\t error rate: \t" << 0 << endl;
        time(&begin);
        blast.BLAST(10000, 11, 50, 100, 0.05);
        time(&end);
        cout << "time of genome search : " << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 10000 << "\t error rate: \t" << 0.05 << endl;
        time(&begin);
   //     blast.BLAST(100000, 11, 50, 100, 0.05);
        time(&end);
        cout << "time of genome search : " << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 100000 << "\t error rate: \t" << 0.05 << endl;
        time(&begin);
   //     blast.BLAST(1000000, 11, 50, 100, 0.05);
        time(&end);
        cout << "time of genome search : " << end - begin << " seconds" << endl;
        cout << "number of queries:\t" << 1000000 << "\t error rate: \t" << 0.05 << endl;

    }
   if (strcmp(argv[1], "1b") == 0) {
       time_t begin;
       time_t end;
       // FASTAreadset_HT hashtable("/Users/ethanyackulic/CLionProjects/HW4/data/test2.fasta", 10, 4);
       //    BLAST_DB hashtable(argv[2], atoi(argv[3]), 11);
       //   BLAST_DB blast();
       BLAST_DB blast(argv[2], 10000000, 11);
       cout << "running readfile" << endl;
       blast.readFile(argv[3]);
       blast.BLASTfile(11, 50, 100);

   }
   return 0;

}
//
