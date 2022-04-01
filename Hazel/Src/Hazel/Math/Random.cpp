#include "hzpch.h"
#include "Random.h"

std::mt19937 Hazel::Random::s_RandomEngine;
std::uniform_int_distribution<std::mt19937::result_type> Hazel::Random::s_Distribution;