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
    cout <<"BLAST constructor ran"<<endl;
    hashtable = new FASTAreadset_HT(filename, m, seq_size);
    query_queue = new FASTAreadset_LL;

}
BLAST_DB::~BLAST_DB(){

    cout << "destructor ran" << endl;
//    delete hashtable;
//loop through query array and destroy

}

const char * BLAST_DB::splitQuery(int seed_size, int query_size,float p) {
   //
    int g_index = hashtable->generateRandom(seed_size, query_size);
   const char * rand_query = hashtable->generateFalseSequences(g_index, query_size,p);
   hashtable->generateSequences(g_index,query_size);

    Node * search_result;

  //  cout << rand_query << endl;

    for (int i = 0; i < query_size - seed_size + 1; i++) {
        char *queryMers = new char[query_size + 1];
        for (int j = 0; j < seed_size; j++) {
            queryMers[j] = rand_query[i + j];
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
//    print_score_matrix(array_size,score_matrix);
    return score_matrix[array_size][array_size];
}
// UPDATE TRACeback with score matrix increments  (sampe two loops)
//second function uses traceback matrix to rebuild sequence locations


void BLAST_DB::BLAST(int number_of_queries,int seed_size, int query_size, int n, float p) {
// n is match success rate for saving entry (0-100%)

    int score_before = 0;
    int score_after = 0;
    int total_score = 0;
    int count = 0;
    int seed_loc;
    int genome_loc;

    int query_before_start;
    int query_after_start;
    int query_after_end;
    int genome_before_start;
    int genome_after_start;


    int before_seed_length;
    int after_seed_length;

    //read in queries from file
    //DO this in main first
    // run BLAST
    int max_score;
    for (int i = 0; i < number_of_queries; i++) {
//updating query_queue with random queries from genome;
        max_score = 0;
        const char *rand_query = splitQuery(seed_size, query_size, p);


        Node *current_seed;
        Node *current_genome_node;
        current_seed = query_queue->removeLast();


        while (current_seed != nullptr) {
       //     cout << current_seed->sequence << '\t' << current_seed->location << endl;

            current_genome_node = hashtable->radixSearch(current_seed->sequence, seed_size, true);
            seed_loc = current_seed->location;

            query_before_start = 0;
        //    query_before_end = seed_loc;
            query_after_start = seed_loc + seed_size;
            query_after_end = query_size;


            before_seed_length = seed_loc;
            after_seed_length = query_after_end - query_after_start;

            char *query_before_sequence = new char[before_seed_length + 1];
            char *query_after_sequence = new char[after_seed_length + 1];
            char *genome_before_sequence = new char[before_seed_length + 1];
            char *genome_after_sequence = new char[after_seed_length + 1];

            while (current_genome_node != nullptr) {

                genome_loc = current_genome_node->location;

                genome_before_start = genome_loc - seed_loc;
        //        genome_before_end = genome_loc;
                genome_after_start = genome_loc + seed_size;
       //         genome_after_end = genome_loc + query_size - seed_size;

                if (seed_loc == 0 && genome_before_start >= 0) {
                    for (int i = 0; i < after_seed_length; i++) {
//                        cout << "After Only" << endl;
//                        cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                             << after_seed_length << endl;
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];


                    }
                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';
//                    cout << "query_after:\t" << query_after_sequence << endl;
//                    cout << "genome_after:\t" << genome_after_sequence << endl;
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                } else if (seed_loc == 39 && genome_before_start >= 0) {
                    for (int i = 0; i < before_seed_length; i++) {
//                            cout << "Before Only" << endl;
//                            cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                                 << after_seed_length << endl;
                        query_before_sequence[i] = rand_query[query_before_start + i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];


                    }
                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';
                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);

                } else if (seed_loc > 0 && seed_loc < 39 && genome_before_start >= 0) {

                    for (int i = 0; i < before_seed_length; i++) {
                        query_before_sequence[i] = rand_query[i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];
                    }

                    for (int i = 0; i < after_seed_length - 1; i++) {
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];
                    }

                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';

                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';

                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                    //removing seed

                }

                total_score = score_before + score_after + 22;
                if (total_score > max_score){
                    max_score = total_score;
                }
          //      cout << "score_before:\t" << score_before << '\t' << "score_after:\t" << score_after << '\t'
            //         << "Total score is:\t" << total_score<< endl;

                score_after = 0;
                score_before = 0;
         //       total_score = 0;

                current_genome_node = current_genome_node->next;
            } // search node while loop
            Node * temp = current_seed;
            delete[] temp->sequence;

            current_seed = query_queue->removeLast();
        } //query_que while loop

        if (max_score >= n) {
            count++;

        }

    }
    cout << "Count is: \t" << count <<endl;
}

