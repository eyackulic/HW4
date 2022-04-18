//
// Created by Ethan Yackulic on 3/10/22.
//

#include "FASTAreadset_HT.h"
#include <cmath>
#include <stdlib.h>

FASTAreadset_HT::FASTAreadset_HT(){
    //default constructor for FASTA readset hashtable

    //initializing counters
    collisionCount = 0;
    frag_found_counter = 0;
}

FASTAreadset_HT::FASTAreadset_HT(const char *filename, int m, int seq_size) {
    //custom constructor - takes a file name and two integers
    // m is size of hashtable
    //seq size is number of characters per sequence
    //output is all possible, sequentially-derived sequences from filename, based on seq_size
    // Function calls:
            // FASTAreadsetLL::FASTAreadsetLL;
            // singleArray; HT.cpp; line 116
            // getSequences; HT.cpp; line 145

    // initializing values
    line = 0;
    collisionCount = 0;
    frag_found_counter = 0;
    hashtable_size = m;
    // initializing hash_table from Linked List class
    hash_table = new FASTAreadset_LL[m];
    //fills single array with all characters
    singleArray(filename);
    // derives all possible sequences from SingleArray
    getSequences(seq_size);

}

FASTAreadset_HT::~FASTAreadset_HT(){
  //destructor -- most items in this hw were destroyed onsite
    cout << "destructor ran" << endl;
    delete genome_array;
}


unsigned int FASTAreadset_HT::get_radix_value(const char *sequence, int seq_size) {
    //function to derive a radix value for an input sequence of seq_size size
    //function calculates the value for each character based on its position
    //sequence radix value are updated through addition as i increases (i.e. moves further right along the sequence)
    //Function calls:
    //Function called in: add_to_hashtable; HT.cpp ; line 82
    unsigned int radix_value = 0;
    for(int i=seq_size - 1; i>=0;i--){
        switch (sequence[i]){
            case 'A':
                radix_value += 0;
                break;
            case 'C':
                radix_value += 1 * pow(5, seq_size - i - 1);
                break;
            case 'G':
                radix_value += 2 * pow(5,seq_size-i - 1);
                break;
            case 'T':
                radix_value += 3 * pow(5,seq_size-i - 1);
                break;
            case 'N':
                radix_value += 4 * pow(5,seq_size-i - 1);
                break;
            default:
              //  cout << "" << endl;
                    radix_value +=0;
//                  cout << "invalid sequence character: " << sequence << endl;

//            case 'N':
//                radix_value += 4 * pow(4,seq_size-i);
//                break;
        }

    }
//returns final value

    return radix_value;
}

void FASTAreadset_HT::add_to_hashtable(const char *sequence, int seq_size, int location){
  //function to add a sequence to the hashtable
  // takes a sequence and converts into radix value
  // determines hash_index based on radix value and size of hashtable
  // determines if hash_table is empty at given hash_index
  // if so, a node is added for that sequence
  // otherwise, hash_index is not empty -- increment collision count
  // next, search if the sequence has already been put in hash table
  // if not, add new sequence to hash table

    //Function calls:
    //          addNode; LL.cpp; line 76
    //          isEmpty; LL.cpp; line 121
    //          get_radix_value; HT.cpp; line 48
    //          searchNode; LL.cpp; line 134

    //Function called in:
    //          getSequences; HT.cpp; line 145

    unsigned int radix_value = get_radix_value(sequence, seq_size);
    unsigned int hash_index = radix_value % hashtable_size;

    if(hash_table[hash_index].isEmpty()){
        hash_table[hash_index].addNode(sequence, location);
    }else {
        collisionCount++;
//        if (hash_table[hash_index].searchNode(sequence, seq_size) == nullptr) {
            hash_table[hash_index].addNode(sequence, location);
//        } else {
 //       }
    }
}


