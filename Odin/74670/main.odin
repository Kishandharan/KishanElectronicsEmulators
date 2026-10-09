package main
import fmt "core:fmt"

Mem :: struct{
  inp: [4]bool,
  wraddr: [2]bool, 
  readdr: [2]bool,
  out: [4]Tristate,
  nwe: bool,
  nre: bool,
  mem: [4][4]bool
};

Tristate :: enum{
  ON, 
  OFF, 
  FL
};

btoi :: proc(bit1 : bool, bit2 : bool) -> int{
  val : int = 0
  if !bit1 && !bit2{ val = 0; } 
  if !bit1 && bit2 { val = 1; }
  if bit1 && !bit2 { val = 2; }
  if bit1 && bit2 { val = 3; }
  return val;
}

memInit :: proc() -> Mem{
  mem : Mem;
  mem.inp = {false,false,false,false};
  mem.wraddr = {false,false};
  mem.readdr = {false,false};
  mem.out = {.FL, .FL, .FL, .FL};
  mem.nwe = true;
  mem.nre = true;
  for i in 0..<4{
    for j in 0..<4{
      mem.mem[i][j] = false;
    }
  }
  return mem;
}

setNWE :: proc(mem: ^Mem, bit: bool){
  mem.nwe = bit;
  if bit == true{ return; }
  wraddr_bit1 : bool =  mem.wraddr[0];
  wraddr_bit2 : bool =  mem.wraddr[1];
  matrix_index1 : int = btoi(wraddr_bit1, wraddr_bit2);

  for i in 0..<4{
    mem.mem[matrix_index1][i] = mem.inp[i];
  }

  if mem.nre == true{ return; }
  readdr_bit1 : bool = mem.readdr[0];
  readdr_bit2 : bool = mem.readdr[1];
  matrix_index2 : int = btoi(readdr_bit1, readdr_bit2);

  if matrix_index1 != matrix_index2{ return; }

  for i in 0..<4{

    if mem.mem[matrix_index2][i]{
      mem.out[i] = .ON;
      continue;
    }
    mem.out[i] = .OFF;

  }
}

main :: proc(){
  mem1 : Mem = memInit();

  mem1.inp[0] = true;
  mem1.inp[1] = true;
  mem1.inp[2] = true;
  mem1.inp[3] = true;
  mem1.nre = false;

  mem1.readdr[0] = true;
  mem1.readdr[1] = true;

  setNWE(&mem1, false);

  fmt.println(mem1.mem);
  fmt.println(mem1.out);
}

