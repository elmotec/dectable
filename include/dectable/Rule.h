#ifndef INC_RULE_H_AOX9VTDR
#define INC_RULE_H_AOX9VTDR

/** Copyright (c) 2017 elmotec. See LICENSE */

#include <vector>
#include <string>
#include <iosfwd>

namespace dectable
{

    typedef std::vector<std::string> RuleInput;
    typedef std::vector<std::string> RuleOutput;

    /// Input operator for RuleInput and RuleOutput. dectable specific.
    std::istream & operator >> (std::istream &, std::vector<std::string> &);
    /// Output operator for RuleInput and RuleOutput. dectable specific.
    std::ostream & operator << (std::ostream &, const std::vector<std::string> &);

    /** @brief Configuration for rule matching. */
    class RuleConfiguration
    {
        public:
            /// Default constructor determines default values.
            RuleConfiguration();
            /// Special string that will match any input.
            std::string matchAny;
    };

    /** @brief Representation of a decision table rule
     *
     *  Each rule is defined by RuleInput and a RuleOutput.
     *
     *  The DecisionTable will try to match the RuleInput passed to
     *  the DecisionTable. Use std::find in <algorithm> to look up
     *  the match, then GetOutput() to get the output.
     *
     *  For instance:
     *  auto it = std::find(table_.begin(), table_.end(), RuleInput(1, "some"));
     *  assert(it != table_.end());  // no match
     *  const RuleOutput & match = it->GetOutput();
     */
    class Rule
    {
    public:
        Rule ();
        /// Instances of Rule will be built off this constructor.
        Rule (const RuleInput & input, const RuleOutput & output);
        virtual ~Rule ();

        /// Access to the Rule configuration.
        static RuleConfiguration & Configuration();

        /// Compare the definition of the rule. True if rules are identical.
        bool operator==(const Rule &) const;
        /// Compare the definition of the rule. True if rules are different.
        bool operator!=(const Rule &) const;

        const RuleOutput & GetOutput() const
        { return output_; }
        void SetOutput(const RuleOutput & ruleOutput)
        { output_ = ruleOutput; }
        const RuleOutput & GetInput() const
        { return input_; }
        void SetInput(const RuleInput & ruleInput)
        { input_ = ruleInput; }

        friend std::istream & operator >> (std::istream &, Rule &);
        friend std::ostream & operator << (std::ostream &, const Rule &);

    private:
        RuleInput input_;
        RuleOutput output_;
    };

    /// Input operator for Rule.
    std::istream & operator >> (std::istream &, Rule &);
    /// Output operator for Rule.
    std::ostream & operator << (std::ostream &, const Rule &);

} /* dectable */ 

#endif /* end of include guard: INC_RULE_H_AOX9VTDR */
