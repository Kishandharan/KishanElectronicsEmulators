#include <stdio.h>

typedef struct ic74hc595{
  int outprime;
  int outfinal[8];

  bool out[8];
  bool buf[8];
  bool ser;
  bool noe;
  bool oclk;
  bool bclk;
  bool bclr;
} Expander;

Expander expanderInit(){
  Expander exp1;
  for(int i = 0; i < 8; i++){ 
    exp1.out[i] = 0; 
    exp1.buf[i] = 0; 
    exp1.outfinal[i] = 0; 
  }
  exp1.outprime = 1;
  exp1.ser = 0;
  exp1.noe = 0;
  exp1.oclk = 0;
  exp1.bclk = 0;
  exp1.bclr = 0;
  return exp1;
}

void setSER(Expander *exp, bool bit){
  exp->ser = bit;
}

void setBCLK(Expander *exp, bool bit){
  if(exp->bclr == 1){
    if(exp->bclk == 0 && bit == 1){
      exp->buf[7] = exp->buf[6];
      exp->buf[6] = exp->buf[5];
      exp->buf[5] = exp->buf[4];
      exp->buf[4] = exp->buf[3];
      exp->buf[3] = exp->buf[2];
      exp->buf[2] = exp->buf[1];
      exp->buf[1] = exp->buf[0];
      exp->buf[0] = exp->ser; 
    }
  }
  exp->bclk = bit;
}

void setOCLK(Expander *exp, bool bit){
  if(exp->oclk == 0 && bit == 1){
    for(int i = 0; i < 8; i++){
      exp->out[i] = exp->buf[i]; 
    }
    if(exp->noe == 0){
      for(int i = 0; i < 8; i++){
        exp->outfinal[i] = exp->out[i];
      }
      exp->outprime = !exp->outfinal[7];
    }
  }
  exp->oclk = bit;
}

void setBCLR(Expander *exp, bool bit){
  exp->bclr = bit;
  if(bit == 0){
    for(int i = 0; i < 8; i++){ exp->buf[i] = 0; }
  }
}

void setNOE(Expander *exp, bool bit){
  if(bit == 0){
    for(int i = 0; i < 8; i++){
      exp->outfinal[i] = exp->out[i];
    }
    exp->outprime = !exp->outfinal[7];
  }else{
    for(int i = 0; i < 8; i++){
      exp->outfinal[i] = -1;
    }
    exp->outprime = -1;
  }
  exp->noe = bit;
}

void printExpanderDetails(Expander *exp){
  printf("-----------------------------\n");
  printf("SER: %d\n", exp->ser);
  printf("nOE: %d\n", exp->noe);
  printf("OCLK: %d\n", exp->oclk);
  printf("BCLK: %d\n", exp->bclk);
  printf("BCLR: %d\n", exp->bclr);
  printf("BUF: %d%d%d%d%d%d%d%d\n", 
         exp->buf[0],
         exp->buf[1],
         exp->buf[2],
         exp->buf[3],
         exp->buf[4],
         exp->buf[5],
         exp->buf[6],
         exp->buf[7]
  );
  printf("OUT: %d%d%d%d%d%d%d%d\n", 
         exp->out[0],
         exp->out[1],
         exp->out[2],
         exp->out[3],
         exp->out[4],
         exp->out[5],
         exp->out[6],
         exp->out[7]
  );
  printf("OUT FINAL: %d %d %d %d %d %d %d %d\n", 
         exp->outfinal[0],
         exp->outfinal[1],
         exp->outfinal[2],
         exp->outfinal[3],
         exp->outfinal[4],
         exp->outfinal[5],
         exp->outfinal[6],
         exp->outfinal[7]
  );
  printf("OUT PRIME: %d\n", exp->outprime);
  printf("-----------------------------");
}

int main(){
  Expander exp1 = expanderInit();
  setBCLR(&exp1, 1); // Don't clear the First Buffer
  setNOE(&exp1, 1); // Clear the outputs to High-Impedance
  setBCLR(&exp1, 0);

  setSER(&exp1, 1);
  setBCLK(&exp1, 0);
  setBCLK(&exp1, 1);

  setSER(&exp1, 1);
  setBCLK(&exp1, 0);
  setBCLK(&exp1, 1);

  setSER(&exp1, 0);
  setBCLK(&exp1, 0);
  setBCLK(&exp1, 1);

  setOCLK(&exp1, 0);
  setOCLK(&exp1, 1);

  printExpanderDetails(&exp1);

  return 0;
}
