#include <stdio.h>

typedef struct icCD4511{
  bool a, b, c, d, e, f, g;
  bool latch[7];
  bool nLT;
  bool nBL;
  bool LE;
} Converter;

Converter init(){
  Converter con1;
  for(int i = 0; i < 7; i++){con1.latch[i] = 0;}
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
  if(conv->LE == 0){
    if(bit1 == 0 && bit2 == 0 && bit3 == 0 && bit4 == 0){
      conv->latch[0] = 1;
      conv->latch[1] = 1;
      conv->latch[2] = 1;
      conv->latch[3] = 1;
      conv->latch[4] = 1;
      conv->latch[5] = 1;
      conv->latch[6] = 0;
    }
  }
}

int main(){
  
}
