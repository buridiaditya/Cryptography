#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// XOR function 
void XOR(bool* A,bool * B,int len){
    int i;
    for(i = 0; i < len; i++)
        A[i] = A[i]^B[i];
    return ;
}

// Generates Private Key Randomly
bool* generatePrivateKey(int size){
    int i;
    bool * key = (bool*) malloc(sizeof(bool) * size);
    for(i = 0; i < size; i++)
        key[i] = rand()%2;
    return key;
}

// Converts plain Text to binary
bool* textToBinary(char* plainText){
    int i,j;
    bool * binaryPlainText = (bool*) malloc(strlen(plainText) * 8 * sizeof(bool) );
    for( i = 0; i < strlen(plainText); i++ ){
        for( j = 0; j < 8; j++ )
        binaryPlainText[j+8*i] = (plainText[i] & (1<<(7-j)) ? (1):(0) );
    }
    return binaryPlainText;
}

bool* binaryStringBoolArray(char* input){
    int i;
    bool* array = (bool*)malloc(sizeof(bool)*strlen(input));
    for(i = 0; i < strlen(input); i++)
        array[i] = input[i]-'0';
    return array;
}

// Generates Round Keys
bool** generateRoundKeys(bool* key,int size,int rounds){
    int i ;
    if(rounds > size/4) rounds = size/4;
    bool ** keys = (bool**)malloc(sizeof(bool*)*rounds);

    for(i = 0; i < rounds; i++)
        keys[i] = key + 4;
    return keys;
}

// Substitution function
void substitution(bool Stable[16][4],bool* text){
    int i;
    bool* Sub = Stable[text[0]*8 + text[1]*4 + text[2]*2 + text[3]*1];
    for(i = 0; i < 4; i++)
        text[i] = Sub[i];
    return;
}

// Permutation function
void permutation(int* Ptable,bool* text,int length){
    int i;
    bool temp;
    bool memory[length];
    for(i = 0; i < length; i++)
        memory[i] = false;
    for(int i = 0; i < length; i++){
        if(memory[i] == false){
            memory[Ptable[i]-1] = true;
            memory[i] = true;
            temp = text[i];
            text[i] = text[Ptable[i]-1];
            text[Ptable[i]-1] = temp;
        }
    }
    return;
}

int main(int argn,char **argv){

    char * plainText = (char*)malloc(sizeof(char)*100);
    char * mode = (char*)malloc(sizeof(char)*5);
    bool * key;
    bool** roundKeys;
    bool* plainTextBinary;
    bool* plainTextBinTrun;
    bool keys[5][16];
    int i,j,k,l,m,sizeOfKey = 32,rounds = 5;
    int lengthOfRoundKey = ((sizeOfKey/4 < rounds)?(4):( (sizeOfKey/4 - rounds + 1) * 4 ));

    srand(time(NULL));
    
    key = generatePrivateKey(sizeOfKey);
    roundKeys = generateRoundKeys(key,sizeOfKey,rounds);

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Substitution table 
    bool Stable[16][4] = {{1,1,1,0},{0,1,0,0},{1,1,0,1},{0,0,0,1},{0,0,1,0},{1,1,1,1},{1,0,1,1},{1,0,0,0},{0,0,1,1},{1,0,1,0},{0,1,1,0},{1,1,0,0},{0,1,0,1},{1,0,0,1},{0,0,0,0},{0,1,1,1}};
    bool SInvtable[16][4] = {{1,1,1,0},{0,0,1,1},{0,1,0,0},{1,0,0,0},{0,0,0,1},{1,1,0,0},{1,0,1,0},{1,1,1,1},{0,1,1,1},{1,1,0,1},{1,0,0,1},{0,1,1,0},{1,0,1,1},{0,0,1,0},{0,0,0,0},{0,1,0,1}};

    // Permutation table 
    int Ptable[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //// ENSURE PLAIN TEXT SIZE TO BE EQUAL TO ROUNDKEY SIZE
    while(1){
        scanf("%s",mode);
        if(strcmp(mode,"E")==0){
            scanf("%s",plainText);
            printf("Encryption of %s : ",plainText);
            plainTextBinary = textToBinary(plainText);
            
            for(i = 0; i < strlen(plainText)*8; i++)
                printf("%d",plainTextBinary[i]);
            printf("\n");

            for( l = 0; l < (strlen(plainText)*8)/lengthOfRoundKey; l++){
                plainTextBinTrun = plainTextBinary + lengthOfRoundKey*l;

                for( i = 0; i < rounds-2; i++){
                    XOR(plainTextBinTrun,keys[i],lengthOfRoundKey);
                    for(j = 0; j < lengthOfRoundKey/4; j++){
                        substitution(Stable,plainTextBinTrun + 4*j);
                    }
                    permutation(&Ptable[0],plainTextBinTrun,lengthOfRoundKey);
                }
                XOR(plainTextBinTrun,keys[rounds-2],lengthOfRoundKey);
                for(i = 0; i < lengthOfRoundKey/4; i++)    
                    substitution(Stable,plainTextBinTrun + 4*i);
                
                XOR(plainTextBinTrun,keys[rounds-1],lengthOfRoundKey); 

            }
            printf("Encrypted : ");
            for(i = 0; i < strlen(plainText)*8; i++){
                printf("%d",plainTextBinary[i]);   
            }
            printf("\n");   
        }
        else if(strcmp(mode,"D") == 0){
            scanf("%s",plainText);
            plainTextBinary = binaryStringBoolArray(plainText);
            for(l = 0; l <  (strlen(plainText))/lengthOfRoundKey; l++){
                plainTextBinTrun = plainTextBinary + lengthOfRoundKey*l;
                
                XOR(plainTextBinTrun,keys[rounds-1],lengthOfRoundKey);
                
                for(i = 0; i < lengthOfRoundKey/4; i++)
                    substitution(SInvtable,plainTextBinTrun + 4 * i);
                XOR(plainTextBinTrun,keys[rounds-2],lengthOfRoundKey);
                for(i = rounds-3; i >= 0; i--){
                    permutation(&Ptable[0],plainTextBinTrun,lengthOfRoundKey);
                    for( j = 0; j < lengthOfRoundKey/4; j++){
                        substitution(SInvtable,plainTextBinTrun + 4 * j);
                    }
                    XOR(plainTextBinTrun,keys[i],lengthOfRoundKey);
                }
            }
            printf("Decrypted : ");
            for(int i = 0; i < strlen(plainText); i++){
                printf("%d",plainTextBinary[i]);   
            }
            printf("\n");
        }
        else if(strcmp(mode,"exit")==0){
            break;
        }
    }
}
