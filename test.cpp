////
//// Created by Ethan Yackulic on 4/18/22.
////
//
//char BLAST_DB::update_traceback(const char * seq1, const char * seq2, int index1, int index2, int ** score_matrix){
//    int gapLeft = 0;
//    int gapUp = 0;
//    int mismatch_score = 0;
//    char direction;
//
//    gapLeft = score_matrix[index1][index2 - 1] - 1;
//    gapUp = score_matrix[index1 - 1][index2] - 1;
//
//    if(seq1[index1 - 1] != seq2[index2 - 1]){
//        mismatch_score = score_matrix[index1 - 1][index2 - 1] - 1;
//
//    }else{
//        mismatch_score = score_matrix[index1 - 1][index2 - 1] + 2;
//    }
//
//    if (gapUp >= gapLeft && gapUp > mismatch_score){
//        direction = 'U';
//    } else if(gapLeft > gapUp && gapLeft > mismatch_score){
//        direction = 'L';
//    }else {
//        direction = 'D';
//    }
//
//    return direction;
//
//}
//
//prettyAlign * BLAST_DB::traceback_pretty(const char * seq1, const char * seq2, int index1, int index2, int alignment_score ,char ** traceback_matrix){
//
//    //new names: prettyAlign, buff 1,2,3 , alignment
//
//    prettyAlign * align = new prettyAlign;
//
//    char buff1[50];
//    char buff2[50];
//    char buff3[50];
//
//
//    align->seq1 = buff1;
//    align->seq2 = buff2;
//    align->seq3 = buff3;
//
//    int alignment;
//    for(int i = 0; i < query_length + 1; i++){
//        align->seq1[i] = '\0';
//        align->seq2[i] = '\0';
//        align->symbols[i] = '\0';
//    }
//    align->alignment_score = alignment_score;
//
//    char current_cell;
//    while(index1 >  0 || index2 > 0){
//        direction = traceback_matrix[index1][index2];
//        if(direction == 'L'){
//            align->seq2[alignment] = seq1[index2-1];
//            align->seq1[alignment] = '_';
//            align->symbols[alignment] = ' ';
//            index2--;
//        }else if(direction == 'U'){
//            align->seq2[alignment] = '_';
//            align->seq1[alignment] = seq2[index1-1];
//            align->symbols[alignment] = ' ';
//            index1--;
//        }else if (direction == 'D'){
//            if(index1 > 0){
//                align->seq1[alignment] = seq2[index1-1];
//            }else{
//                align->seq1[alignment] = '_';
//            }
//            if(index2 > 0){
//                align->seq2[alignment] = seq1[index2-1];
//            }else{
//                align->seq2[alignment] = '_';
//            }
//            if(seq1[index1-1] == seq2[index2-1] && index1 > 0 && index2 > 0){
//                align->symbols[alignment] = '|';
//            }else if(seq1[index1-1] != seq2[index2-1] && index1 > 0 && index2 > 0){
//                align->symbols[alignment] = 'x';
//            }else{
//                align->symbols[alignment] = ' ';
//            }
//
//            index1--;
//            index2--;
//
//        }
//        alignment++;
//    }
//
//
//
//    char * final_seq1 = new char[alignment+1];
//    char * final_seq2 = new char[alignment+1];
//    char * final_symbols = new char[alignment+1];
//
//    for (int i = alignment; i >= 0; i--){
//        final_seq1[alignment - i] = align->seq1[i-1];
//        final_seq2[alignment - i] = align->seq2[i-1];
//        final_symbols[alignment - i] = align->symbols[i-1];
//    }
//
//    align->seq1 = final_seq1;
//    align->seq2 = final_seq2;
//    align->symbols = final_symbols;
//
//    return align;
//}
//
//
//
//
//
//Alignment* BLAST_DB::NeedlemanWunsch(const char * sequence1, const char * sequence2, int sequence_length){
//    int** score_matrix = new int*[sequence_length+1];
//    char** traceback_matrix = new char*[sequence_length+1];
//    for(int i = 0; i < sequence_length+1; i++){
//        scorematrix[i] = new int[sequence_length+1];
//        traceback_matrix[i] = new char[sequence_length + 1];
//        for(int j = 0; j < sequence_length + 1; j++){
//            traceback_matrix[i][j] = '\0';
//        }
//        scorematrix[0][i] = 0-i;
//        traceback_matrix[0][i] = 'L';
//        scorematrix[i][0] = 0-i;
//        traceback_matrix[i][0] = 'U';
//
//    }
//
//    for(int i = 1; i < sequence_length + 1; i++){
//        for(int j = 1; j < sequence_length + 1; j++){
//            scorematrix[i][j] = get_score(sequence1, sequence2, i, j, scorematrix);
//            traceback_matrix[i][j] = update_traceback(sequence1, sequence2, i, j, scorematrix);
//        }
//
//    }
//
//    Alignment * output_alignment  = traceback_pretty(sequence1, sequence2, sequence_length, sequence_length, scorematrix[sequence_length][sequence_length], traceback_matrix);
//
//    //deleting traceback and score matrices
//
//    for(int i = 0; i < sequence_length; i++){
//        delete[] scorematrix[i];
//        delete[] traceback_matrix[i];
//    }
//
//    delete scorematrix;
//    delete traceback_matrix;
//
//    return output_alignment;
//}
//
//void BLAST_DB::print_pretty_alignmente(Alignment * before, Alignment * seed, Alignment * after){
//    if(before->seq1 == nullptr){
//        cout << seed->seq1 << after->seq1 << endl;
//        cout << seed->symbols << after->symbols << endl;
//        cout << seed->seq2 << after->seq2 << endl;
//        cout << "alignment score:\t" << (before->alignment_score + after->alignment_score + (SEED_LENGTH * 2)) << endl;
//        cout << endl;
//
//    }else if(after->seq1 == nullptr) {
//
//        cout << before->seq1 << seed->seq1  << endl;
//        cout << before->symbols << seed->symbols  << endl;
//        cout << before->seq2 << seed->seq2  << endl;
//        cout << "alignment score:\t" << (before->alignment_score + after->alignment_score + (SEED_LENGTH * 2)) << endl;
//        cout << endl;
//    }else
//    {
//        cout << before->seq1 << seed->seq1 << after->seq1 << endl;
//        cout << before->symbols << seed->symbols << after->symbols << endl;
//        cout << before->seq2 << seed->seq2 << after->seq2 << endl;
//        cout << "alignment score:\t" << (before->alignment_score + after->alignment_score + (SEED_LENGTH * 2)) << endl;
//        cout << endl;
//    }
//}

