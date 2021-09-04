#pragma once

#include <string>
#include <vector>

using Byte = char;
using Bytecode = std::vector<Byte>;

std::string BytecodeOpToString(const Byte* ip);