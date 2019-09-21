#include "Brainfuck.h"

#include <iostream>

namespace brainfuck {

Brainfuck::Brainfuck(const std::string &instructions)
    : instructions(instructions), instructionPointer(0), dataPointer(0) {
  data.fill(0);
}

void Brainfuck::run() {
  while (instructionPointer < instructions.size())
    execInstruction(instructions.at(instructionPointer));
}

void Brainfuck::execInstruction(char instruction) {
  switch (instruction) {
  case '>':
    incrPointer();
    break;
  case '<':
    decrPointer();
    break;
  case '+':
    incrData();
    break;
  case '-':
    decrData();
    break;
  case '.':
    outputData();
    break;
  case ',':
    inputData();
    break;
  case '[':
    loopBegin();
    break;
  case ']':
    loopEnd();
    break;
  default:
    // Brainfuck skips unrecognised instructions without complaining.
    break;
  }
  ++instructionPointer;
}

void Brainfuck::incrPointer() {
  if (++dataPointer >= data.size())
    throw BrainfuckError("incremented data pointer out of bounds");
}

void Brainfuck::decrPointer() {
  if (dataPointer-- == 0)
    throw BrainfuckError("decremented data pointer out of bounds");
}

void Brainfuck::incrData() {
  assert(dataPointer < data.size());
  ++data.at(dataPointer);
}

void Brainfuck::decrData() {
  assert(dataPointer < data.size());
  --data.at(dataPointer);
}

void Brainfuck::outputData() {
  assert(dataPointer < data.size());
  std::cout << data.at(dataPointer);
}

void Brainfuck::inputData() {
  assert(dataPointer < data.size());
  std::cin >> data.at(dataPointer);
}

void Brainfuck::loopBegin() {
  assert(dataPointer < data.size());
  assert(instructionPointer < instructions.size());
  if (data.at(dataPointer) != 0) {
    loopStack.push_back(instructionPointer);
    return;
  }
  // Save my poor fingers.
  const auto guardIncrInstructionPointer = [this]() {
    if (++instructionPointer > instructions.size())
      throw BrainfuckError("incremented instruction pointer out of bounds "
                           "while looking for loop end");
  };
  // We're trying to find the corresponding end loop command.
  // But we can have nested loops so make sure we're aware of that.
  guardIncrInstructionPointer();
  int stackSize = 0;
  char currentInstruction;
  while (currentInstruction = instructions.at(instructionPointer),
         currentInstruction != ']' || stackSize != 0) {
    assert(stackSize >= 0);
    if (currentInstruction == '[')
      ++stackSize;
    if (currentInstruction == ']')
      --stackSize;
    guardIncrInstructionPointer();
  }
}

void Brainfuck::loopEnd() {
  if (loopStack.empty())
    throw BrainfuckError(
        "encountered loop end without a corresponding loop begin");
  assert(dataPointer < data.size());
  if (data.at(dataPointer) == 0) {
    loopStack.pop_back();
    return;
  }
  instructionPointer = loopStack.back();
  assert(instructionPointer < instructions.size());
}

void Brainfuck::dumpState() const {
  static const size_t BF_DUMP_LINE_LENGTH = 20;
  for (size_t i = 0; i < instructions.size(); ++i) {
    if (i != 0 && i % BF_DUMP_LINE_LENGTH == 0)
      std::cout << "\n";
    if (instructionPointer == i)
      std::cout << "(" << instructions.at(i) << ")";
    else
      std::cout << " " << instructions.at(i) << " ";
  }
  std::cout << "\n";
}

} // namespace brainfuck
