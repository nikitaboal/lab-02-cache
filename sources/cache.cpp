// Copyright 2021 Your Name <your_email>

#include <cache.hpp>

static unsigned int seed = 11111;

auto example() -> void
{
  throw std::runtime_error("not implemented");
}

void forwardResearch(const int* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      times->tempValue = in[j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void backwardResearch(const int* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  auto startPoint = Time::now();

  for (size_t i = 0; i < 1000; i++)
  {
    for (size_t j = 0; j < inSize; j += STEP)
    {
      times->tempValue = in[inSize - j];
    }
  }

  auto stopPoint = Time::now();
  diffFloat diff = startPoint - stopPoint;
  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void randomResearch(const int* in, size_t inSize, researchTimes* times)
{
  for (size_t i = 0; i < inSize; i += STEP)
  {
    times->tempValue = in[i];
  }

  size_t counter = inSize / STEP;

  std::vector<int> index(inSize);
  for (size_t i = 0; i < counter; i++)
  {
    index[i] = static_cast<int>(i * STEP);
  }

  diffFloat diff;
  for (size_t i = 0; i < 1000; i++)
  {
    random_shuffle(index.begin(), index.end());

    auto startPoint = Time::now();
    for (size_t j = 0; j < counter; j++)
    {
      times->tempValue = in[index[j]];
    }
    auto stopPoint = Time::now();
    diff += startPoint - stopPoint;
  }

  times->time = std::chrono::duration_cast<ns>(abs(diff / 1000));
}

void experiment(size_t bufferSize, size_t number, researchTimes* times)
{
  std::cout << "\t- experiment:\n" << "\t\tnumber: " << number << std::endl
            << "\t\tinput_data:\n" << "\t\t\tbuffer_size:" << bufferSize<<"byte"
            << std::endl << "\t\tresults:\n" <<  "\t\t\tduration: "
            << times->time.count() << " ns" << std::endl;
}

void fullExperiment()
{
  size_t bufferSizes[] = { 131072, 262144, 1048576, 6291456, 9437184 };
  researchTimes times = { 0, ZERO };

  std::cout << "investigation:\n" << "\ttravel_variant: Forward\n"
            << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = new int[bufferSizes[i]];
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed);
    }
    forwardResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
  }

  std::cout << "\ttravel_variant: Backward\n"
            << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = new int[bufferSizes[i]];
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed);
    }
    backwardResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
  }

  std::cout << "\ttravel_variant: Random\n"
            << "\texperiments:" << std::endl;

  for (size_t i = 0; i < 5; i++)
  {
    auto* array = new int[bufferSizes[i]];
    for (size_t j = 0; j < bufferSizes[i]; j++)
    {
      array[j] = rand_r(&seed);
    }
    randomResearch(array, bufferSizes[i], &times);
    experiment(bufferSizes[i], i + 1, &times);
  }
}
// dgh
// ds
