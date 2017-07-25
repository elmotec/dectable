/** Copyright (c) 2017 elmotec. See LICENSE */

#include "gtest/gtest.h"
#include <algorithm>
#include <sstream>
#include "dectable/DecisionTable.h"


using namespace ::std;
using namespace ::dectable;

/**
 *  Create a vector<string> out of a string.
 *
 *  Format is <number of entries> [<entry> ...]
 *
 *  Provided for convenience.
 *
 *  @return a vector<string> so it can be turned to a dectable::RuleInput or
 *  a dectable::RuleOutput. */
vector<string> FromString(const string & str)
{
    RuleInput ruleIo;  // to force call to operator >>(istream &, RuleInput &).
    istringstream is(str);
    assert(is.good());
    is >> ruleIo;
    assert(is.good());  // FIXME: requires str to end with a space.
    return ruleIo;
}

TEST(Example, Permissions)
{
    // The rule output is very simple: allow or deny.
    RuleOutput allow(FromString("1 allow "));
    RuleOutput deny(FromString("1 deny "));

    // Here, the convention is for the rule input to be a triplet of:
    // role action subject
    //
    // * is a configurable place holder that will match any value. This is
    // what makes decision table shine; it provides flexibility to define
    // rules.
    Rule adminsCanDoEverything(FromString("3 administrators * * "), allow);
    Rule dogOwnerCanAccessDogOnly(FromString("3 dogOwners * dog "), allow);
    Rule publicReadAccess(FromString("3 * read public "), allow);
    Rule denyEverythingElse(FromString("3 * * * "), deny);

    // and the decision table. Note the order matter...
    DecisionTable permissions;
    permissions.push_back(adminsCanDoEverything);
    permissions.push_back(dogOwnerCanAccessDogOnly);
    permissions.push_back(publicReadAccess);
    permissions.push_back(denyEverythingElse);

    // Usage:
    RuleInput dogOwnerToPetDog(FromString("3 dogOwners pet dog "));
    ASSERT_EQ(FindFirstMatch(permissions.begin(), permissions.end(),
                             dogOwnerToPetDog)->GetOutput(),
              allow);

    RuleInput userToFeedFish(FromString("3 users feed fish "));
    ASSERT_EQ(FindFirstMatch(permissions.begin(), permissions.end(),
                             userToFeedFish)->GetOutput(),
              deny);

    RuleInput adminToFeedFish(FromString("3 administrators feed fish "));
    ASSERT_EQ(FindFirstMatch(permissions.begin(), permissions.end(),
                             adminToFeedFish)->GetOutput(),
              allow);
}
