#include "Brainfuck.h"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: ./brainfuck <source_file>\n";
    return EXIT_FAILURE;
  }
  const char *fileName = argv[1];
  std::ifstream file(fileName);
  const std::string source((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
  brainfuck::Brainfuck bf(source);
  try {
    bf.run();
  } catch (const brainfuck::BrainfuckError &error) {
    std::cerr << "BRAINFUCK: " << error.what() << "\n";
    bf.dumpState();
  }
  return EXIT_SUCCESS;
}
