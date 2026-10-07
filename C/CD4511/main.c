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
  return con1;
}

void setINP(Converter *conv, bool bit1, bool bit2, bool bit3, bool bit4){
  if(!nLT || !nBL || LE) return;

  // Code to be run if nLT and nBL is 0, and LE is 1
  bool nLT = conv->nLT;
  bool nBL = conv->nBL;
  bool LE = conv->LE;
  bool condFlag = 0;
  bool conds[] = {
    (!bit1 && !bit2 && !bit3 && !bit4),
    (!bit1 && !bit2 && !bit3 && bit4),
    (!bit1 && !bit2 && bit3 && !bit4),
    (!bit1 && !bit2 && bit3 && bit4),
    (!bit1 && bit2 && !bit3 && !bit4),
    (!bit1 && bit2 && !bit3 && bit4),
    (!bit1 && bit2 && bit3 && !bit4),
    (!bit1 && bit2 && bit3 && bit4),
    (bit1 && !bit2 && !bit3 && !bit4),
    (bit1 && !bit2 && !bit3 && bit4),
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

  for(int i = 0; i < 10; i++){
    if(conds[i]){
      conv->a = results[i][0];
      conv->b = results[i][1];
      conv->c = results[i][2];
      conv->d = results[i][3];
      conv->e = results[i][4];
      conv->f = results[i][5];
      conv->g = results[i][6];
      condFlag = true;
      break;
    }else{
      condFlag = false;
    }
  }
  if(!condFlag){
    conv->a = 0;
    conv->b = 0;
    conv->c = 0;
    conv->d = 0;
    conv->e = 0;
    conv->f = 0;
    conv->g = 0;
  }
}


int main(){
  
}