//keep track of best score ( and seed) if you dont meet a threshold (like 100%)
//iterate through with different values for iteration
// add error within splitQuery function



void BLAST_DB::BLASTfile(char * filename, int lines_to_read,int seed_size, int query_size, int n) {
// n is match success rate for saving entry (0-100%)

    ifstream input;        //create filestream to read the file
    input.open(filename);        //initialize the filestream by pointing it to the right file
    char *temp_head = new char[1000];
//    char *temp_read = new char[1000];
    if (lines_to_read == 0) {
        num_of_lines_read = getLength(filename);
    } else{
        num_of_lines_read = lines_to_read;
    }
//    cout << "Reading " << num_of_lines_read << " lines" << endl;
    query_array = new char*[num_of_lines_read];

    for (int i = 0; i < num_of_lines_read; i++) {
        query_array[i] = new char[51];
        input >> temp_head;    //read in the header line
        input >> query_array[i];//read in the read line

    }
    cout << "reading in line: " << 3 << '\t' << query_array[3] << endl;

    int score_before = 0;
    int score_after = 0;
    int total_score = 0;
    int count = 0;
    int seed_loc;
    int genome_loc;

    int query_before_start;
    int query_after_start;
    int query_after_end;
    int genome_before_start;
    int genome_after_start;


    int before_seed_length;
    int after_seed_length;

    //read in queries from file
    //DO this in main first
    // run BLAST
    int max_score;
    for (int i = 0; i < num_of_lines_read; i++) {
        max_score = 0;
//updating query_queue with random queries from genome;

        const char * rand_query = query_array[i];
        queryBuilder(query_array[i],50,11);


        Node *current_seed;
        Node *current_genome_node;
     //   query_queue->printLL();
        current_seed = query_queue->removeLast();
//cout << "current seed: \t" << current_seed->sequence << endl;

        while (current_seed != nullptr) {
        //    cout << current_seed->sequence << '\t' << current_seed->location << endl;

            current_genome_node = hashtable->radixSearch(current_seed->sequence, seed_size, true);
            seed_loc = current_seed->location;

            query_before_start = 0;
            //    query_before_end = seed_loc;
            query_after_start = seed_loc + seed_size;
            query_after_end = query_size;


            before_seed_length = seed_loc;
            after_seed_length = query_after_end - query_after_start;

            char *query_before_sequence = new char[before_seed_length + 1];
            char *query_after_sequence = new char[after_seed_length + 1];
            char *genome_before_sequence = new char[before_seed_length + 1];
            char *genome_after_sequence = new char[after_seed_length + 1];

            while (current_genome_node != nullptr) {

                genome_loc = current_genome_node->location;

                genome_before_start = genome_loc - seed_loc;
                //        genome_before_end = genome_loc;
                genome_after_start = genome_loc + seed_size;
                //         genome_after_end = genome_loc + query_size - seed_size;

                if (seed_loc == 0 && genome_before_start >= 0) {
                    for (int i = 0; i < after_seed_length; i++) {
//                        cout << "After Only" << endl;
//                        cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                             << after_seed_length << endl;
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];


                    }
                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';
//                    cout << "query_after:\t" << query_after_sequence << endl;
//                    cout << "genome_after:\t" << genome_after_sequence << endl;
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                } else if (seed_loc == 39 && genome_before_start >= 0) {
                    for (int i = 0; i < before_seed_length; i++) {
//                            cout << "Before Only" << endl;
//                            cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                                 << after_seed_length << endl;
                        query_before_sequence[i] = rand_query[query_before_start + i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];


                    }
                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';

//                        cout << "query_before:\t" << query_before_sequence << endl;
//                        cout << "genome_before:\t" << genome_before_sequence << endl;
                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);

                } else if (seed_loc > 0 && seed_loc < 39 && genome_before_start >= 0) {

                    for (int i = 0; i < before_seed_length; i++) {
                        query_before_sequence[i] = rand_query[i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];
                    }

                    for (int i = 0; i < after_seed_length - 1; i++) {
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];
                    }

//                    cout << "Before and After" << endl;
//                    cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t" << after_seed_length
//                         << endl;
//                    cout << "query_before:\t" << query_before_sequence << endl;
//                    cout << "genome_before:\t" << genome_before_sequence << endl;
//                    cout << "query_after:\t" << query_after_sequence << endl;
//                    cout << "genome_after:\t" << genome_after_sequence << endl;

                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';

                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';

                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                    //removing seed

                }

                total_score = score_before + score_after + 22;
                if (total_score > max_score){
                    max_score = total_score;
                }
                //      cout << "score_before:\t" << score_before << '\t' << "score_after:\t" << score_after << '\t'
                //         << "Total score is:\t" << total_score<< endl;

                score_after = 0;
                score_before = 0;
                //       total_score = 0;

                current_genome_node = current_genome_node->next;
            } // search node while loop
            Node * temp = current_seed;
            delete[] temp->sequence;

            current_seed = query_queue->removeLast();
        } //query_que while loop
