#include "Parsers/Parser.h"

Sourcehold::Parsers::Parser::Parser(const std::string &path,
                                    std::ios_base::openmode mode) {
  stream.open(path, mode);
  // Logging
  if (stream.bad()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to open file at " << path << " with mode " << mode << '\n';
  }
}
Sourcehold::Parsers::Parser::~Parser() {
  assert(stream.is_open());

  stream.close();
}

void Sourcehold::Parsers::Parser::Skip(uint32_t n) noexcept {
  stream.seekg(n, std::ios_base::cur);
}

void Sourcehold::Parsers::Parser::SeekG(uint32_t pos) noexcept {
  stream.seekg(pos, std::ios_base::beg);
}

void Sourcehold::Parsers::Parser::SeekP(uint32_t pos) noexcept {
  stream.seekp(pos, std::ios_base::beg);
}

uint32_t Sourcehold::Parsers::Parser::TellG() noexcept {
  return stream.tellg();
}

std::string Sourcehold::Parsers::Parser::GetLine() noexcept {
  std::string line;
  std::getline(stream, line);
  // Logging
  if (stream.bad()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to read line from file \n";
  }
  return line;
}
