#include "Parsers/Parser.h"

#include <gtest/gtest.h>

#include <ios>

using namespace Sourcehold::Parsers;

//! TODO
//! Should we add this to the startup config ?
const std::string testsDir = "../tests/data/parser/";

TEST(ParserTest, Constructor) {
  auto file = testsDir + "mock0.hex";
  auto mode = std::ios_base::in | std::ios_base::binary;

  Parser parser(file, mode);
  EXPECT_TRUE(parser.Good());
  // TODO
  // Catch parser destructor assert, when open failed.
  // Parser parserFail(file + ".fail", mode);
  // EXPECT_FALSE(parserFail.Good());
  //
  // EXPECT_DEATH(parserFail,
  //              "Assertion failed: (stream.is_open()), function ~Parser");
}

TEST(ParserTest, GetByte) {
  auto file = testsDir + "mock0.hex";
  auto mode = std::ios_base::in | std::ios_base::binary;
  auto groundtruth = uint8_t{0x12};

  Parser parser(file, mode);
  auto candidate = parser.Get<uint8_t>();
  EXPECT_EQ(candidate, groundtruth);
}
TEST(ParserTest, GetWord) {
  auto file = testsDir + "mock0.hex";
  auto mode = std::ios_base::in | std::ios_base::binary;
  auto groundtruth = uint16_t{0x3412};

  Parser parser(file, mode);
  auto candidate = parser.Get<uint16_t>();
  EXPECT_EQ(candidate, groundtruth);
}
TEST(ParserTest, GetBytes) {
  auto file = testsDir + "mock0.hex";
  auto mode = std::ios_base::in | std::ios_base::binary;
  auto groundtruth = std::array<uint8_t, 3>{0x12, 0x34, 0x56};

  Parser parser(file, mode);
  auto candidate = parser.Get<uint8_t, 3>();

  for (auto i = 0; i < groundtruth.size(); ++i) {
    EXPECT_EQ(candidate[i], groundtruth[i]);
  }
}
TEST(ParserTest, WriteByte) {
  auto file = testsDir + "mock1.hex";
  auto mode = std::ios_base::in | std::ios_base::out | std::ios_base::binary;
  auto groundtruth = uint8_t{0x42};

  Parser parser(file, mode);
  parser.Write<uint8_t>(groundtruth);

  auto candidate = parser.Get<uint8_t>();

  EXPECT_EQ(candidate, groundtruth);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
