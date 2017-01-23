#include "test_sample.hpp"
#include <FastFunc/FastFunc.hpp>
#include "catch.hpp"

#define TAG "FastFunc"

TEST_CASE(TAG)
{

    SECTION("equality_freeFuncNoParam")
    {
        auto freeFuncA_1 = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
        auto freeFuncA_2 = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
        REQUIRE(freeFuncA_1 == freeFuncA_2);

        auto inlineFreeFuncA_1 = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
        auto inlineFreeFuncA_2 = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
        REQUIRE(inlineFreeFuncA_1 == inlineFreeFuncA_2);

        auto inlineFreeFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
        auto inlineFreeFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
        REQUIRE(inlineFreeFuncParamA_1 == inlineFreeFuncParamA_2);
    }

    SECTION("inequality_freeFuncNoParam")
    {
        auto freeFuncA = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
        auto freeFuncB = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamB);
        REQUIRE(freeFuncA != freeFuncB);

        auto inlineFreeFuncA = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
        auto inlineFreeFuncB = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamB);
        REQUIRE(inlineFreeFuncA != inlineFreeFuncB);

        auto inlineFreeFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
        auto inlineFreeFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamB);
        REQUIRE(inlineFreeFuncParamA != inlineFreeFuncParamB);
    }

    SECTION("lambda", TAG)
    {
        ssvu::FastFunc<void(void)> lambda_1([](void) { return; });
        ssvu::FastFunc<void(void)> lambda_2([](void) { return; });
        auto lambda_3 = ssvu::FastFunc<void(void)>([](void) { return; });
        ssvu::FastFunc<void(void)> lambda_4 = [](void) { return; };
        REQUIRE(lambda_1 != lambda_2);
        REQUIRE(lambda_1 != lambda_3);
        REQUIRE(lambda_1 != lambda_4);
    }

    SECTION("equality_staticMemFuncNoParam")
    {
        auto singleInheritStaticmemFuncNoParamA_1 = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
        auto singleInheritStaticmemFuncNoParamA_2 = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
        REQUIRE(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);
    }

    SECTION("inequality_staticMemFuncNoParam")
    {
        auto singleInheritStaticmemFuncNoParamA = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
        auto singleInheritStaticmemFuncNoParamB = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamB);
        REQUIRE(singleInheritStaticmemFuncNoParamA != singleInheritStaticmemFuncNoParamB);
    }

    SECTION("equality_memFunc")
    {
        SingleInheritBaseClass single_inhert_base_obj;
        auto singleInheritBMemFuncA_1 = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
        auto singleInheritBMemFuncA_2 = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
        REQUIRE(singleInheritBMemFuncA_1 == singleInheritBMemFuncA_2);
        auto singleInheritBMemFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
        auto singleInheritBMemFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
        REQUIRE(singleInheritBMemFuncParamA_1 == singleInheritBMemFuncParamA_2);

        SingleInheritBaseClass single_inhert_obj;
        auto singleInheritMemFuncA_1 = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
        auto singleInheritMemFuncA_2 = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
        REQUIRE(singleInheritMemFuncA_1 == singleInheritMemFuncA_2);
        auto singleInheritMemFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
        auto singleInheritMemFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
        REQUIRE(singleInheritMemFuncParamA_1 == singleInheritMemFuncParamA_2);
    }

    SECTION("inequality_memFunc")
    {
        SingleInheritBaseClass single_inhert_base_obj;
        auto singleInheritBMemFuncA = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
        auto singleInheritBMemFuncB = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamB);
        REQUIRE(singleInheritBMemFuncA != singleInheritBMemFuncB);
        auto singleInheritBMemFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
        auto singleInheritBMemFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamB);
        REQUIRE(singleInheritBMemFuncParamA != singleInheritBMemFuncParamB);

        SingleInheritClass single_inhert_obj;
        auto singleInheritMemFuncA = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncNoParamA);
        auto singleInheritMemFuncB = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncNoParamB);
        REQUIRE(singleInheritMemFuncA != singleInheritMemFuncB);
        auto singleInheritMemFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncWithParamA);
        auto singleInheritMemFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncWithParamB);
        REQUIRE(singleInheritMemFuncParamA != singleInheritMemFuncParamB);
    }

}
