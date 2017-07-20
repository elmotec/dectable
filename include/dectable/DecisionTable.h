#ifndef INC_DECTABLE_H_DWBO4EHS
#define INC_DECTABLE_H_DWBO4EHS

#include <vector>
#include <string>
#include <iosfwd>
#include "dectable/Rule.h"

namespace dectable
{

    typedef std::vector<Rule> DecisionTable;

    /// Simple input for DecisionTable (loosely based on JSON).
    std::istream & operator>>(std::istream &, DecisionTable &);
    /// Simple output for DecisionTable (loosely based on JSON).
    std::ostream & operator<<(std::ostream &, const DecisionTable &);

}  // namespace dectable

#endif /* end of include guard: INC_DECTABLE_H_DWBO4EHS */
