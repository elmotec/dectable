/** Copyright (c) 2017 elmotec. See LICENSE */

#include "dectable/Rule.h"
#include <cassert>
#include <iostream>

namespace dectable
{

    using namespace ::std;

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

    Rule::~Rule()
    {}

    bool Rule::operator==(const Rule & other) const
    {
        return input_ == other.input_ && output_ == other.output_;
    }

    bool Rule::operator!=(const Rule & other) const
    {
        return ! (*this == other);
    }

    istream & operator >> (istream & is, vector<string> & vec)
    {
        if (! is.good())
        {
            return is;
        }
        size_t size = 0;
        is >> size;
        if (! is.good())
        {
            return is;
        }
        vec.resize(size);
        for (size_t ii = 0; ii < vec.size(); ++ii)
        {
            if (is.good())
            {
                is >> vec[ii];
            }
        }
        return is;
    }

    ostream & operator << (ostream & os, const vector<string> & vec)
    {
        size_t vecSize = vec.size();
        os << vecSize << " ";
        for (size_t ii = 0; ii < vecSize; ++ii)
        {
            os << vec[ii];
            if (ii < vecSize - 1)
                os << " ";
        }
        return os;
    }

    istream & operator >> (istream & is, Rule & rule)
    {
        if (is.good())
        {
            is >> rule.input_;
            is >> rule.output_;
        }
        return is;
    }

    ostream & operator << (ostream & os, const Rule & rule)
    {
        if (os.good())
        {
            os << rule.input_ << " ";
            os << rule.output_;
        }
        return os;
    }

} /* dectable */ 
