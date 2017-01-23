#include "test_sample.hpp"
#include <SRDelegate/SRDelegate.hpp>

#include "catch.hpp"

#define TAG "SRDelegate_Cpp11"

TEST_CASE()
{

    SECTION("custom")
    {
        auto inlineFreeFuncA_3 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);
        auto inlineFreeFuncA_4 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);

        auto singleInheritStaticmemFuncNoParamA_1 = generic::delegate<void(void)>::from(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
        auto singleInheritStaticmemFuncNoParamA_2 = generic::delegate<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
        REQUIRE(inlineFreeFuncA_3 != singleInheritStaticmemFuncNoParamA_1);
        REQUIRE(inlineFreeFuncA_3 != singleInheritStaticmemFuncNoParamA_2);
        REQUIRE(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);

        auto inlineFreeFuncB_1 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamB);
        REQUIRE(inlineFreeFuncA_3 != inlineFreeFuncB_1);
    }

    SECTION("inlineFreeFuncWithParam")
    {
        auto inlineFreeFuncA_1 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
        auto inlineFreeFuncA_2 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
        REQUIRE(inlineFreeFuncA_1 == inlineFreeFuncA_2);
        REQUIRE(inlineFreeFuncA_2 == inlineFreeFuncA_1);

        auto inlineFreeFuncParamA_1 = generic::delegate<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
        auto inlineFreeFuncParamA_2 = generic::delegate<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
        auto inlineFreeFuncParamB_1 = generic::delegate<void(EventSPtr)>(&rawInlineFreeFuncWithParamB);
        REQUIRE(inlineFreeFuncParamA_1 == inlineFreeFuncParamA_2);
        REQUIRE(inlineFreeFuncParamA_2 == inlineFreeFuncParamA_1);
        REQUIRE(inlineFreeFuncParamA_1 != inlineFreeFuncParamB_1);
        REQUIRE(inlineFreeFuncParamB_1 != inlineFreeFuncParamA_1);

        auto inlineFreeFuncA_3 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);
        auto inlineFreeFuncA_4 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);
        generic::delegate<void(void)> inlineFreeFuncA_5 = &rawInlineFreeFuncNoParamA;
        auto inlineFreeFuncA_6 = generic::delegate<void(void)>::from(&rawInlineFreeFuncNoParamA);
        //REQUIRE(inlineFreeFuncA_1 == inlineFreeFuncA_3); // fails
        REQUIRE(inlineFreeFuncA_3 == inlineFreeFuncA_4);
        //REQUIRE(inlineFreeFuncA_3 == inlineFreeFuncA_5); // fails
        //REQUIRE(inlineFreeFuncA_1 == inlineFreeFuncA_6); // fails
        REQUIRE(inlineFreeFuncA_3 == inlineFreeFuncA_6);
        REQUIRE(inlineFreeFuncA_3 == inlineFreeFuncA_4);
        REQUIRE(inlineFreeFuncA_5 == inlineFreeFuncA_6);
    }

    SECTION("equality_freeFuncNoParam")
    {
        auto freeFuncA_1 = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
        auto freeFuncA_2 = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
        REQUIRE(freeFuncA_1 == freeFuncA_2);

        auto inlineFreeFuncA_1 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
        auto inlineFreeFuncA_2 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
        REQUIRE(inlineFreeFuncA_1 == inlineFreeFuncA_2);

        auto inlineFreeFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
        auto inlineFreeFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
        REQUIRE(inlineFreeFuncParamA_1 == inlineFreeFuncParamA_2);
    }

    SECTION("inequality_freeFuncNoParam")
    {
        auto freeFuncA = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
        auto freeFuncB = generic::delegate<void(void)>::from<&rawFreeFuncNoParamB>();
        REQUIRE(freeFuncA != freeFuncB);

        auto inlineFreeFuncA = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
        auto inlineFreeFuncB = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamB>();
        REQUIRE(inlineFreeFuncA != inlineFreeFuncB);

        auto inlineFreeFuncParamA = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
        auto inlineFreeFuncParamB = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamB>();
        REQUIRE(inlineFreeFuncParamA != inlineFreeFuncParamB);
    }

    SECTION("lambda")
    {
        generic::delegate<void(void)> lambda_1([]() { int i = 1 + 1; return; });
        generic::delegate<void(void)> lambda_2([]() { int i = 1 + 1; return; });
        auto lambda_3 = generic::delegate<void(void)>::from([]() { return; });
        generic::delegate<void(void)> lambda_4 = []() { int i = 1 + 1; return; };
        REQUIRE(lambda_1 != lambda_2);
        REQUIRE(lambda_1 != lambda_3);
        REQUIRE(lambda_1 != lambda_4);
    }

    SECTION("equality_staticMemFuncNoParam")
    {
        auto singleInheritStaticmemFuncNoParamA_1 = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
        auto singleInheritStaticmemFuncNoParamA_2 = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
        REQUIRE(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);
    }

    SECTION("inequality_staticMemFuncNoParam")
    {
        auto singleInheritStaticmemFuncNoParamA = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
        auto singleInheritStaticmemFuncNoParamB = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamB>();
        REQUIRE(singleInheritStaticmemFuncNoParamA != singleInheritStaticmemFuncNoParamB);
    }

    SECTION("equality_memFunc")
    {
        SingleInheritBaseClass single_inhert_base_obj;
        auto singleInheritBMemFuncA_1 = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
        auto singleInheritBMemFuncA_2 = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
        REQUIRE(singleInheritBMemFuncA_1 == singleInheritBMemFuncA_2);
        auto singleInheritBMemFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
        auto singleInheritBMemFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
        REQUIRE(singleInheritBMemFuncParamA_1 == singleInheritBMemFuncParamA_2);

        SingleInheritClass single_inhert_obj;
        auto singleInheritMemFuncA_1 = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
        auto singleInheritMemFuncA_2 = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
        REQUIRE(singleInheritMemFuncA_1 == singleInheritMemFuncA_2);
        auto singleInheritMemFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
        auto singleInheritMemFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
        REQUIRE(singleInheritMemFuncParamA_1 == singleInheritMemFuncParamA_2);
    }

    SECTION("inequality_memFunc")
    {
        SingleInheritBaseClass single_inhert_base_obj;
        auto singleInheritBMemFuncA = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
        auto singleInheritBMemFuncB = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamB>(&single_inhert_base_obj);
        REQUIRE(singleInheritBMemFuncA != singleInheritBMemFuncB);
        auto singleInheritBMemFuncParamA = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
        auto singleInheritBMemFuncParamB = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamB>(&single_inhert_base_obj);
        REQUIRE(singleInheritBMemFuncParamA != singleInheritBMemFuncParamB);

        SingleInheritClass single_inhert_obj;
        auto singleInheritMemFuncA = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
        auto singleInheritMemFuncB = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamB>(&single_inhert_obj);
        REQUIRE(singleInheritMemFuncA != singleInheritMemFuncB);
        auto singleInheritMemFuncParamA = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
        auto singleInheritMemFuncParamB = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamB>(&single_inhert_obj);
        REQUIRE(singleInheritMemFuncParamA != singleInheritMemFuncParamB);
    }

}