void FASTAreadset_HT::singleArray(const char *filename) {
    //creates a single array of all input sequences
    //creates a counter of all characters in array
    //Function calls:
    //Function called in:
    //          getSequence; HT.cpp ; line 145
    //          FASTAreadset_HT::FASTAreadset_HT; line 17


    ifstream input(filename);
    genome_array = new char[6000000]; // should be big enough to hold it
    char temp_buffer[1000];
    char current_char;
    genome_size = 0;

//skip first line
    input.getline(temp_buffer, 1000);
    //iterate through all entries
    while (input.get(current_char)) {
        if (current_char == 'A' || current_char == 'G' || current_char == 'T' || current_char == 'C' ||
            current_char == 'N') {
            //fill array
            genome_array[genome_size] = current_char;
            //increment count
            genome_size++;
        }
    }
}
void FASTAreadset_HT::getSequences(int seq_size) {
   // function that derives all possible sequences from a single array
    //Function calls:
    //              add_to_hashtable; HT.cpp; line 78
    //Function called in:
    //              FASTAreadset_HT::FASTAreadset_HT; line 17

    int start = 0;
    int end = seq_size;
    line = 0;
    //iterate through all genome entries
    while(end <= genome_size){
        int i = 0;
        char * new_seq = new char[seq_size+1];
        while (i < seq_size) {
            new_seq[i] = genome_array[start + i];
            i++;
        }
        new_seq[seq_size] = '\0';
        add_to_hashtable(new_seq, seq_size, start);
        //increment
        line++;
        start += 1;
        end += 1;
    }
}
void FASTAreadset_HT::print_genome(int seq_size) {
    // function that prints total number of lines and character cound
    //Function calls:
    //Function called in:
    int start = 0;
    int end = seq_size;
    int line = 0;
    //iterate through all genome entries
    while (end <= genome_size) {
        int i = 0;
        char *new_seq = new char[seq_size + 1];
        while (i < seq_size) {
            new_seq[i] = genome_array[start + i];
            i++;
        }
        line++;
        start += 1;
        end += 1;
    }
    cout << "total lines: " << line << endl;
    cout << "count: " << genome_size << endl;

}

void FASTAreadset_HT::print_hashtable(){
    // function to print hashtable
    // Function calls:
    //              printLL; LL.cpp; line 159
    //Function called in:
cout <<"hashtable size: \t" <<hashtable_size <<endl;
 //   for (int i =0; i < hashtable_size; i++) {
    for (int i =0; i < 15; i++) {
        cout << "index value " << i << endl;
        hash_table[i].printLL();
        cout << endl;
    }
}

bool FASTAreadset_HT::radixSearch(const char * input, int seq_size) {
    //
    // function that derives all possible sequences from a single array
    //Function calls:
    //              get_radix_value; HT.cpp; line 48
    //              isEmpty; LL.cpp; line 121
    //              searchNode; LL.cpp; line 134
    //Function called in:
    //              findRandomGM16Mers; HT.cpp; line 262
    //              findRandom16Mers; HT.cpp; line 319
    //              findMistakes; HT.cpp; line 397
    //
    unsigned int radix_value = get_radix_value(input, seq_size);
    unsigned int hash_value = radix_value % hashtable_size;
    if (hash_table[hash_value].isEmpty()){
        return false;
    } else if(hash_table[hash_value].searchNode(input, seq_size) == nullptr){
        return false;
    } else{
        frag_found_counter++;
        return true;
    }

}

Node * FASTAreadset_HT::radixSearch(const char * input, int seq_size, bool on) {
    //
    // function that derives all possible sequences from a single array
    //Function calls:
    //              get_radix_value; HT.cpp; line 48
    //              isEmpty; LL.cpp; line 121
    //              searchNode; LL.cpp; line 134
    //Function called in:
    //              findRandomGM16Mers; HT.cpp; line 262
    //              findRandom16Mers; HT.cpp; line 319
    //              findMistakes; HT.cpp; line 397
    //
    unsigned int radix_value = get_radix_value(input, seq_size);
    unsigned int hash_value = radix_value % hashtable_size;
    if (hash_table[hash_value].isEmpty()){
        return nullptr;
    } else if(hash_table[hash_value].searchNode(input, seq_size) == nullptr){
        return nullptr;
    } else{
        frag_found_counter++;
        return hash_table[hash_value].searchNode(input, seq_size);
    }

}

