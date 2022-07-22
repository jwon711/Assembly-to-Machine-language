
#include "parser.h"
#include "assembler.h"

unsigned int convert(Instruction instruction){
    
    unsigned int output = 0;
    
    if(instruction.opcode == ADD || instruction.opcode == SUB){
        
        int opcode = 0;
        
        int opcode_mask = 0b11111111111;
        opcode_mask = opcode_mask << 21; 
        
        if(instruction.opcode == ADD){
            opcode = 0x458;
        }
        else{
            opcode = 0x658;
        }
        opcode = opcode << 21;
        opcode = opcode & opcode_mask;
        
        int rm_mask = 0b11111;
        rm_mask = rm_mask << 16;
        int rm = instruction.Rm;
        rm = rm << 16;
        rm = rm & rm_mask;
        
        int rn_mask = 0b11111;
        rn_mask = rn_mask << 5;
        int rn = instruction.Rn;
        rn = rn << 5;
        rn = rn & rn_mask;
        
        int rd = instruction.Rd;
        
        output = opcode | rm | rn | rd;
    }
    
    if(instruction.opcode == ADDI || instruction.opcode == SUBI){
        
        int opcode = 0;
        
        int opcode_mask = 0b1111111111;
        opcode_mask = opcode_mask << 22;
        
        if(instruction.opcode == ADDI){
            opcode = 0b1001000100;
        }
        else{
            opcode = 0b1101000100;
        }
        opcode = opcode << 22;
        opcode = opcode & opcode_mask;
        
        int immediate_mask = 0b111111111111;
        immediate_mask = immediate_mask << 10;
        int immediate = instruction.immediate;
        immediate = immediate << 10;
        immediate = immediate & immediate_mask;
        
        int rn_mask = 0b11111;
        rn_mask = rn_mask << 5;
        int rn = instruction.Rn;
        rn = rn << 5;
        rn = rn & rn_mask;
        
        int rd = instruction.Rd;
        
        output = opcode | immediate | rn | rd;
    }
    
    if(instruction.opcode == LDUR || instruction.opcode == STUR){
        
        int opcode = 0;
        
        int opcode_mask = 0b11111111111;
        opcode_mask = opcode_mask << 21;
        
        if(instruction.opcode == LDUR){
            opcode = 0x7C2;
        }
        else{
            opcode = 0x7C0;
        }
        
        opcode = opcode << 21;
        opcode = opcode & opcode_mask;
        
        int dt_address_mask = 0b111111111;
        dt_address_mask = dt_address_mask << 12;
        int dt_address = instruction.immediate;
        dt_address = dt_address << 12;
        dt_address = dt_address & dt_address_mask;
        
        int rn_mask = 0b11111;
        rn_mask = rn_mask << 5;
        int rn = instruction.Rn;
        rn = rn << 5;
        rn = rn & rn_mask;
        
        int rt = instruction.Rd;
        
        output = opcode | dt_address | rn | rt;
    }
    return output;
}

