#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// XOR function 
bool* XOR(bool* A,bool * B,int len){
    bool *C = (bool*)malloc(sizeof(bool)*len);    
    int i;
    for(i = 0; i < len; i++)
        C[i] = A[i]^B[i];
    return C;
}

// Substitution function
void substitution(bool **Stable,bool* text,int length){
    int i;
    bool* Sub = Stable[text[3]*8 + text[2]*4 + text[1]*2 + text[0]*1];
    for(i = 0; i < 4; i++)
        text[i] = Sub[i];
    return;
}

// Permutation function
void permutation(int* Ptable,bool* text,int length){
    int 
}

int main(int argn,char ** argv){
    char * keyString = argv[1];
    char * plainText = argv[2];
    char * mode = argv[3];
    bool key[32],i,j,k;
    bool plainTextBin[16];
    for(i = 0; i < 16; i++)
        plainTextBin[i] = plainText[i] - '0';
    for(i = 0; i < 32; i++)
        key[i] = keyString[i]-'0';
    // Assuming input is in HexaDecimal mode so each character is equivalently a 4 bit string. Assuming 4 rounds and each plain text contains 16 bits. 
    // Generate round Keys
    bool keys[5][16];
    for(i = 0; i < 5; i++){
        for(j = 0; j < 16; j++){
            keys[i][j] = key[(4*i+j)];
        }
    }
    // Substitution table - Hard Coded for now
    bool Stable[5][4] = {{1,1,1,0},
                        {0,1,0,0},
                        {1,1,0,1},
                        {0,0,0,1},
                        {0,0,1,0},
                        {1,1,1,1},
                        {1,0,1,1},
                        {1,0,0,0},
                        {0,0,1,1},
                        {1,0,1,0},
                        {0,1,1,0},
                        {1,1,0,0},
                        {0,1,0,1},
                        {1,0,0,1},
                        {0,0,0,0},
                        {0,1,1,1},
                        };

    // Permutation table - Hard Coded for now

    int Ptable[16] = {1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16};
    if(strcmp(mode,"E")==0){
        for( i = 0; i < 4-1; i++){
            plainTextBin = XOR(plainTextBin,keys[i]);
            for(j = 0; j < 4; j++){
                substitution(Stable,plainTextBin + 4*sizeof(bool)*j,4);
            }
            permutation(Ptable,plainTextBin,16);
        }
        plainTextBin = XOR(plainTextBin,keys[3]);
        for(i = 0; i < 4; i++)    
            substitution(Stable,plainTextBin + 4*sizeof(bool)*i,4);
        plainTextBin = XOR(plainTextBin,keys[4]); 
    }
}
