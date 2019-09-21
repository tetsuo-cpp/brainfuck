#include "Brainfuck.h"

#include <fstream>
#include <iostream>

int main(int argc, char **argv) {
  if (argc != 2) {
    std::cerr << "Usage: ./brainfuck <source_file>\n";
    return EXIT_FAILURE;
  }
  const char *fileName = argv[1];
  std::ifstream file(fileName);
  if (!file) {
    std::cerr << "BRAINFUCK: Could not open source file \"" << fileName
              << "\".\n";
    return EXIT_FAILURE;
  }
  const std::string source((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
  brainfuck::Brainfuck bf(source);
  try {
    bf.run();
  } catch (const brainfuck::BrainfuckError &error) {
    std::cerr << "BRAINFUCK: " << error.what() << ".\n";
    bf.dumpState();
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
