#include "dectable/DecisionTable.h"
#include <vector>
#include <sstream>

namespace dectable
{
    using namespace ::std;

    std::istream & operator>>(std::istream & is, DecisionTable &)
    {
        return is;
    }

    std::ostream & operator<<(std::ostream & os, const DecisionTable &)
    {
        return os;
    }

}  // dectable
