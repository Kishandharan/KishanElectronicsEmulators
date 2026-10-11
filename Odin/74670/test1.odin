package main 
import rfile "RegisterFile"
import fmt "core:fmt"

main :: proc(){
  rfile1 : rfile.Mem = rfile.memInit();

  rfile.setINP(&rfile1, true, false, true, true);
  rfile.setWRADDR(&rfile1, false, true);
  rfile.setREADDR(&rfile1, true, true);
  rfile.setNWE(&rfile1, false);
  rfile.setNRE(&rfile1, false);
  rfile.printMem(rfile1);
}
