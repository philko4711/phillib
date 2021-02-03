
#include "random.h"

namespace phillib
{

namespace utils
{

void randomInts(const unsigned int n, std::vector<int>& vals, const int threshN, const int threshP)
{

  std::random_device              rd;
  std::default_random_engine      gen(rd());
  std::uniform_int_distribution<> dis(threshN, threshP);
  for(unsigned int i = 0; i < n; i++)
    vals.push_back(dis(gen));
}

void randomReal(const unsigned int n, std::vector<float>& vals, const float threshN, const float threshP)
{
  std::random_device               rd;
  std::default_random_engine       gen(rd());
  std::uniform_real_distribution<> dis(threshN, threshP);
  for(unsigned int i = 0; i < n; i++)
    vals.push_back(dis(gen));
}

} // namespace utils

} // namespace phillib