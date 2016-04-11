#include "test_sample.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(raw_functions)

BOOST_AUTO_TEST_CASE(equality)
{
    BOOST_CHECK(&rawFreeFuncNoParamA == &rawFreeFuncNoParamA);
	BOOST_CHECK(&rawFreeFuncNoParamB == &rawFreeFuncNoParamB);

	BOOST_CHECK(&rawInlineFreeFuncNoParamA == &rawInlineFreeFuncNoParamA);
	BOOST_CHECK(&rawInlineFreeFuncNoParamB == &rawInlineFreeFuncNoParamB);
}

BOOST_AUTO_TEST_CASE(inequality)
{
    BOOST_CHECK(&rawFreeFuncNoParamA != &rawFreeFuncNoParamB);
	BOOST_CHECK(&rawFreeFuncNoParamB != &rawFreeFuncNoParamA);

	BOOST_CHECK(&rawInlineFreeFuncNoParamA != &rawInlineFreeFuncNoParamB);
	BOOST_CHECK(&rawInlineFreeFuncNoParamB != &rawInlineFreeFuncNoParamA);
}

BOOST_AUTO_TEST_SUITE_END()