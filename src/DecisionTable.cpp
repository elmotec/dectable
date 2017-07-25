#include "dectable/DecisionTable.h"
#include <algorithm>
#include <cassert>
#include <functional>
#include <sstream>
#include <vector>

namespace dectable
{
    using namespace ::std;

    istream & operator>>(istream & is, DecisionTable & table)
    {
        size_t size = 0;
        if (! is.good())
        {
            return is;
        }
        is >> size;
        table.resize(size);
        size_t tableInputSizeSoFar = 0;
        size_t tableOutputSizeSoFar = 0;
        for (size_t ii = 0; ii < table.size(); ++ii)
        {
            if (is.good())
            {
                is >> table[ii];
            }
            size_t tableInputSize = table[ii].GetInput().size();
            size_t tableOutputSize = table[ii].GetOutput().size();
            if (ii != 0)
            {
                assert(tableInputSizeSoFar == tableInputSize);
                assert(tableOutputSizeSoFar == tableOutputSize);
            }
            else
            {
                tableInputSizeSoFar = tableInputSize;
                tableOutputSizeSoFar = tableOutputSize;
            }
        }
        return is;
    }

    ostream & operator<<(ostream & os, const DecisionTable & table)
    {
        os << table.size() << " ";
        for (size_t ii=0; ii < table.size(); ++ii)
        {
            os << table[ii] << " ";
        }
        return os;
    }

    /** Find out if there is a match between the 2 rule inputs.
     *
     *  Loops through the input fields. If any difference is found,
     *  other than the RuleConfiguration::matchAny special string,
     *  return false.
     *
     *  Otherwise return true, meaning we found a match.
     *
     *  Note that the Rule is ordered so std::find will return the first
     *  rule for which there is a match. One can use std::find_all to
     *  find all the rules that match.
     *
     *  */
    bool IsMatch(const RuleInput & reference, const RuleInput & candidate)
    {
        const RuleConfiguration & config = Rule::Configuration();
        assert(reference.size() == candidate.size());
        for (size_t ii = 0; ii < candidate.size(); ++ii)
        {
            if (reference[ii] != config.matchAny &&
                    reference[ii] != candidate[ii])
            {
                return false;
            }
        }
        return true;
    }

    class Matcher
    {
        public:
            Matcher(const RuleInput & candidate): candidate_(candidate)
            {}
            bool operator()(const Rule & rule) const
            { return IsMatch(rule.GetInput(), candidate_); }

        private:
            RuleInput candidate_;
    };

    /** Convenience wrapper to call IsMatch.
     *
     *  Forwards the call to std::find_if with appropriate wrapper.
     */
    DecisionTable::const_iterator FindFirstMatch(DecisionTable::const_iterator begin, DecisionTable::const_iterator end, const RuleInput & candidate)
    {
        Matcher isMatch(candidate);
        DecisionTable::const_iterator it = std::find_if(begin, end, isMatch);
        return it;
    }

}  // dectable
