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

setNRE :: proc(mem: ^Mem, bit: bool){
  mem.nre = bit;

  if bit == true{ 
    for i in 0..<4{ mem.out[i] = .FL; }
    return; 
  }

  readdr_bit1 : bool = mem.readdr[0];
  readdr_bit2 : bool = mem.readdr[1];
  matrix_index : int = btoi(readdr_bit1, readdr_bit2);

  for i in 0..<4{
    if mem.mem[matrix_index][i] == false{
      mem.out[i] = .OFF;
      continue;
    }
    mem.out[i] = .ON;
  }
}

setWRADDR :: proc(mem: ^Mem, bit1: bool, bit2: bool){
  mem.wraddr[0] = bit1;
  mem.wraddr[1] = bit2;

  if mem.nwe == true{ return; }
  matrix_index1 := btoi(bit1, bit2);
  for i in 0..<4{
    mem.mem[matrix_index1][i] = mem.inp[i];
  }

  if mem.nre == true { return; }
  readdr_bit1 := mem.readdr[0];
  readdr_bit2 := mem.readdr[1];
  matrix_index2 := btoi(readdr_bit1, readdr_bit2);

  if matrix_index1 != matrix_index2{ return; }
  for i in 0..<4{
    mem.out[i] = .ON if mem.inp[i] == true else .OFF;
  }
}

setREADDR :: proc(mem: ^Mem, bit1: bool, bit2: bool){
  mem.readdr[0] = bit1;
  mem.readdr[1] = bit2;

  if mem.nre == true { return; }
  matrix_index := btoi(bit1, bit2);
  for i in 0..<4{
    mem.out[i] = .ON if mem.mem[matrix_index][i] == true else .OFF;
  }
}

setINP :: proc(mem: ^Mem, bit1: bool, bit2: bool, bit3: bool, bit4: bool){
  mem.inp[0] = bit1;
  mem.inp[1] = bit2;
  mem.inp[2] = bit3;
  mem.inp[3] = bit4;

  if mem.nwe == true { return; }

  wraddr_bit1 := mem.wraddr[0];
  wraddr_bit2 := mem.wraddr[1];
  matrix_index1 := btoi(wraddr_bit1, wraddr_bit2);

  mem.mem[matrix_index1][0] = bit1;
  mem.mem[matrix_index1][1] = bit2;
  mem.mem[matrix_index1][2] = bit3;
  mem.mem[matrix_index1][3] = bit4;

  if mem.nre == true { return; }

  readdr_bit1 := mem.readdr[0];
  readdr_bit2 := mem.readdr[1];
  matrix_index2 := btoi(readdr_bit1, readdr_bit2);

  if matrix_index1 != matrix_index2 { return; }

  mem.out[0] = .ON if bit1 == true else .OFF;
  mem.out[1] = .ON if bit2 == true else .OFF;
  mem.out[2] = .ON if bit3 == true else .OFF;
  mem.out[3] = .ON if bit4 == true else .OFF;
}

getOUT :: proc(mem: ^Mem) -> [4]Tristate{
  return mem.out;
}

main :: proc(){
  mem1 : Mem = memInit();
}
