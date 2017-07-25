#include "gtest/gtest.h"
#include <algorithm>
#include "dectable/DecisionTable.h"
#include <csignal>

using namespace ::testing;
using namespace ::dectable;
using namespace ::std;

TEST(RuleConfiguration, DefaultConfigurationMatchAnyIsStar) {
    ASSERT_EQ(Rule::Configuration().matchAny, "*");
}

TEST(DecisionTable, IsEmptyWhenCreated) {
    ASSERT_TRUE(DecisionTable().size() == 0);
}

TEST(DecisionTable, MatchFirstOfTwoSameRule) {
    DecisionTable table;
    table.push_back(Rule(RuleInput(1, "input"), RuleOutput(1, "first rule")));
    table.push_back(Rule(RuleInput(1, "input"), RuleOutput(1, "second rule")));
    DecisionTable::const_iterator it =
        FindFirstMatch(table.begin(), table.end(), RuleInput(1, "input"));
    ASSERT_EQ(it->GetOutput(), RuleOutput(1, "first rule"));
}

class AMatchAllDecitionTable: public Test
{
    public:
        AMatchAllDecitionTable();

        DecisionTable table_;
        Rule matchSome_;
        Rule matchAny_;
};

AMatchAllDecitionTable::AMatchAllDecitionTable()
    : matchSome_(RuleInput(1, "some"), RuleOutput(1, "some output")),
      matchAny_(RuleInput(1, "*"), RuleOutput(1, "match-all output"))
{
    table_.push_back(matchSome_);
    table_.push_back(matchAny_);
}

TEST_F(AMatchAllDecitionTable, HasCorrectSize) {
    ASSERT_TRUE(table_.size() == 2);
}

TEST_F(AMatchAllDecitionTable, FindMatchingSomeRule) {
    DecisionTable::const_iterator it =
        FindFirstMatch(table_.begin(), table_.end(), RuleInput(1, "some"));
    EXPECT_NE(it, table_.end());
    ASSERT_EQ(it->GetOutput(), RuleOutput(1, "some output"));
}

TEST_F(AMatchAllDecitionTable, FindMatchAnyRule) {
    DecisionTable::const_iterator it =
        FindFirstMatch(table_.begin(), table_.end(), RuleInput(1, "other"));
    EXPECT_NE(it, table_.end());
    ASSERT_EQ(it->GetOutput(), RuleOutput(1, "match-all output"));
}

class ADecisionTableRule: public Test
{
    public:
        Rule rule_;
        string ruleAsString_;
        ADecisionTableRule();
        void SetUp();
};

ADecisionTableRule::ADecisionTableRule():
    ruleAsString_("3 input1 input2 input3 1 output")
{}

void ADecisionTableRule::SetUp()
{
    istringstream istr(ruleAsString_);
    istr >> rule_;
}

TEST_F(ADecisionTableRule, CanBeReadFromStream)
{
    ASSERT_EQ(rule_.GetInput()[0], "input1");
    ASSERT_EQ(rule_.GetInput()[1], "input2");
    ASSERT_EQ(rule_.GetInput()[2], "input3");
    ASSERT_EQ(rule_.GetOutput()[0], "output");
}

TEST_F(ADecisionTableRule, CanBeWrittenToStream)
{
    ostringstream ostr;
    ostr << rule_;
    ASSERT_EQ(ostr.str(), ruleAsString_);
}

TEST_F(ADecisionTableRule, HasATrueComparisonOperator)
{
    Rule rule;
    istringstream istr(ruleAsString_);
    istr >> rule;
    // Make a small change to the rule:
    rule.SetOutput(RuleOutput(1, "other"));
    ASSERT_NE(rule_, rule);
}

class ADecisionTable: public Test
{
    public:
        string tableAsString_;
        DecisionTable table_;
        ADecisionTable();
        void SetUp();
};

ADecisionTable::ADecisionTable(): tableAsString_(
        "4 "  // number of rules
        // 2 inputs 1 output for rule 1
        "2 some input 1 value1 "
        // 2 inputs 1 output for rule 2, ...
        "2 other input 1 value2 "
        // will match "some" in first element. Anything for second element.
        "2 some * 1 value3 "
        // catch-all rule.
        "2 * * 1 catchAll " )
{}

void ADecisionTable::SetUp()
{
    istringstream istr(tableAsString_);
    istr >> table_;
}

TEST_F(ADecisionTable, CanBeReadFromToStream)
{
    RuleInput firstRuleInput;
    firstRuleInput.push_back("some");
    firstRuleInput.push_back("input");
    RuleInput secondRuleInput;
    secondRuleInput.push_back("other");
    secondRuleInput.push_back("input");
    RuleInput thirdRuleInput;
    thirdRuleInput.push_back("some");
    thirdRuleInput.push_back("*");

    ASSERT_EQ(table_.size(), 4);
    ASSERT_EQ(table_[0].GetInput(), firstRuleInput);
    ASSERT_EQ(table_[0].GetOutput(), RuleOutput(1, "value1"));
    ASSERT_EQ(table_[1].GetInput(), secondRuleInput);
    ASSERT_EQ(table_[1].GetOutput(), RuleOutput(1, "value2"));
    ASSERT_EQ(table_[2].GetInput(), thirdRuleInput);
    ASSERT_EQ(table_[2].GetOutput(), RuleOutput(1, "value3"));
    ASSERT_EQ(table_[3].GetInput(), RuleInput(2, "*"));
    ASSERT_EQ(table_[3].GetOutput(), RuleOutput(1, "catchAll"));
}

TEST_F(ADecisionTable, CanBeWrittenToStream)
{
    ostringstream ostr;
    ostr << table_;
    ASSERT_EQ(ostr.str(), tableAsString_);
}


