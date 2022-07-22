#ifndef PARSER_H
#define PARSER_H

#define MAX_LIMIT 30
#define bufSize 1024

typedef enum INSTRUCTION_TYPES {UNDEFINED, R, I, D} INSTRUCTION_TYPE;
typedef enum OPCODES {UNKNOWN, ADD, ADDI, SUB, SUBI, LDUR, STUR} OPCODE;

typedef struct instruction_struct
{    
    INSTRUCTION_TYPE instruction_type;
    OPCODE opcode;
    int Rm;
    int Rn;
    int Rd;
    int immediate;
} Instruction;

Instruction parseInstructionString(char* instructionString);
void printInstruction(Instruction instr);


#endif /* PARSER_H */

