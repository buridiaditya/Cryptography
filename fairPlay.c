#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argn,char **argv){
        char * keyString = argv[1];
        char * plainText = argv[2];
        char * mode = argv[3];
        char key[5][5];
        int checkAlphaRow[26];
        int checkAlphaColumn[26];
        int alphaPosition = 0;
        int lenKey = strlen(keyString);
        int lenPlainText = strlen(plainText);
        int i,j;
        char * cipherText = (char *) malloc(sizeof(char)*2*lenPlainText);
        // Initialize alphabets positions
        for(i = 0; i < 26; i++){
                checkAlphaRow[i] = -1;
                checkAlphaColumn[i] = -1;
        }
        // Create the Key Matrix
        for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                        if(5*i+j < lenKey && checkAlphaRow[keyString[5*i+j]-'a'] == -1){
                                if((keyString[5*i+j] == 'j' || keyString[5*i+j] == 'i') && (checkAlphaRow['i' - 'a'] != -1 || checkAlphaRow['j' - 'a'] != -1)){
                                        if(checkAlphaRow['i'-'a'] != -1){
                                                checkAlphaRow['j'-'a'] = checkAlphaRow['i'-'a'];
                                                checkAlphaColumn['j'-'a'] = checkAlphaColumn['i'-'a'];
                                        }
                                        else if(checkAlphaRow['j'-'a'] != -1){
                                                checkAlphaRow['i'-'a'] = checkAlphaRow['j'-'a'];
                                                checkAlphaColumn['i'-'a'] = checkAlphaColumn['j'-'a'];
                                        }
                                        continue;
                                }
                                key[i][j] = keyString[5*i+j];
                                checkAlphaRow[keyString[5*i+j] - 'a'] = i;
                                checkAlphaColumn[keyString[5*i+j]-'a'] = j;
                        }
                        else{
                                while(checkAlphaRow[alphaPosition] != -1 || ((alphaPosition == 'j' - 'a' || alphaPosition == 'i' - 'a') && (checkAlphaRow['i'-'a'] != -1 || checkAlphaRow['j'-'a'] != -1))) 
                                        alphaPosition++;
                                key[i][j] = 'a' + alphaPosition;
                                checkAlphaRow[alphaPosition] = i;
                                checkAlphaColumn[alphaPosition] = j;
                        }
                }
        }
        for(i = 0; i < 5; i++){
                for(j = 0; j < 5; j++){
                        printf("%c ",key[i][j]);		
                }		
                printf("\n");
        }
        // Encrypt the Plain Text
        if(strcmp(mode,"E") == 0){
                for(i = 0,j = 0; i < lenPlainText; i++,j++){
                        int a = plainText[i]-'a';
                        int b;
                        if(i == lenPlainText-1)
                                b = 23;
                        else{
                                if(plainText[i] == plainText[i+1])
                                        b = 23;
                                else
                                        b = plainText[i+1]-'a';
                        }
                        if(checkAlphaRow[a] == checkAlphaRow[b]){	
                                cipherText[j] = key[checkAlphaRow[a]][(checkAlphaColumn[a]+1)%5];
                                cipherText[j+1] = key[checkAlphaRow[b]][(checkAlphaColumn[b]+1)%5];
                        }
                        else if(checkAlphaColumn[a] == checkAlphaColumn[b]){
                                cipherText[j] = key[(checkAlphaRow[a]+1)%5][checkAlphaColumn[a]];
                                cipherText[j+1] = key[(checkAlphaRow[b]+1)%5][checkAlphaColumn[b]];
                        }
                        else{
                                cipherText[j] = key[checkAlphaRow[a]][checkAlphaColumn[b]];
                                cipherText[j+1] = key[checkAlphaRow[b]][checkAlphaColumn[a]];
                        }
                        j++;
                        if(i != lenPlainText-1 && plainText[i] != plainText[i+1]){
                                i++;
                        }
                }
                printf("%s\n",cipherText);
        }
        else{
                // Decrypt the Cipher Text
                for(i = 0; i < lenPlainText; i++){
                        int a = plainText[i]-'a';
                        int b = plainText[i+1]-'a';
                        if(checkAlphaRow[a] == checkAlphaRow[b]){	
                                cipherText[i] = key[checkAlphaRow[a]][((checkAlphaColumn[a]-1 > 0)?(checkAlphaColumn[a]-1):(5+checkAlphaColumn[a]-1))];
                                cipherText[i+1] = key[checkAlphaRow[b]][((checkAlphaColumn[b]-1 > 0)?(checkAlphaColumn[b]-1):(5+checkAlphaColumn[b]-1))];
                        }
                        else if(checkAlphaColumn[a] == checkAlphaColumn[b]){
                                cipherText[i] = key[(checkAlphaRow[a]-1)%5][checkAlphaColumn[a]];
                                cipherText[i+1] = key[(checkAlphaRow[b]-1)%5][checkAlphaColumn[b]];
                        }
                        else{
                                cipherText[i] = key[checkAlphaRow[a]][checkAlphaColumn[b]];
                                cipherText[i+1] = key[checkAlphaRow[b]][checkAlphaColumn[a]];
                        }
                        i++;
                }
                printf("%s\n",cipherText);
        }
        return 0;
}
