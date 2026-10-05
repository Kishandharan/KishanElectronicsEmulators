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

  if(!nLT || !nBL || LE) return;

  // TODO: Put code here for calculating the right 7-Seg Input Combination
}

int main(){
  
}
