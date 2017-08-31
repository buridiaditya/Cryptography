#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <boost/dynamic_bitset.hpp>
using namespace std;

void generatePrivateKey(boost::dynamic_bitset<> &key){
    for(int i = 0; i < key.size(); i++)
        key[i] = rand()%2;
    return;
}

void textToBinary(string s,boost::dynamic_bitset<> &bin){

}

void PC1(){

}

void PC2(){

}

void keyLeftCircularShift(boost::dynamic_bitset<> &key){
	bool temp1=key[0],temp2=key[key.size()/2];
	for(int i = 0; i < key.size()/2 - 1 ;i++){
		key[i] = key[i+1];
		key[i+key.size()/2] = key[i+key.size()/2+1];
	}
	key[key.size()/2 - 1] = temp1;
	key[key.size() - 1] = temp2;
}

void IP(boost::dynamic_bitset<> &text){

}

void expansion(vector<boost::dynamic_bitset<>> &Etable,boost::dynamic_bitset<>& text,boost::dynamic_bitset<>& F48){

}

void Substitution(){

}

void Permutation(){

}

int main(int argn,char** argv){
	string plainText,mode;
    int sizeOfKey = 54,rounds = 16;
    boost::dynamic_bitset<> key(sizeOfKey);
    boost::dynamic_bitset<> keyInternal(48);
    boost::dynamic_bitset<> plainTextBinary(64);
    boost::dynamic_bitset<> internal(48);
    generatePrivateKey(key,sizeOfKey);
    srand(time(NULL));
    while(1){
    	scanf("%s",mode);
    	if(strcmp(mode,"E")==0){
    		scanf("%s",plainText);
    		textToBinary(plainText,plainTextBinary);
    		IP(plainTextBinary);
    		for(int i = 0; i < rounds; i++){
    			expansion(Etable,plainTextBinary,internal);
    			XOR(internal,keyInternal);
    		}
    	}
    	else if(strcmp(mode,"D")==0){
    		scanf("%s",plainText);
    	}
    	else if(strcmp(mode,"exit")==0){
    		break;
    	}
    }
}