void FASTAreadset_HT::printCollisionCount(){
    // function that prints collision count
    //Function calls:
    //Function called in:
    cout << "total collisions count is: " << collisionCount<< endl;
}
int FASTAreadset_HT::generateRandom( int genome_size, int seq_size){
    // function that generates a random number for indexing genome
    //Function calls:
    //Function called in: findRandomGM16Mers; HT.cpp; line
    int r_num = rand();
    int randomNumber =  r_num % (genome_size - seq_size - 1);
    return randomNumber;
}

char * FASTAreadset_HT::generateSequences( int g_index, int seq_size){
    // function that generates all sequences based on a starting index position
    //Function calls:
    //Function called in:
    //              findRandomGM16Mers; HT.cpp; line 262
    //              findAll; HT.cpp; line 418
    char * random_genome_sequence = new char[seq_size+1];
    for (int i=0; i < seq_size; i++){
       random_genome_sequence[i] = genome_array[g_index + i];
    }
    random_genome_sequence[seq_size] = '\0';
    return random_genome_sequence;
}

void FASTAreadset_HT::findRandomGM16Mers(int seq_size, int iterations){
    // function that generates a random number for indexing genome
    // sequences of size seq_size are generated based on random indexing of the original sequences
    // these sequences are then searched for within the original dataset
    // process is repeated for n = iterations times
    // number of results returned should be equal to number of iterations
    //Function calls:
    //          generateRandom; HT.cpp; line 239
    //          generateSequences; HT.cpp; line 248
    //          radixSearch; HT.cpp; line 208
    //Function called in:
   int index;
   int genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i <iterations; i++){
        index = generateRandom(genome_size, seq_size);
        char * r_seq = generateSequences(index, seq_size);
        radixSearch(r_seq, seq_size);
        delete[] r_seq;
    }
    cout << "total fragments found in hash table: " << frag_found_counter <<endl;
}

char * FASTAreadset_HT::generateRandomSequence(int seq_size) {
    //function to generate a random sequence string of size seq_size
    // for each character in string, a random number between 0-3 is selected
    //char 'charly' variable is switched to correct character based on selected random number
    //process is completed for seq_size length
    //result is a string of A,C,T, and G, chosen at random
    //Function calls:
    //Function used in: findRandom16Mers; HT.cpp; line 317

    char * random_seq = new char[seq_size+1];
    char charly;
    for (int i = 0; i < seq_size; i++) {
        int r_num = rand();
        int rand = r_num % 3;
        if (rand == 0){
            charly = 'A';
        } else if (rand ==1){
            charly = 'C';
        } else if (rand ==2){
            charly = 'G';
        } else if (rand ==3){
            charly = 'T';
        }
        //add new character to sequence
        random_seq[i] = charly;
    }
    //cap end of string
    random_seq[seq_size] = '\0';
   // cout << random_seq <<endl;
    return random_seq;
}

void FASTAreadset_HT::findRandom16Mers(int seq_size, int iterations){
    //function used to chose random 16mers (or any size - seq_size controlled)
    //from given sequences
    //Function calls:
    //      generateRandomSequence; HT.cpp; line 285
    //      radixSearch; HT.cpp; line 208
    //Function called in:
    genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i <iterations; i++){
        char * r_seq = generateRandomSequence(seq_size);
        radixSearch(r_seq, seq_size);
        delete[] r_seq;
    }
    cout << "total fragments found in random sequences : " << frag_found_counter <<endl;
}


double FASTAreadset_HT::randomFloat(){
    //finds a random float value (i.e. random decimal between 0-1)
    //Function calls:
    //Function called in: bernoulli_trial; HT.cpp; line 344
    double new_val;

    new_val = (double)rand()/(double)RAND_MAX;
    return new_val;
}

bool FASTAreadset_HT::bernoulli_trial(float p){
    //TRUE/FALSE - does random float value pass bernoulli trial based on designated p?
    //Function calls: randomFloat; HT.cpp; line 335
    //Function called in: generateFalseSequences; HT.cpp; line 374
    float new_val;
    new_val = randomFloat();
    if(new_val <= p) {
        return true;
    }else{
        return false;
    }
}

