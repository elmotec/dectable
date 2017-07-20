#ifndef INC_RULE_H_AOX9VTDR
#define INC_RULE_H_AOX9VTDR

#include <vector>
#include <string>

namespace dectable
{

    typedef std::vector<std::string> RuleInput;
    typedef std::vector<std::string> RuleOutput;

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
        /// Useful to compare a RuleInput to the rules in a table.
        Rule (const RuleInput & input);
        /// Instances of Rule will be built off this constructor.
        Rule (const RuleInput & input, const RuleOutput & output);
        virtual ~Rule ();

        /// Access to the Rule configuration.
        static RuleConfiguration & Configuration();

        bool operator==(const Rule &) const;
        bool operator!=(const Rule &) const;

        const RuleOutput & GetOutput() const;

    private:
        RuleInput input_;
        RuleOutput output_;
    };

} /* dectable */ 

#endif /* end of include guard: INC_RULE_H_AOX9VTDR */
