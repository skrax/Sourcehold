#include "Parsers/Parser.h"

Sourcehold::Parsers::Parser::Parser(const std::string &path,
                                    std::ios_base::openmode mode) {
  // open file at path
  stream.open(path, mode);
  if (!stream.good()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to open file at " << path << " with mode " << mode << '\n';
  }
}
Sourcehold::Parsers::Parser::~Parser() {
  assert(stream.is_open());

  stream.close();
}

bool Sourcehold::Parsers::Parser::Good() noexcept {
  return stream.good();
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

std::wstring Sourcehold::Parsers::Parser::GetUTF16Str(size_t len) noexcept {
  std::wstring ws;
  ws.reserve(len);

  for (auto &s : ws) {
    s = GetUTF16();
  }
  return ws;
}

char16_t Sourcehold::Parsers::Parser::GetUTF16() noexcept {
  auto hi = Get<char>();
  auto lo = Get<char>();

  auto utf16 = hi << 8 | lo;
  return utf16;
}

std::string Sourcehold::Parsers::Parser::GetLine() noexcept {
  std::string line;
  std::getline(stream, line);
  if (!Good()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to read line from file \n";
  }
  return line;
}