char FASTAreadset_HT::random_char(char original){
    //returns a randomly selected character that does not equal input character
    // used for introducing erroneous characters into sequence
    //Function calls:
    //Function called in: generateFalseSequences; HT.cpp; line 374
    char possible_vals[4] = {'A', 'C', 'G', 'T'};
    char rand_vals = original;
    int random_number;

    while(rand_vals == original){
        random_number = rand() % 4;
        rand_vals = possible_vals[random_number];
    }

    return rand_vals;
}

char * FASTAreadset_HT::generateFalseSequences( int g_index, int seq_size, float p) {
    //function that uses bernoulli_trial, based on input p,
    //to test when to replace characters in a sequence in order to produce a p% error rate
    //when the bernoulli trial is TRUE, a switch is made using random_char
    //otherwise, the sequence enters the original character
    //Function calls:
    //          bernoulli_trial; HT.cpp; line 344
    //          random_char; HT.cpp; line 357
    //Function called in:
    //          findMistakes; HT.cpp; line 397
    char *random_genome_sequence = new char[seq_size + 1];
    for (int i = 0; i < seq_size; i++) {
        if (bernoulli_trial(p)) {
            random_genome_sequence[i] = random_char(genome_array[g_index + i]);
        } else {
            random_genome_sequence[i] = genome_array[g_index + i];
        }
        random_genome_sequence[seq_size] = '\0';
    }
    return random_genome_sequence;
}


void FASTAreadset_HT::findMistakes(int seq_size, float p){
    //function that takes false sequences generated based on an error rate of p
    // then searches for false sequences in original, non-altered dataset
    // output is number of fragments found after introducing 1% error rate
    //Function calls:
    //          generateFalseSequences; HT.cpp; line 374
    //          radixSearch; Ht.cpp; line 208
    //Function called in:

    int genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i < genome_size - seq_size + 1; i++){
 //   for (int i=0; i < genome_size - seq_size + 1; i++){
        char * r_seq = generateFalseSequences(i, seq_size, p);
        radixSearch(r_seq, seq_size);
        delete[] r_seq;
    }
    cout << "total fragments found in hash table with " << p*100 << "% character error: " << frag_found_counter <<endl;
}



void FASTAreadset_HT::findAll(int seq_size){
    //function that takes false sequences generated based on an error rate of p
    // then searches for false sequences in original, non-altered dataset
    // output is number of fragments found after introducing 1% error rate
    //Function calls:
    //          generateSequences; HT.cpp; line 248
    //          radixSearch; Ht.cpp; line 208
    //Function called in:

    int genome_size = line;
    frag_found_counter = 0;
    for (int i=0; i < genome_size + 1; i++){
   // for (int i=0; i < genome_size - seq_size + 1; i++){
        char * r_seq = generateSequences(i, seq_size);
        radixSearch(r_seq, seq_size);
        delete[] r_seq;
    }
    cout << "total fragments found in hash table: " << frag_found_counter <<endl;
}



char * FASTAreadset_HT::get_radix_string(int radix_value, int base, int seq_size) {
//create all sequences
    int seq_num;
    char* new_sequence = new char[seq_size+1];
    for(int i=seq_size - 1; i>=0;i--){
            int power = pow(base,i);
            seq_num = radix_value / power;

            if (seq_num == 0){
                new_sequence[(seq_size-1)-i] = 'A';
            }else if(seq_num == 1){
                new_sequence[(seq_size-1)-i] = 'C';
            }else if(seq_num == 2){
                new_sequence[(seq_size-1)-i] = 'G';
            }else if (seq_num == 3) {
                new_sequence[(seq_size - 1) - i] = 'T';
            }else if (seq_num == 4){
                    new_sequence[(seq_size-1)-i] = 'N';
                } else{
                cout << "Error" <<endl;
            }
           radix_value = radix_value % power;
//            case 'N':
//                radix_value += 4 * pow(4,seq_size-i);
//                break;
        }
        cout << new_sequence << endl;
        return new_sequence;
    }
