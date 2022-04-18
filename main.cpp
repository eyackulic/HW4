#include <iostream>
#include <fstream>
#include <cstring>
#include "BLAST_DB.h"
#include <stdlib.h>

using namespace std;

int main(int argc, char ** argv) {
//    time_t begin;
//    time_t end;
//    BLAST_DB blast(argv[2], 10000000, 11);
//    time(&begin);
//  //  blast.BLAST(10000, 11, 50, 100, 0);
//    time(&end);
   if (strcmp(argv[1], "1a") == 0) {
       time_t begin;
       time_t end;

       //    BLAST_DB blast("...data/test2.fasta", 10000000, 11);
       BLAST_DB blast(argv[2], 10000000, 11);

       time(&begin);
       int q = 1000000;
       float p = 0.05;
       blast.BLAST(q, 11, 50, 100,  p);
       time(&end);
       cout << "time of genome search :\t" << end - begin << " seconds" << endl;
       cout << "number of queries:\t" << q << "\t error rate: \t" << p << endl;
   }
   if (strcmp(argv[1], "1b") == 0) {
   //    time_t begin;
   //    time_t end;
       BLAST_DB blast(argv[2], 10000000, 11);
       cout << "running readfile" << endl;
     //  blast.readFile(argv[3],100);
       blast.BLASTfile(argv[3],100,11, 50, 10);
blast.hashtable->print_hashtable();
   }
   return 0;

}
//
