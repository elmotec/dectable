#include "gtest/gtest.h"
#include <algorithm>
#include "dectable/DecisionTable.h"

using namespace ::testing;
using namespace ::dectable;
using namespace ::std;

TEST(RuleConfiguration, DefaultConfigurationMatchAnyIsStar) {
    ASSERT_EQ(Rule::Configuration().matchAny, "*");
}

class ADecisionTable: public Test
{
    public:
        DecisionTable table_;
};

/** @TODO */
TEST_F(ADecisionTable, FromJsonInput) {
    string input(
        "("
        "([some, input], [value1]), "
        "([other, input], [value2]), "
        "([some, *], [value3]), "  // will match "some" in first element.
        ")");
    istringstream istr(input);
    istr >> table_;

    RuleInput firstRuleInput;
    firstRuleInput.push_back("some");
    firstRuleInput.push_back("input");
    table_.push_back(firstRuleInput);
    //RuleInput secondRuleInput;
    //secondRuleInput.push_back("other");
    //secondRuleInput.push_back("input");
    //table_.push_back(secondRuleInput);
    //RuleInput thirdRuleInput;
    //thirdRuleInput.push_back("some");
    //thirdRuleInput.push_back("*");
    //table_.push_back(thirdRuleInput);

    ASSERT_EQ(table_[0], firstRuleInput);
    ASSERT_EQ(table_[0].GetOutput(), RuleOutput(1, "value1"));
    //ASSERT_EQ(table_[1], secondRuleInput);
    //ASSERT_EQ(table_[1].GetOutput(), RuleOutput(1, "value2"));
    //ASSERT_EQ(table_[2], thirdRuleInput);
    //ASSERT_EQ(table_[2].GetOutput(), RuleOutput(1, "value3"));
}

TEST_F(ADecisionTable, IsEmptyWhenCreated) {
    ASSERT_TRUE(table_.size() == 0);
}

TEST_F(ADecisionTable, MatchFirstOfTwoSameRule) {
    table_.push_back(Rule(RuleInput(1, "input"), RuleOutput(1, "first rule")));
    table_.push_back(Rule(RuleInput(1, "input"), RuleOutput(1, "second rule")));
    DecisionTable::const_iterator it =
        std::find(table_.begin(), table_.end(), RuleInput(1, "input"));
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
        std::find(table_.begin(), table_.end(), RuleInput(1, "some"));
    EXPECT_NE(it, table_.end());
    ASSERT_EQ(it->GetOutput(), RuleOutput(1, "some output"));
}

TEST_F(AMatchAllDecitionTable, FindMatchAnyRule) {
    DecisionTable::const_iterator it =
        std::find(table_.begin(), table_.end(), RuleInput(1, "other"));
    EXPECT_NE(it, table_.end());
    ASSERT_EQ(it->GetOutput(), RuleOutput(1, "match-all output"));
}


