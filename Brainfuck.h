#pragma once

#include <array>
#include <string>
#include <vector>

namespace brainfuck {

// This is the standard size of the Brainfuck data buffer.
static const size_t BF_DATA_SIZE = 30000;

class Brainfuck {
public:
  explicit Brainfuck(const std::string &instructions);
  virtual ~Brainfuck() = default;

  void run();
  void dumpState() const;

private:
  void execInstruction(char instruction);
  void incrPointer();
  void decrPointer();
  void incrData();
  void decrData();
  void outputData();
  void inputData();
  void loopBegin();
  void loopEnd();

  const std::string &instructions;
  size_t instructionPointer;
  std::array<char, BF_DATA_SIZE> data;
  size_t dataPointer;
  std::vector<size_t> loopStack;
};

class BrainfuckError : public std::runtime_error {
public:
  template <typename T>
  explicit BrainfuckError(T &&msg) : std::runtime_error(std::forward<T>(msg)) {}
  virtual ~BrainfuckError() = default;
};

} // namespace brainfuck
