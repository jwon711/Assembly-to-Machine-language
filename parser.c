#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

void removeChar(char* str, char c);


/* Parses string and initializes the Instruction structure */
Instruction parseInstructionString(char* instructionString){

   Instruction instruction;
   const char s[2] = " ";
   char *token;
   
   // Get first token (before space) which is the opcode......
   char** tokens;
   token = strtok(instructionString, s); 
   tokens = malloc(sizeof(char*));
   //printf("token length: %d\n", ( (int) strlen(token)) );
   tokens[0] = (char *) malloc(strlen(token)+1);
   strcpy(tokens[0], token);
   tokens[0][strlen(token)] = '\0';
   //printf("token: -%s-\n", tokens[0]);  
   int numTokens = 1;
   
   //Set instruction opcode 
   instruction.opcode = UNKNOWN;
   instruction.instruction_type = UNDEFINED;
   if (tokens[0] == NULL){
       printf("ERROR - Opcode string is NULL!\n");
       return instruction;
   }
   else if(strcmp(tokens[0], "ADD") == 0)
        instruction.opcode = ADD;
   else if(strcmp(tokens[0], "SUB") == 0)
        instruction.opcode = SUB;
   else if (strcmp(tokens[0], "ADDI") == 0)
        instruction.opcode = ADDI;
   else if (strcmp(tokens[0], "SUBI") == 0)
        instruction.opcode = SUBI;
   else if (strcmp(tokens[0], "STUR") == 0)
       instruction.opcode = STUR;
   else if (strcmp(tokens[0], "LDUR") == 0)
       instruction.opcode = LDUR;
   else{ 
       printf("ERROR - Unknown opcode!\n");       
       return instruction;
   }
   
   //Setting Instruction Type
   if (instruction.opcode == ADD || instruction.opcode == SUB)
        instruction.instruction_type = R;
   else if (instruction.opcode == ADDI || instruction.opcode == SUBI)
        instruction.instruction_type = I;   
   else if (instruction.opcode == LDUR || instruction.opcode == STUR)
        instruction.instruction_type = D;   
   
   // walk through other tokens 
   while( token != NULL ) {
      token = strtok(NULL, s);
      if (token != NULL){     
        
        removeChar( token, ','); 
        //printf("token length: %d\n", (int) strlen(token));  
        tokens = realloc(tokens, sizeof(char*) * (numTokens+1) );
        
        tokens[numTokens] = (char *) malloc(strlen(token)+1);
        strcpy(tokens[numTokens], token); 
        //printf("token: %s\n", tokens[numTokens]);
        
        //Population Instruction Structure
        if (instruction.instruction_type == R){
            if (numTokens == 1)
                instruction.Rd = ((int) tokens[numTokens][1]) - 48;
            else if (numTokens == 2)
                instruction.Rn = ((int) tokens[numTokens][1]) - 48;
            else if (numTokens == 3)
                instruction.Rm = ((int) tokens[numTokens][1]) - 48;   
         }
        else if (instruction.instruction_type == I){
            if (numTokens == 1)
                instruction.Rd = ((int) tokens[numTokens][1]) - 48;
            else if (numTokens == 2)
                instruction.Rn = ((int) tokens[numTokens][1]) - 48;
            else if (numTokens == 3)
                instruction.immediate = atoi(tokens[numTokens]);
        }
        else if (instruction.instruction_type == D){
            if (numTokens == 1)
                instruction.Rd = ((int) tokens[numTokens][1]) - 48;
            else if (numTokens == 2)
                instruction.Rn = ((int) tokens[numTokens][2]) - 48;
            else if (numTokens == 3){
                removeChar(tokens[numTokens], ']');
                tokens[numTokens][0] = ' ';
                instruction.immediate = atoi(tokens[numTokens]);
            }
        }
        (numTokens)++;        
      }  
   }   
    return instruction; 
}



/* Displays the contents of a Instruction structure */
void printInstruction(Instruction instr){
    printf("--------------------------\n");
    printf("Instruction Type: %d\n", instr.instruction_type);
    printf("Instruction Opcode: %d\n", instr.opcode);
    printf("Instruction Rd: %d\n", instr.Rd);
    printf("Instruction Rn: %d\n", instr.Rn);
    printf("Instruction Rm: %d\n", instr.Rm);
    printf("Instruction Immediate Field: %d\n", instr.immediate);
    printf("--------------------------\n");
}


/* Get first part of a string, delimiter is character c */
void removeChar(char* str, char c){
    for(int i=0;i<strlen(str); i++){
        if (str[i] == c){
            str[i] = '\0';
            return;
        }
    }
}
