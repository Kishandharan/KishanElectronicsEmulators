#include <stdio.h>

typedef struct icCD4511{
  bool a, b, c, d, e, f, g;
  bool nLT;
  bool nBL;
  bool LE;
} Converter;

Converter init(){
  Converter con1;
  con1.nLT = 1;
  con1.nBL = 1;
  con1.LE = 1;
  con1.a = 0;
  con1.b = 0;
  con1.c = 0;
  con1.d = 0;
  con1.e = 0;
  con1.f = 0;
  con1.g = 0;
}

void setINP(Converter *conv, bool bit1, bool bit2, bool bit3, bool bit4){
  bool nLT = conv->nLT;
  bool nBL = conv->nBL;
  bool LE = conv->LE;
  bool condFlag = 0;
  bool conds[] = {
    (!bit1 && !bit2 && !bit3 && !bit4), // 0000
    (!bit1 && !bit2 && !bit3 && bit4), // 0001
    (!bit1 && !bit2 && bit3 && !bit4), // 0010
    (!bit1 && !bit2 && bit3 && bit4), // 0011
    (!bit1 && bit2 && !bit3 && !bit4), // 0100
    (!bit1 && bit2 && !bit3 && bit4), // 0101
    (!bit1 && bit2 && bit3 && !bit4), // 0110
    (!bit1 && bit2 && bit3 && bit4), // 0111
    (bit1 && !bit2 && !bit3 && !bit4), // 1000
    (bit1 && !bit2 && !bit3 && bit4), // 1001
  };
  bool results[][] = {
    [1,1,1,1,1,1,0],
    [0,1,1,0,0,0,0],
    [1,1,0,1,1,0,1],
    [1,1,1,1,0,0,1],
    [0,1,1,0,0,1,1],
    [1,0,1,1,0,1,1],
    [1,0,1,1,1,1,1],
    [1,1,1,0,0,0,0],
    [1,1,1,1,1,1,1],
    [1,1,1,1,0,1,1]
  };

  if(!nLT || !nBL || LE) return;
  for(int i = 0; i < 10; i++){
    if(conds[i]){
      conv->a = results[i][0];
    }
  }
}

int main(){
  
}
