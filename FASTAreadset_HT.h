//
// Created by Ethan Yackulic on 3/10/22.
//

#ifndef UNTITLED1_FASTAREADSET_HT_H
#define UNTITLED1_FASTAREADSET_HT_H

#include "FASTAreadset_LL.h"

class FASTAreadset_HT {
private:
    int hashtable_size;

    int collisionCount;
    int frag_found_counter;
    FASTAreadset_LL * hash_table;
    int line;

    Node *first = nullptr;
    Node *last = nullptr;

public:
    char * genome_array;
    FASTAreadset_HT();
    FASTAreadset_HT(const char *filename, int m, int seq_size);
    ~FASTAreadset_HT();

    unsigned int get_radix_value(const char * sequence, int seq_size);

    void add_to_hashtable(const char * sequence, int seq_size, int location);
    void getSequences(int seq_size);
    void singleArray(const char *filename);
    void print_hashtable();
    void printCollisionCount();
    void print_genome(int seq_size);
    //add search function
    bool radixSearch(const char * input, int seq_size);
    Node * radixSearch(const char * input, int seq_size, bool on);
    bool isEqual(const char * seq1, const char * seq2);
    int generateRandom (int genome_size, int seq_size);
    char * generateSequences(int g_index, int seq_size);
    void findRandomGM16Mers( int seq_size, int iterations);
    void findRandom16Mers( int seq_size, int iterations);
    char * generateRandomSequence(int seq_size);
    double randomFloat();
    bool bernoulli_trial(float p);
    char random_char(char original);
    char * generateFalseSequences( int g_index, int seq_size, float p);
    void findMistakes(int seq_size, float p);
    void findAll(int seq_size);
    char * get_radix_string(int radix_value, int base, int seq_size);


}
;
#endif //UNTITLED1_FASTAREADSET_HT_H
