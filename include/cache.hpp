// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_CACHE_HPP
#define INCLUDE_CACHE_HPP

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <chrono>
#include <vector>
#include <algorithm>
#include <random>

#define STEP 16
#define ZERO std::chrono::nanoseconds::zero()

typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::nanoseconds ns;
typedef std::chrono::duration<float> diffFloat;

struct researchTimes {
  int tempValue;
  ns time;
};

/* Intel Core i7-10510U
 * cache_sizes['1'] = 256 KB
 * cache_sizes['2'] = 1024 KB
 * cache_sizes['3'] = 8192 KB
 * 128 KB < 256 KB < 1024 KB < 6144 KB < 12288 KB
 */

auto example() -> void;

void forwardResearch(const int* in, size_t inSize, researchTimes* times);

void backwardResearch(const int* in, size_t inSize, researchTimes* times);

void randomResearch(const int* in, size_t inSize, researchTimes* times);

void experiment(size_t bufferSize, size_t number, researchTimes* times);

void fullExperiment();

#endif  // INCLUDE_CACHE_HPP
