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

/*
 * Parser super class, provide an interface for file IO
 * TODO: DO __NOT__ assume everyone is using little-endian
 */
class Parser {
 public:
  Parser(const std::string &path, std::ios_base::openmode mode);
  ~Parser();

  bool Good() noexcept;
  void Skip(uint32_t n) noexcept;
  void SeekG(uint32_t pos) noexcept;
  void SeekP(uint32_t pos) noexcept;
  uint32_t TellG() noexcept;

  template <typename T>
  T Get() noexcept;
  template <typename T, size_t n>
  std::array<T, n> Get() noexcept;

  template <typename T>
  std::vector<T> GetToEOF() noexcept;
  std::wstring GetUTF16Str(size_t len) noexcept;
  char16_t GetUTF16() noexcept;
  std::string GetLine() noexcept;

  template <typename T>
  void Write(T data) noexcept;
  template <typename T, size_t n>
  void Write(const std::array<T, n> &data) noexcept;

 private:
  std::fstream stream;
};

template <typename T>
T Parser::Get() noexcept {
  T data;
  stream.read(reinterpret_cast<char *>(&data), sizeof(data));

  if (!Good()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to read from file \n";
  }
  return data;
}

template <typename T, size_t n>
std::array<T, n> Parser::Get() noexcept {
  std::array<T, n> data;
  for (auto &i : data) {
    i = Get<T>();
  }
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

template <typename T, size_t n>
void Parser::Write(const std::array<T, n> &data) noexcept {
  std::for_each(data.begin(), data.end(), Write<T>());
}

template <typename T>
void Parser::Write(T data) noexcept {
  stream.write(reinterpret_cast<char *>(&data), sizeof(T));
  if (!Good()) {
    System::Logger::error(System::Subsystem::PARSERS)
        << "failed to write to file \n";
  }
}

}  // namespace Parsers
}  // namespace Sourcehold
