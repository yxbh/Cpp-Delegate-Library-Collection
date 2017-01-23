#include "test_sample.hpp"

#include "catch.hpp"

#define TAG "raw"

TEST_CASE(TAG)
{

    SECTION("equality")
    {
        REQUIRE(&rawFreeFuncNoParamA == &rawFreeFuncNoParamA);
        REQUIRE(&rawFreeFuncNoParamB == &rawFreeFuncNoParamB);

        REQUIRE(&rawInlineFreeFuncNoParamA == &rawInlineFreeFuncNoParamA);
        REQUIRE(&rawInlineFreeFuncNoParamB == &rawInlineFreeFuncNoParamB);
    }

    SECTION("inequality")
    {
        REQUIRE(&rawFreeFuncNoParamA != &rawFreeFuncNoParamB);
        REQUIRE(&rawFreeFuncNoParamB != &rawFreeFuncNoParamA);

        REQUIRE(&rawInlineFreeFuncNoParamA != &rawInlineFreeFuncNoParamB);
        REQUIRE(&rawInlineFreeFuncNoParamB != &rawInlineFreeFuncNoParamA);
    }

}