//cout << "max score is: \t" <<max_score << endl;
        if (max_score >= n) {
            count++;
        }
    }
    cout << "Count is: \t" << count <<endl;

}

//keep track of best score ( and seed) if you dont meet a threshold (like 100%)
//iterate through with different values for iteration
// add error within splitQuery function

int BLAST_DB::getLength(const char *filename) {
    fstream input;
    input.open(filename);

    char line_buffer[100];
    int length_count = 0;

    while (input.good()) { // until input no longer works
        length_count++; //add to length count
        input >> line_buffer; //temp storage
    }
//    divide counter by 2 for header and line
   int length = length_count / 2;
    return length;
}

void BLAST_DB::readFile(const char * filename, int lines_to_read) {

    ifstream input;        //create filestream to read the file
    input.open(filename);        //initialize the filestream by pointing it to the right file
    char *temp_head = new char[1000];
//    char *temp_read = new char[1000];
    if (lines_to_read == 0) {
        num_of_lines_read = getLength(filename);
    } else{
        num_of_lines_read = lines_to_read;
    }
//    cout << "Reading " << num_of_lines_read << " lines" << endl;
    query_array = new char*[num_of_lines_read];

    for (int i = 0; i < num_of_lines_read; i++) {
        query_array[i] = new char[51];
        input >> temp_head;    //read in the header line
        input >> query_array[i];//read in the read line
    //    cout << "reading in line: " << i << '\t' << query_array[i] << endl;

    }
}



void BLAST_DB::queryBuilder(char * query,int query_size, int seed_size){
    int g_index = hashtable->generateRandom(seed_size, query_size);
    hashtable->generateSequences(g_index,query_size);

    for (int i = 0; i < query_size - seed_size + 1; i++) {
        char *queryMers = new char[query_size + 1];
        for (int j = 0; j < seed_size; j++) {
            queryMers[j] = query[i + j];
    }
    queryMers[seed_size] = '\0';
    Node * search_result = hashtable->radixSearch(queryMers, seed_size, true);
    if (search_result != nullptr) {
     //   cout << queryMers<<endl;
        query_queue->addNode(queryMers, i);
    }
}

}






