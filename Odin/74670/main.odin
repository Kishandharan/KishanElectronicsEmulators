package main
import fmt "core:fmt"

Mem :: struct{
  inp: [4]bool,
  wraddr: [2]bool, 
  readdr: [2]bool,
  out: [4]Tristate,
  nwe: bool,
  nre: bool,
};

Tristate :: enum{
  ON, 
  OFF, 
  FL
};

memInit :: proc() -> Mem{
  mem : Mem;
  mem.inp = {false,false,false,false};
  mem.wraddr = {false,false};
  mem.readdr = {false,false};
  mem.out = {.FL, .FL, .FL, .FL};
  mem.nwe = true;
  mem.nre = true;
  return mem;
}

main :: proc(){
  mem1 : Mem = memInit();
  fmt.println("Initial State: ");
  fmt.println(mem1);
}

