#pragma once

#include <assert.h>

#include <algorithm>
#include <array>
#include <cinttypes>
#include <codecvt>
#include <fstream>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

#include "System/Logger.h"

namespace Sourcehold {
namespace Parsers {

// Noexcept std::fstream wrapper.
// Handles read and write operations on a file.
// Loggs errors to std output
class Parser {
 public:
  // Creates and opens a fstream at path with mode
  Parser(const std::string &path, std::ios_base::openmode mode);
  // Closes the fstream
  ~Parser();
  // The following functions resemble fstream counterparts
  void Skip(uint32_t n) noexcept;
  void SeekG(uint32_t pos) noexcept;
  void SeekP(uint32_t pos) noexcept;
  uint32_t TellG() noexcept;

  // Reads T from stream.
  // reinterpret_cast from T to char*
  template <typename T>
  T Get() noexcept;
  template <typename T, bool reversed = false>
  std::vector<T> Get(size_t n) noexcept;
  template <typename T, size_t n, bool reversed = false>
  std::array<T, n> Get() noexcept;
  template <typename T>
  std::vector<T> GetToEOF() noexcept;

  std::string GetLine() noexcept;

  // Writes T to stream
  // reinterpret_cast from T to char*
  template <typename T>
  void Write(T data) noexcept;
  template <typename T, size_t n>
  void Write(const std::array<T, n> &data) noexcept;

 private:
  std::fstream stream;
};
//***************************
//**Template implementation**
//***************************
template <typename T>
T Parser::Get() noexcept {
  T data;
  stream.read(reinterpret_cast<char *>(&data), sizeof(data));
  // Logging
  if (stream.bad()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to read from file \n";
  }
  return data;
}

template <typename T, bool reversed>
std::vector<T> Parser::Get(size_t n) noexcept {
  std::vector<T> data(n);

  reversed
      ? std::generate(data.rbegin(), data.rend(), [&]() { return Get<T>(); })
      : std::generate(data.begin(), data.end(), [&]() { return Get<T>(); });
  return data;
}
template <typename T, size_t n, bool reversed>
std::array<T, n> Parser::Get() noexcept {
  std::array<T, n> data;

  reversed
      ? std::generate(data.rbegin(), data.rend(), [&]() { return Get<T>(); })
      : std::generate(data.begin(), data.end(), [&]() { return Get<T>(); });
  return data;
}
template <typename T>
std::vector<T> Parser::GetToEOF() noexcept {
  std::vector<T> result;
  std::transform(std::istream_iterator<uint8_t>(stream),  //
                 std::istream_iterator<uint8_t>(),        //
                 std::back_inserter(result),              //
                 Get<T>());
  return result;
}

template <typename T>
void Parser::Write(T data) noexcept {
  stream.write(reinterpret_cast<char *>(&data), sizeof(T));
  // Logging
  if (stream.bad()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to write to file \n";
  }
}
template <typename T, size_t n>
void Parser::Write(const std::array<T, n> &data) noexcept {
  for (auto &i : data) {
    Write<T>(i);
  }
}
}  // namespace Parsers
}  // namespace Sourcehold
