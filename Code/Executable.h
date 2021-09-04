#pragma once

#include <string>
#include <vector>
#include "Value.h"

using Byte = char;
struct Executable
{
    std::vector<Byte> m_code;
    std::vector<Value> m_constants;
};

std::string ExecutableOpToString(const Byte* ip);