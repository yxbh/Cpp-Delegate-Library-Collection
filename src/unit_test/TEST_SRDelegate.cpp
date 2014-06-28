#include "test_sample.hpp"
#include <SRDelegate/SRDelegate.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(SRDelegate_Cpp11)

BOOST_AUTO_TEST_CASE(custom)
{
    auto inlineFreeFuncA_1 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
    auto inlineFreeFuncA_2 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
    BOOST_CHECK(inlineFreeFuncA_1 == inlineFreeFuncA_2);

    //auto inlineFreeFuncParamA_1 = generic::delegate<void(EventSPtr)>(&rawInlineFreeFuncWithParamA); // does not compile in VS2013 (SFINAE issue?).
    auto inlineFreeFuncA_3 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);
    auto inlineFreeFuncA_4 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamA);
    generic::delegate<void(void)> inlineFreeFuncA_5 = &rawInlineFreeFuncNoParamA;
    auto inlineFreeFuncA_6 = generic::delegate<void(void)>::from(&rawInlineFreeFuncNoParamA);
    BOOST_CHECK(inlineFreeFuncA_1 == inlineFreeFuncA_3);
    BOOST_CHECK(inlineFreeFuncA_3 == inlineFreeFuncA_4);
    BOOST_CHECK(inlineFreeFuncA_3 == inlineFreeFuncA_5);
    BOOST_CHECK(inlineFreeFuncA_1 == inlineFreeFuncA_6);
    BOOST_CHECK(inlineFreeFuncA_3 == inlineFreeFuncA_6);
    auto singleInheritStaticmemFuncNoParamA_1 = generic::delegate<void(void)>::from(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
    auto singleInheritStaticmemFuncNoParamA_2 = generic::delegate<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
    BOOST_CHECK(inlineFreeFuncA_3 != singleInheritStaticmemFuncNoParamA_1);
    BOOST_CHECK(inlineFreeFuncA_3 != singleInheritStaticmemFuncNoParamA_2);
    BOOST_CHECK(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);

    auto inlineFreeFuncB_1 = generic::delegate<void(void)>(&rawInlineFreeFuncNoParamB);
    BOOST_CHECK(inlineFreeFuncA_3 != inlineFreeFuncB_1);
}

BOOST_AUTO_TEST_CASE(equality_freeFuncNoParam)
{
    auto freeFuncA_1 = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
    auto freeFuncA_2 = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
    BOOST_CHECK(freeFuncA_1 == freeFuncA_2);

    auto inlineFreeFuncA_1 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
    auto inlineFreeFuncA_2 = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
    BOOST_CHECK(inlineFreeFuncA_1 == inlineFreeFuncA_2);

    auto inlineFreeFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
    auto inlineFreeFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
    BOOST_CHECK(inlineFreeFuncParamA_1 == inlineFreeFuncParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_freeFuncNoParam)
{
    auto freeFuncA = generic::delegate<void(void)>::from<&rawFreeFuncNoParamA>();
    auto freeFuncB = generic::delegate<void(void)>::from<&rawFreeFuncNoParamB>();
    BOOST_CHECK(freeFuncA != freeFuncB);

    auto inlineFreeFuncA = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamA>();
    auto inlineFreeFuncB = generic::delegate<void(void)>::from<&rawInlineFreeFuncNoParamB>();
    BOOST_CHECK(inlineFreeFuncA != inlineFreeFuncB);

    auto inlineFreeFuncParamA = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamA>();
    auto inlineFreeFuncParamB = generic::delegate<void(EventSPtr)>::from<&rawInlineFreeFuncWithParamB>();
    BOOST_CHECK(inlineFreeFuncParamA != inlineFreeFuncParamB);
}

BOOST_AUTO_TEST_CASE(lambda)
{
    generic::delegate<void(void)> lambda_1([](){ int i = 1 + 1; return; });
    generic::delegate<void(void)> lambda_2([](){ int i = 1 + 1; return; });
    auto lambda_3 = generic::delegate<void(void)>::from([](){ return; });
    generic::delegate<void(void)> lambda_4 = [](){ int i = 1 + 1; return; };
    BOOST_CHECK(lambda_1 != lambda_2);
    BOOST_CHECK(lambda_1 != lambda_3);
    BOOST_CHECK(lambda_1 != lambda_4);
}

BOOST_AUTO_TEST_CASE(equality_staticMemFuncNoParam)
{
    auto singleInheritStaticmemFuncNoParamA_1 = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
    auto singleInheritStaticmemFuncNoParamA_2 = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
    BOOST_CHECK(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_staticMemFuncNoParam)
{
    auto singleInheritStaticmemFuncNoParamA = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamA>();
    auto singleInheritStaticmemFuncNoParamB = generic::delegate<void(void)>::from<&SingleInheritBaseClass::rawStaticMemFuncNoParamB>();
    BOOST_CHECK(singleInheritStaticmemFuncNoParamA != singleInheritStaticmemFuncNoParamB);
}

BOOST_AUTO_TEST_CASE(equality_memFunc)
{
    SingleInheritBaseClass single_inhert_base_obj;
    auto singleInheritBMemFuncA_1 = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
    auto singleInheritBMemFuncA_2 = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
    BOOST_CHECK(singleInheritBMemFuncA_1 == singleInheritBMemFuncA_2);
    auto singleInheritBMemFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
    auto singleInheritBMemFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
    BOOST_CHECK(singleInheritBMemFuncParamA_1 == singleInheritBMemFuncParamA_2);

    SingleInheritClass single_inhert_obj;
    auto singleInheritMemFuncA_1 = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
    auto singleInheritMemFuncA_2 = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
    BOOST_CHECK(singleInheritMemFuncA_1 == singleInheritMemFuncA_2);
    auto singleInheritMemFuncParamA_1 = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
    auto singleInheritMemFuncParamA_2 = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
    BOOST_CHECK(singleInheritMemFuncParamA_1 == singleInheritMemFuncParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_memFunc)
{
    SingleInheritBaseClass single_inhert_base_obj;
    auto singleInheritBMemFuncA = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamA>(&single_inhert_base_obj);
    auto singleInheritBMemFuncB = generic::delegate<void(void)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncNoParamB>(&single_inhert_base_obj);
    BOOST_CHECK(singleInheritBMemFuncA != singleInheritBMemFuncB);
    auto singleInheritBMemFuncParamA = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamA>(&single_inhert_base_obj);
    auto singleInheritBMemFuncParamB = generic::delegate<void(EventSPtr)>::from<SingleInheritBaseClass, &SingleInheritBaseClass::rawMemFuncWithParamB>(&single_inhert_base_obj);
    BOOST_CHECK(singleInheritBMemFuncParamA != singleInheritBMemFuncParamB);

    SingleInheritClass single_inhert_obj;
    auto singleInheritMemFuncA = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamA>(&single_inhert_obj);
    auto singleInheritMemFuncB = generic::delegate<void(void)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncNoParamB>(&single_inhert_obj);
    BOOST_CHECK(singleInheritMemFuncA != singleInheritMemFuncB);
    auto singleInheritMemFuncParamA = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamA>(&single_inhert_obj);
    auto singleInheritMemFuncParamB = generic::delegate<void(EventSPtr)>::from<SingleInheritClass, &SingleInheritClass::rawMemFuncWithParamB>(&single_inhert_obj);
    BOOST_CHECK(singleInheritMemFuncParamA != singleInheritMemFuncParamB);
}

BOOST_AUTO_TEST_SUITE_END()
