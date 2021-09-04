#pragma once

#include <string>
#include <vector>

using Byte = char;
struct Executable
{
    std::vector<Byte> m_code;
};

std::string ExecutableOpToString(const Byte* ip);