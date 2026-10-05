#include <stdio.h>

typedef struct ic74hc670{
  bool WR_ADDR[2];
  bool RE_ADDR[2];
  bool MEMORY[4][4];
  bool DATA[4];
  int OUT[4]; 
  bool nWE;
  bool nRE;
} MEM;

MEM memInit(){
  MEM mem;
  mem.WR_ADDR[0] = 0;
  mem.WR_ADDR[1] = 0;
  mem.RE_ADDR[0] = 0;
  mem.RE_ADDR[1] = 0;
  for(int i = 0; i < 4; i++){
    for(int j = 0; j < 4; j++){
      mem.MEMORY[i][j] = 0;
    }
  }
  mem.DATA[0] = 0;
  mem.DATA[1] = 0;
  mem.DATA[2] = 0;
  mem.DATA[3] = 0;
  mem.OUT[0] = -1;
  mem.OUT[1] = -1;
  mem.OUT[2] = -1;
  mem.OUT[3] = -1;
  mem.nWE = 1;
  mem.nRE = 1;
  return mem;
}

int btoi(bool bit1, bool bit2){
  int result = 0;

  if(bit1 == 0 && bit2 == 0){ result = 0;}
  else if(bit1 == 0 && bit2 == 1){ result = 1; }
  else if(bit1 == 1 && bit2 == 0){ result = 2; }
  else if(bit1 == 1 && bit2 == 1){ result = 3; }

  return result;
}

void setWrAddr(MEM *mem, bool bit1, bool bit2){
  int readNum = 0;

  mem->WR_ADDR[0] = bit1;
  mem->WR_ADDR[1] = bit2;
  
  if(mem->nWE == 0){
    readNum = btoi(bit1, bit2);
    mem->MEMORY[readNum][0] = mem->DATA[0];
    mem->MEMORY[readNum][1] = mem->DATA[1];
    mem->MEMORY[readNum][2] = mem->DATA[2];
    mem->MEMORY[readNum][3] = mem->DATA[3];
  }

  if(mem->nRE == 0){
    if(mem->RE_ADDR[0] == bit1 && mem->RE_ADDR[1] == bit2){
      mem->OUT[0] = mem->MEMORY[readNum][0];
      mem->OUT[1] = mem->MEMORY[readNum][1];
      mem->OUT[2] = mem->MEMORY[readNum][2];
      mem->OUT[3] = mem->MEMORY[readNum][3];
    }
  }
}

void setReAddr(MEM *mem, bool bit1, bool bit2){
  mem->RE_ADDR[0] = bit1;
  mem->RE_ADDR[1] = bit2;

  if((mem->nRE) == 0){
     mem->OUT[0] = mem->MEMORY[btoi(bit1, bit2)][0];
     mem->OUT[1] = mem->MEMORY[btoi(bit1, bit2)][1];
     mem->OUT[2] = mem->MEMORY[btoi(bit1, bit2)][2];
     mem->OUT[3] = mem->MEMORY[btoi(bit1, bit2)][3];
  }
}

void setNRE(MEM *mem, bool new_nRE){
  mem->nRE = new_nRE;
  if(new_nRE == 1){
    mem->OUT[0] = -1;
    mem->OUT[1] = -1;
    mem->OUT[2] = -1;
    mem->OUT[3] = -1;
    return;
  }

  mem->OUT[0] = mem->MEMORY[btoi(mem->RE_ADDR[0], mem->RE_ADDR[1])][0];
  mem->OUT[1] = mem->MEMORY[btoi(mem->RE_ADDR[0], mem->RE_ADDR[1])][1];
  mem->OUT[2] = mem->MEMORY[btoi(mem->RE_ADDR[0], mem->RE_ADDR[1])][2];
  mem->OUT[3] = mem->MEMORY[btoi(mem->RE_ADDR[0], mem->RE_ADDR[1])][3];
}

void setNWE(MEM *mem, bool new_nWE){
  mem->nWE = new_nWE;
  if(new_nWE == 0){
    mem->MEMORY[btoi(mem->WR_ADDR[0], mem->WR_ADDR[1])][0] = mem->DATA[0];
    mem->MEMORY[btoi(mem->WR_ADDR[0], mem->WR_ADDR[1])][1] = mem->DATA[1];
    mem->MEMORY[btoi(mem->WR_ADDR[0], mem->WR_ADDR[1])][2] = mem->DATA[2];
    mem->MEMORY[btoi(mem->WR_ADDR[0], mem->WR_ADDR[1])][3] = mem->DATA[3];

    bool cond1 = mem->WR_ADDR[0] == mem->RE_ADDR[0];
    bool cond2 = mem->WR_ADDR[1] == mem->RE_ADDR[1];
    bool cond3 = cond1 && cond2;
    if(cond3){
        mem->OUT[0] = mem->DATA[0];
        mem->OUT[1] = mem->DATA[1];
        mem->OUT[2] = mem->DATA[2];
        mem->OUT[3] = mem->DATA[3];
    }
  }
}

void setDATA(MEM *mem, bool bit1, bool bit2, bool bit3, bool bit4){
  int writeNum = 0;

  mem->DATA[0] = bit1;
  mem->DATA[1] = bit2;
  mem->DATA[2] = bit3;
  mem->DATA[3] = bit4;

  if(mem->nWE == 0){
    writeNum = btoi(mem->WR_ADDR[0], mem->WR_ADDR[1]);
    mem->MEMORY[writeNum][0] = bit1;
    mem->MEMORY[writeNum][1] = bit2;
    mem->MEMORY[writeNum][2] = bit3;
    mem->MEMORY[writeNum][3] = bit4;

    if(mem->nRE == 0){
      bool cond1 = mem->WR_ADDR[0] == mem->RE_ADDR[0];
      bool cond2 = mem->WR_ADDR[1] == mem->RE_ADDR[1];
      bool cond3 = cond1 && cond2;
      if(cond3){
        mem->OUT[0] = bit1;
        mem->OUT[1] = bit2;
        mem->OUT[2] = bit3;
        mem->OUT[3] = bit4;
      }
    }
  }
}

int main(){
  MEM mem = memInit();

  setWrAddr(&mem, 0, 0);
  setReAddr(&mem, 0, 0);
  setDATA(&mem, 1, 1, 1, 1);
  setNRE(&mem, 0);
  setNWE(&mem, 0);
  setNWE(&mem, 1);

  printf("%d", mem.MEMORY[0][0]);
  printf("%d", mem.MEMORY[0][1]);
  printf("%d", mem.MEMORY[0][2]);
  printf("%d\n", mem.MEMORY[0][3]);

  printf("%d", mem.OUT[0]);
  printf("%d", mem.OUT[1]);
  printf("%d", mem.OUT[2]);
  printf("%d", mem.OUT[3]);

  return 0;
}
