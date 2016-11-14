#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "loli.h"

void createToken(int type, char* name){
    token* t = (token*)malloc(sizeof(token));

    t -> type  = type;
    t -> name  = name;
    t -> next  = NULL;
    
    if (headToken == NULL){
    	headToken = t;
	} else{
		prevToken = currentToken;
		t -> prev = prevToken;
		prevToken -> next = t;
	}
	
	currentToken = t;
}

int moveTokenToNext(){
	if (currentToken -> next == NULL){
		return 0;
	}
	
	prevToken = currentToken;
	currentToken = currentToken -> next;
	return 1;
}

int moveTokenToPrev(){
	if (currentToken -> prev == NULL){
		return 0;
	}
	
	currentToken = currentToken -> prev;
	
	if (currentToken -> prev != NULL){
		prevToken = currentToken -> prev;
	}
	
	return 1;
}

char* int2Char(int number){
    int n = log10(number) + 1;
    int i = n - 1;
	char *numberArray = calloc(n, sizeof(char));
    
    for (; i > -1; --i, number /= 10 ){
		numberArray[i] = number % 10 + '0';
    }
    
    return numberArray;
}

int init(char *fileName){
	fin = fopen(fileName, "r");
	
	return fin != NULL;
}

int getChar(){
	if (cacheIndex >= lineLength){
		++lineNumber;
		ch = ' ';
		lineLength = 0;
		cacheIndex = 0;
		while (ch != '\n'){
			if(fscanf(fin, "%c", &ch) == EOF){
                charCache[lineLength] = 0;
                break;
            }
            
            charCache[lineLength] = ch;
            ++lineLength;
            
            if(lineLength == cacheLength){
                break;
            }
		}
	}
	
	prevCh = ch;
	ch = charCache[cacheIndex];
	++cacheIndex;
	
	return (ch == 0)? -1: 0;
}

int checkReserved(){
	int i = 0;
	for (; i < reservedLength; i++){
		if (strcmp(idCache, reservedName[i]) == 0){
			return reservedSymbol[i];
		}
	}
	
	return ident;
}

int getToken(){
	while (ch == ' ' || ch == '\t' || ch == '\n'){
		getChar();
	}
	
    int result;
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
		int index = 0;
        int length = 0;
        
        do{
            ++length;
            if(index < idLength){
                idCache[index] = ch;
                ++index;
            }
            
            result = getChar();
        }while((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9') || ch == '_');
        
        idCache[index] = 0;
        
        if(length > idLength){
        	//error();
        }
        
        createToken(checkReserved(), idCache);
        
        return result;
	} else if (ch >= '0' && ch <= '9'){
		int num = 0;
		int numLength = 0;
        
        do{
			num = 10 * num + ch - '0';
			
            ++numLength;
            
            result = getChar();
        }while(ch >= '0' && ch <= '9');
        
        createToken(number, int2Char(num));
        
        return result;
	} else {
		switch (ch){
            case '=':
                createToken(assign, "=");
                getChar();
                break;
                
            case ';':
                createToken(semicon, ";");
                getChar();
                break;
        }
	}
	
	return -1;
}

int main(int argc, char *argv[]){
	if (init(argv[1]) == 0){
		printf("error");
		return 1;
	}
	
	getToken();
	
	printf("new: %d\t%s\n", currentToken -> type, currentToken -> name);
	
	getToken();
	
	printf("new: %d\t%s\n", currentToken -> type, currentToken -> name);
	
	getToken();
	
	printf("new: %d\t%s\n", currentToken -> type, currentToken -> name);
	
	getToken();
	
	printf("new: %d\t%s\n", currentToken -> type, currentToken -> name);
	
	getToken();
	
	printf("new: %d\t%s\n", currentToken -> type, currentToken -> name);
	
	return 0;
}
