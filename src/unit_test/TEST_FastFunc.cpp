#include "test_sample.hpp"
#include <FastFunc/FastFunc.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(FastFunc)

BOOST_AUTO_TEST_CASE(equality_freeFuncNoParam)
{
    auto freeFuncA_1 = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
    auto freeFuncA_2 = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
    BOOST_CHECK(freeFuncA_1 == freeFuncA_2);

    auto inlineFreeFuncA_1 = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
    auto inlineFreeFuncA_2 = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
    BOOST_CHECK(inlineFreeFuncA_1 == inlineFreeFuncA_2);

    auto inlineFreeFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
    auto inlineFreeFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
    BOOST_CHECK(inlineFreeFuncParamA_1 == inlineFreeFuncParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_freeFuncNoParam)
{
    auto freeFuncA = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamA);
    auto freeFuncB = ssvu::FastFunc<void(void)>(&rawFreeFuncNoParamB);
    BOOST_CHECK(freeFuncA != freeFuncB);

    auto inlineFreeFuncA = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamA);
    auto inlineFreeFuncB = ssvu::FastFunc<void(void)>(&rawInlineFreeFuncNoParamB);
    BOOST_CHECK(inlineFreeFuncA != inlineFreeFuncB);

    auto inlineFreeFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamA);
    auto inlineFreeFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&rawInlineFreeFuncWithParamB);
    BOOST_CHECK(inlineFreeFuncParamA != inlineFreeFuncParamB);
}

BOOST_AUTO_TEST_CASE(lambda)
{
    ssvu::FastFunc<void(void)> lambda_1([](void){ return; });
    ssvu::FastFunc<void(void)> lambda_2([](void){ return; });
    auto lambda_3 = ssvu::FastFunc<void(void)>([](void){ return; });
    ssvu::FastFunc<void(void)> lambda_4 = [](void){ return; };
    BOOST_CHECK(lambda_1 != lambda_2);
    BOOST_CHECK(lambda_1 != lambda_3);
    BOOST_CHECK(lambda_1 != lambda_4);
}

BOOST_AUTO_TEST_CASE(equality_staticMemFuncNoParam)
{
    auto singleInheritStaticmemFuncNoParamA_1 = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
    auto singleInheritStaticmemFuncNoParamA_2 = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
    BOOST_CHECK(singleInheritStaticmemFuncNoParamA_1 == singleInheritStaticmemFuncNoParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_staticMemFuncNoParam)
{
    auto singleInheritStaticmemFuncNoParamA = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamA);
    auto singleInheritStaticmemFuncNoParamB = ssvu::FastFunc<void(void)>(&SingleInheritBaseClass::rawStaticMemFuncNoParamB);
    BOOST_CHECK(singleInheritStaticmemFuncNoParamA != singleInheritStaticmemFuncNoParamB);
}

BOOST_AUTO_TEST_CASE(equality_memFunc)
{
    SingleInheritBaseClass single_inhert_base_obj;
    auto singleInheritBMemFuncA_1 = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
    auto singleInheritBMemFuncA_2 = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
    BOOST_CHECK(singleInheritBMemFuncA_1 == singleInheritBMemFuncA_2);
    auto singleInheritBMemFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
    auto singleInheritBMemFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
    BOOST_CHECK(singleInheritBMemFuncParamA_1 == singleInheritBMemFuncParamA_2);

    SingleInheritBaseClass single_inhert_obj;
    auto singleInheritMemFuncA_1 = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
    auto singleInheritMemFuncA_2 = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
    BOOST_CHECK(singleInheritMemFuncA_1 == singleInheritMemFuncA_2);
    auto singleInheritMemFuncParamA_1 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
    auto singleInheritMemFuncParamA_2 = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
    BOOST_CHECK(singleInheritMemFuncParamA_1 == singleInheritMemFuncParamA_2);
}

BOOST_AUTO_TEST_CASE(inequality_memFunc)
{
    SingleInheritBaseClass single_inhert_base_obj;
    auto singleInheritBMemFuncA = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamA);
    auto singleInheritBMemFuncB = ssvu::FastFunc<void(void)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncNoParamB);
    BOOST_CHECK(singleInheritBMemFuncA != singleInheritBMemFuncB);
    auto singleInheritBMemFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamA);
    auto singleInheritBMemFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_base_obj, &SingleInheritBaseClass::rawMemFuncWithParamB);
    BOOST_CHECK(singleInheritBMemFuncParamA != singleInheritBMemFuncParamB);

    SingleInheritClass single_inhert_obj;
    auto singleInheritMemFuncA = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncNoParamA);
    auto singleInheritMemFuncB = ssvu::FastFunc<void(void)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncNoParamB);
    BOOST_CHECK(singleInheritMemFuncA != singleInheritMemFuncB);
    auto singleInheritMemFuncParamA = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncWithParamA);
    auto singleInheritMemFuncParamB = ssvu::FastFunc<void(EventSPtr)>(&single_inhert_obj, &SingleInheritClass::rawMemFuncWithParamB);
    BOOST_CHECK(singleInheritMemFuncParamA != singleInheritMemFuncParamB);
}

BOOST_AUTO_TEST_SUITE_END()
