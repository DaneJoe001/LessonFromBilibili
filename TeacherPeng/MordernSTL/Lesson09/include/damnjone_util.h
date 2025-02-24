#pragma once

#include <array>
#include <list>
#include <ostream>

namespace DamnJoneUtil
{
    template<class T>
    void print_array(std::ostream& os, const T& array, const std::string tip = "")
    {
        if (tip == "")
        {
            os << "Values in container: { ";
        }
        else
        {
            os << tip << ": { ";
        }
        std::size_t index = 0;
        std::size_t max_index = array.size() - 1;
        for (const auto& it : array)
        {
            index++;
            os << it;
            if (index <= max_index)
            {
                os << ',';
            }
        }
        os << " }" << std::endl;
    }

}
