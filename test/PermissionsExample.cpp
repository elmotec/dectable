#include "gtest/gtest.h"
#include <algorithm>
#include "dectable/DecisionTable.h"


using namespace ::std;
using namespace ::dectable;


TEST(Example, Permissions)
{
    // In this case, the convention is for the rule input to be a triplet of:
    // role, action, subject
    //
    // The setup is a little laborious but can be eased using more recent 
    // version of C++, boost, or file input.
    RuleInput administrators;
    administrators.push_back("adminstrators");
    administrators.push_back("*");
    administrators.push_back("*");
    RuleInput dogOwners;
    dogOwners.push_back("dogOwners");
    dogOwners.push_back("*");
    dogOwners.push_back("dog");
    RuleInput publicDirectoriesRead;
    publicDirectoriesRead.push_back("*");
    publicDirectoriesRead.push_back("read");
    publicDirectoriesRead.push_back("public");
    RuleInput catchAll;
    catchAll.push_back("*");
    catchAll.push_back("*");
    catchAll.push_back("*");

    // The rule output is very simple: allow or deny.
    RuleOutput allow(1, "allow");
    RuleOutput deny(1, "deny");

    // Define the rules ...
    Rule adminsCanDoEverything(administrators, allow);
    Rule dogOwnerCanAccessDogOnly(dogOwners, allow);
    Rule publicReadAccess(publicDirectoriesRead, allow);
    Rule denyEvertythingElse(catchAll, deny);

    // and the decision table. Note the order matter...
    DecisionTable permissions;
    permissions.push_back(adminsCanDoEverything);
    permissions.push_back(dogOwnerCanAccessDogOnly);
    permissions.push_back(publicReadAccess);
    permissions.push_back(denyEvertythingElse);

    // Usage:
    RuleInput powerUserWantsToPetDog;
    powerUserWantsToPetDog.push_back("dogOwners");
    powerUserWantsToPetDog.push_back("pet");
    powerUserWantsToPetDog.push_back("dog");
    DecisionTable::const_iterator puIt = FindFirstMatch(permissions.begin(),
                                                        permissions.end(),
                                                        powerUserWantsToPetDog);
    assert(puIt != permissions.end());
    string puOutput = puIt->GetOutput()[0];
    ASSERT_EQ(puOutput, "allow");

    RuleInput userWantsToFeedFish;
    userWantsToFeedFish.push_back("kid");
    userWantsToFeedFish.push_back("feed");
    userWantsToFeedFish.push_back("fish");
    DecisionTable::const_iterator uIt = FindFirstMatch(permissions.begin(),
                                                       permissions.end(),
                                                       userWantsToFeedFish);
    assert(uIt != permissions.end());
    string uOutput = uIt->GetOutput()[0];
    ASSERT_EQ(uOutput, "deny");
}