void BLAST_DB::BLASTfile(int seed_size, int query_size, int n) {
// n is match success rate for saving entry (0-100%)

    int score_before = 0;
    int score_after = 0;
    int total_score = 0;
    int count = 0;
    int seed_loc;
    int genome_loc;

    int query_before_start;
    int query_after_start;
    int query_after_end;
    int genome_before_start;
    int genome_after_start;


    int before_seed_length;
    int after_seed_length;

    //read in queries from file
    //DO this in main first
    // run BLAST
    int max_score;
    for (int i = 0; i < num_of_lines_read; i++) {
        max_score = 0;
//updating query_queue with random queries from genome;

        const char * rand_query = query_array[i];
        queryBuilder(query_array[i],50,11);


        Node *current_seed;
        Node *current_genome_node;
        //   query_queue->printLL();
        current_seed = query_queue->removeLast();
//cout << "current seed: \t" << current_seed->sequence << endl;

        while (current_seed != nullptr) {
            //    cout << current_seed->sequence << '\t' << current_seed->location << endl;

            current_genome_node = hashtable->radixSearch(current_seed->sequence, seed_size, true);
            seed_loc = current_seed->location;

            query_before_start = 0;
            //    query_before_end = seed_loc;
            query_after_start = seed_loc + seed_size;
            query_after_end = query_size;


            before_seed_length = seed_loc;
            after_seed_length = query_after_end - query_after_start;

            char *query_before_sequence = new char[before_seed_length + 1];
            char *query_after_sequence = new char[after_seed_length + 1];
            char *genome_before_sequence = new char[before_seed_length + 1];
            char *genome_after_sequence = new char[after_seed_length + 1];

            while (current_genome_node != nullptr) {

                genome_loc = current_genome_node->location;

                genome_before_start = genome_loc - seed_loc;
                //        genome_before_end = genome_loc;
                genome_after_start = genome_loc + seed_size;
                //         genome_after_end = genome_loc + query_size - seed_size;

                if (seed_loc == 0 && genome_before_start >= 0) {
                    for (int i = 0; i < after_seed_length; i++) {
//                        cout << "After Only" << endl;
//                        cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                             << after_seed_length << endl;
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];


                    }
                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';
//                    cout << "query_after:\t" << query_after_sequence << endl;
//                    cout << "genome_after:\t" << genome_after_sequence << endl;
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                } else if (seed_loc == 39 && genome_before_start >= 0) {
                    for (int i = 0; i < before_seed_length; i++) {
//                            cout << "Before Only" << endl;
//                            cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t"
//                                 << after_seed_length << endl;
                        query_before_sequence[i] = rand_query[query_before_start + i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];


                    }
                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';

//                        cout << "query_before:\t" << query_before_sequence << endl;
//                        cout << "genome_before:\t" << genome_before_sequence << endl;
                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);

                } else if (seed_loc > 0 && seed_loc < 39 && genome_before_start >= 0) {

                    for (int i = 0; i < before_seed_length; i++) {
                        query_before_sequence[i] = rand_query[i];
                        genome_before_sequence[i] = hashtable->genome_array[genome_before_start + i];
                    }

                    for (int i = 0; i < after_seed_length - 1; i++) {
                        query_after_sequence[i] = rand_query[query_after_start + i];
                        genome_after_sequence[i] = hashtable->genome_array[genome_after_start + i];
                    }

//                    cout << "Before and After" << endl;
//                    cout << "before_len:\t" << before_seed_length << '\t' << "after_seed_length:\t" << after_seed_length
//                         << endl;
//                    cout << "query_before:\t" << query_before_sequence << endl;
//                    cout << "genome_before:\t" << genome_before_sequence << endl;
//                    cout << "query_after:\t" << query_after_sequence << endl;
//                    cout << "genome_after:\t" << genome_after_sequence << endl;

                    query_before_sequence[before_seed_length] = '\0';
                    genome_before_sequence[before_seed_length] = '\0';

                    query_after_sequence[after_seed_length] = '\0';
                    genome_after_sequence[after_seed_length] = '\0';

                    score_before = NW(query_before_sequence, genome_before_sequence, before_seed_length);
                    score_after = NW(query_after_sequence, genome_after_sequence, after_seed_length);

                    //removing seed

                }

                total_score = score_before + score_after + 22;
                if (total_score > max_score){
                    max_score = total_score;
                }
                //      cout << "score_before:\t" << score_before << '\t' << "score_after:\t" << score_after << '\t'
                //         << "Total score is:\t" << total_score<< endl;

                score_after = 0;
                score_before = 0;
                //       total_score = 0;

                current_genome_node = current_genome_node->next;
            } // search node while loop
            Node * temp = current_seed;
            delete[] temp->sequence;

            current_seed = query_queue->removeLast();
        } //query_que while loop
//cout << "max score is: \t" <<max_score << endl;
        if (max_score >= n) {
            count++;
        }
    }
    cout << "Count is: \t" << count <<endl;

}