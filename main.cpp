#include <iostream>
#include "BLAST_DB.h"
using namespace std;

int main(int argc, char ** argv) {
//    NW(seq1, seq2);
//    BLAST_DB hashtable(argv[4], atoi(argv[3]), 11);

    const char *seq1 = "AAACTGCAAAC";
    const char *seq2 = "AAACTGCAAAT";

    BLAST_DB blast("../data/test2.fasta", 10, 4);
    blast.splitQuery(11,11,seq1);
    blast.NW(seq1,seq2,11);
    blast.hashtable->print_hashtable();



return 0;

}
//
