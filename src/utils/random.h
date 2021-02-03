#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include <vector>

namespace phillib
{

namespace utils
{

/**
 * @brief
 *
 * @param n
 * @param vals
 * @param threshN
 * @param threshP
 */
void randomInts(const unsigned int n, std::vector<int>& vals, const int threshN, const int threshP);

/**
 * @brief
 *
 * @param n
 * @param vals
 * @param threshN
 * @param threshP
 */
void randomReal(const unsigned int n, std::vector<float>& vals, const float threshN, const float threshP);

} // namespace utils

} // namespace phillib

#endif