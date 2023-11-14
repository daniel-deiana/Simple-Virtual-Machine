#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/termios.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/* Memory storage */
#define MEMORY_SIZE (1 << 16)
uint16_t memory[MEMORY_SIZE];

/* Registers */
enum
{
  R_R0 = 0,
  R_R1,
  R_R2,
  R_R3,
  R_R4,
  R_R5,
  R_R6,
  R_R7,
  R_PC,
  R_FLAGS,
  R_COUNT
};

uint16_t registers[R_COUNT];

/* Instruction opcodes */
enum
{
  OP_BR = 0, /* branch */
  OP_ADD,    /* add  */
  OP_LD,     /* load */
  OP_ST,     /* store */
  OP_JSR,    /* jump register */
  OP_AND,    /* bitwise and */
  OP_LDR,    /* load register */
  OP_STR,    /* store register */
  OP_RTI,    /* unused */
  OP_NOT,    /* bitwise not */
  OP_LDI,    /* load indirect */
  OP_STI,    /* store indirect */
  OP_JMP,    /* jump */
  OP_RES,    /* reserved (unused) */
  OP_LEA,    /* load effective address */
  OP_TRAP    /* execute trap */
};

enum
{
  FL_POS = 1 << 0, /* P */
  FL_ZRO = 1 << 1, /* Z */
  FL_NEG = 1 << 2, /* N */
};

/** sign_extend: Returns a 16 bit extended version of a 2's complement
  *  represented number 
  */ 
uint16_t sign_extend(uint16_t word, uint8_t lenght) {
  return 0;
}

int main (int argc, char* argv[]) {

  if (argc < 2) {
    /* show usage string */
    printf("lc3 [image-file1] ...\n");
    exit(2);
  }


  /*
  for (int j = 1; j < argc; ++j) {
    if (!read_image(argv[j])) {
      printf("failed to load image: %s\n", argv[j]);
      exit(1);
    }
  }
  */ 

  int running = 1; 

  /**
    * Initialize flags to zero and instruction pointer 
    * to starting position
  */
  registers[R_FLAGS] = FL_ZRO;

  enum{ PC_START = 0x3000 };
  registers[R_PC] = PC_START;

  while (running) {

    /**
     * First we fetch the instruction then inspect the opcode
     * to execute it 
    */

    uint16_t instr = mem_read(registers[R_PC]++); 
    // the opcode is found at the 4 msb of the instruction
    uint16_t opcode = instr >> 12; 

    switch (opcode)
    {
    
    case OP_BR:
      /**
        * Branch instruction: the semantic is, if any of the flags (n,z,p) are * set check for them and branch if at least one of them is set. 
        */
      uint16_t br_condition = (instr >> 9) & 0x07;

      /* Offset to branch from pc is found at first 9 bits of the instruction */
      uint16_t br_offset = instr & 0x01FF;

      if (br_condition & registers[R_FLAGS]) {
        registers[R_PC] += sign_extend(br_offset, 9);
      }        
      break;
    case OP_ADD:
      break;

    default:
      break;
    }
  
  }
}