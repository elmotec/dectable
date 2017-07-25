#ifndef INC_DECTABLE_H_DWBO4EHS
#define INC_DECTABLE_H_DWBO4EHS

#include <vector>
#include <string>
#include <iosfwd>
#include "dectable/Rule.h"

namespace dectable
{

    typedef std::vector<Rule> DecisionTable;

    /// Simple input for DecisionTable.
    std::istream & operator>>(std::istream &, DecisionTable &);
    /// Simple output for DecisionTable.
    std::ostream & operator<<(std::ostream &, const DecisionTable &);

    /// Find the first rule, if any, that matches the candidate.
    /** Modeled after std::find_if */
    DecisionTable::const_iterator FindFirstMatch(DecisionTable::const_iterator begin, DecisionTable::const_iterator end, const RuleInput & candidate);

    /// True if the candidate rule input matches the reference.
    bool IsMatch(const RuleInput & reference, const RuleInput & candidate);

}  // namespace dectable

#endif /* end of include guard: INC_DECTABLE_H_DWBO4EHS */
