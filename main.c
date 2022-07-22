#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main(){
    
    //Get Instruction from the user (using standard input)
    printf("Enter an ARM instruction: ");  
    char str[MAX_LIMIT]; 
    fgets(str, MAX_LIMIT, stdin); 
    
    // Create an instruction structure from instruction string
    Instruction instruction = parseInstructionString(str);            
    unsigned int num = 0;
    
    while(!feof(stdin)){
        fscanf(stdin, "%s\n", &instruction);
        num = convert(instruction);
        
        fprintf(stdout, "%x\n", num);
    }
    //Print the contents of the instruction 
    printInstruction(instruction);
 
    return (EXIT_SUCCESS);
}

