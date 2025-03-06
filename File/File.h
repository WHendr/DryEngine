#pragma once
#include <vector>
#include <string>

#include <iostream>
#include <fstream>

namespace Dry::File
{

class File
{
public:
    static std::vector<char> readFile(const std::string& filename);
};

}
