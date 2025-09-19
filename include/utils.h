#pragma once
#ifndef UTILS_H
#define UTILS_H

#include <cstdlib>
#include <vector>
#include <string>

int discretize_state(const std::vector<double>& state);

std::string action_label(int action);

#endif 
