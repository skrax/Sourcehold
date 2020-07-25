#include <Parsers/MlbFile.h>
#include <gtest/gtest.h>
constexpr auto pathToMlb = "../data/stronghold.mlb";
constexpr auto modeRead = std::ios_base::in | std::ios_base::binary;
TEST(MlbTest, mlbtest) {
  using namespace Sourcehold::Parsers;
  Parser mlb(pathToMlb, modeRead);
  auto result = Mlb::Load(mlb);
  for (auto& i : result) {
    std::cout << i << std::endl;
  }
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
