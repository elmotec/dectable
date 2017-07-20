#include "dectable/Rule.h"
#include <cassert>

namespace dectable
{

    /** Defaults:
     *
     *  matchAny is * */
    RuleConfiguration::RuleConfiguration():
        matchAny("*")
    {}

    RuleConfiguration & Rule::Configuration()
    {
        static RuleConfiguration config;
        return config;
    }

    Rule::Rule()
    {}

    Rule::Rule(const RuleInput & input,
            const RuleOutput & output)
        : input_(input), output_(output)
    {}

    Rule::Rule(const RuleInput & input)
        : input_(input)

    {}

    Rule::~Rule()
    {}

    const RuleOutput & Rule::GetOutput() const
    {
        return output_;
    }

    /** Find out if there is a match between the 2 rule inputs.
     *
     *  Loops through the input fields. If any difference is found,
     *  other than the RuleConfiguration::matchAny special string,
     *  returnfalse.
     *
     *  Otherwise return true, meaning we found a match.
     *
     *  Note that the Rule is ordered so std::find will return the first
     *  rule for which there is a match.
     *
     *  */
    bool Rule::operator==(const Rule & other) const
    {
        const RuleConfiguration & config = Rule::Configuration();
        assert(input_.size() == other.input_.size());
        for (size_t ii = 0; ii < input_.size(); ++ii)
        {
            if (input_[ii] != config.matchAny &&
                    other.input_[ii] != config.matchAny && 
                    input_[ii] != other.input_[ii])
            {
                return false;
            }
        }
        return true;
    }

    bool Rule::operator!=(const Rule & other) const
    {
        return ! (*this == other);
    }

} /* dectable */ 
