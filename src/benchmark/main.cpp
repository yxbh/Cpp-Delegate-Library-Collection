// original FastDelegate by Don Clugston.
#include "FastDelegate.h"
#include "FastDelegateBind.h"

// V2 (C++11 implementation) of Don Clugston's FastDelegate by Pa�l Jim�nez..
#include <FastDelegate/FastDelegate.hpp>

// A C++11 implementation of Don Clugston's FastDelegate by Vittorio Romeo
#include <FastFunc/FastFunc.hpp>

// A C++ implmenetation of Sergey Ryazanov's "The Impossibly Fast C++ Delegates"
#include <SRDelegate/SRDelegate.hpp>

#include <cassert>
#include <chrono>
#include <functional>
#include <iostream>
#include <iomanip>
#include <memory>

// Code snippet for the function definitions used in the benchmarks.
/*
        int x, y;
        x = 1;
        y = 2;
        int z = x + y;
        z = z;
 */

/*
    int x, y;
    assert(p_spEvent->getType() == TestEvent::Type);
    auto event = std::static_pointer_cast<TestEvent>(p_spEvent);
    x = event->getData();
    y = event->getData();
    int z = x + y;
    z = z;
*/

using EventType = int;

class IEvent
{
public:
    IEvent(void) = default;
    IEvent(const IEvent & p_rIEvent) = delete;
    IEvent(const IEvent && p_rIEvent) = delete;
    IEvent & operator=(const IEvent & p_rIEvent) = delete;
    IEvent & operator=(const IEvent && p_rrIEvent) = delete;
    virtual ~IEvent(void) = default;

    virtual EventType getType(void) const = 0;
    virtual std::string getName(void) const = 0;

}; // IEvent class

using EventSPtr = std::shared_ptr<IEvent>;

class TestEvent
    : public IEvent
{
public:
    static const EventType Type = 0x4a6ee2cf;

private:
    int m_Data = 100;

public:
    TestEvent(void) = default;
    virtual ~TestEvent(void) = default;

    virtual EventType getType(void) const final
    { return TestEvent::Type; }
    virtual std::string getName(void) const final
    { return "TestEvent"; }

    int getData(void) const
    { return m_Data; }

}; // TestEvent class

class Foo
{
public:
    static void staticMemFunc(void)
    {
        int x, y;
        x = 1;
        y = 2;
        int z = x + y;
        z = z;
    }

    static void staticMemFunc2(EventSPtr p_spEvent)
    {
        int x, y;
        assert(p_spEvent->getType() == TestEvent::Type);
        const auto event = std::static_pointer_cast<TestEvent>(p_spEvent);
        x = event->getData();
        y = event->getData();
        int z = x + y;
        z = z;
    }

    void memFunc(void) const
    {
        int x, y;
        x = 1;
        y = 2;
        int z = x + y;
        z = z;
    }

    void memFunc2(EventSPtr p_spEvent) const
    {
        int x, y;
        assert(p_spEvent->getType() == TestEvent::Type);
        auto event = std::static_pointer_cast<TestEvent>(p_spEvent);
        x = event->getData();
        y = event->getData();
        int z = x + y;
        z = z;
    }
};

static void staticGlobalFunc(void)
{
    int x, y;
    x = 1;
    y = 2;
    int z = x + y;
    z = z;
}

static void staticGlobalFunc2(EventSPtr p_spEvent)
{
    int x, y;
    assert(p_spEvent->getType() == TestEvent::Type);
    auto event = std::static_pointer_cast<TestEvent>(p_spEvent);
    x = event->getData();
    y = event->getData();
    int z = x + y;
    z = z;
}

static const int ITERATION_COUNT = 100 * 1000 * 1000; // number of iterations

using Clock = std::chrono::high_resolution_clock;
using Milliseconds = std::chrono::milliseconds;

namespace internal
{
    Clock::time_point before, after;
}

static void beginBenchmark(void)
{
    internal::before = Clock::now();
}

static void endBenchmark(const char * const test_name = "")
{
    internal::after = Clock::now();
    const auto duration = std::chrono::duration_cast<Milliseconds>(internal::after-internal::before);
    std::clog << std::setw(20) << test_name << " : " << duration.count() << "ms\n";
}

static void newLine(void)
{
    std::clog << '\n';
}

static void writeLine(const char * const msg)
{
    std::clog << msg << '\n';
}

void benchmarkFunctionsWithNoParameters(void)
{
    Foo foo;

    std::function<void(void)>                   memFunc1        = std::bind(&Foo::memFunc, &foo);
    ssvu::FastFunc<void(void)>                  memFunc2        = ssvu::FastFunc<void(void)>(&foo, &Foo::memFunc);
	fastdelegate_org::FastDelegate<void(void)>  memFunc3        = fastdelegate_org::bind(&Foo::memFunc, &foo);
    fastdelegate::FastDelegate<void(void)>		memFunc4        = fastdelegate::MakeDelegate(&foo, &Foo::memFunc);
    generic::delegate<void(void)>               memFunc5        = generic::delegate<void(void)>::from<Foo, &Foo::memFunc>(&foo);

    std::function<void(void)>                   staticClassFunc1 = std::bind(&Foo::staticMemFunc);
    ssvu::FastFunc<void(void)>                  staticClassFunc2 = ssvu::FastFunc<void(void)>(&Foo::staticMemFunc);
	fastdelegate_org::FastDelegate0<>           staticClassFunc3 = fastdelegate_org::FastDelegate0<>(&Foo::staticMemFunc);
	fastdelegate::FastDelegate<void(void)>		staticClassFunc4 = fastdelegate::MakeDelegate(&Foo::staticMemFunc);
    generic::delegate<void(void)>               staticClassFunc5 = generic::delegate<void(void)>::from<&Foo::staticMemFunc>();

    std::function<void(void)>                   staticGlobalFunc1 = std::bind(&::staticGlobalFunc);
    ssvu::FastFunc<void(void)>                  staticGlobalFunc2 = ssvu::FastFunc<void(void)>(&::staticGlobalFunc);
	fastdelegate_org::FastDelegate<void(void)>  staticGlobalFunc3 = fastdelegate_org::FastDelegate<void(void)>(&::staticGlobalFunc);
	fastdelegate::FastDelegate<void(void)>		staticGlobalFunc4 = fastdelegate::MakeDelegate(&::staticGlobalFunc);
    generic::delegate<void(void)>               staticGlobalFunc5 = generic::delegate<void(void)>::from<&::staticGlobalFunc>();

    ::newLine();
    ::writeLine("[member function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) foo.memFunc();
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc1();
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc2();
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc3();
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc4();
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc5();
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
    ::writeLine("[static class function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) Foo::staticMemFunc();
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc1();
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc2();
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc3();
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc4();
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc5();
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
    ::writeLine("[static global function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) ::staticGlobalFunc();
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc1();
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc2();
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc3();
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc4();
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc5();
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
}

static void benchmarkFunctionsWithParameters(void)
{
    Foo foo;
    EventSPtr event_sptr = std::make_shared<TestEvent>();

    std::function<void(EventSPtr)>                  memFunc1   = std::bind(&Foo::memFunc2, &foo, std::placeholders::_1);
    ssvu::FastFunc<void(EventSPtr)>                 memFunc2   = ssvu::FastFunc<void(EventSPtr)>(&foo, &Foo::memFunc2);
	fastdelegate_org::FastDelegate<void(EventSPtr)> memFunc3   = fastdelegate_org::bind(&Foo::memFunc2, &foo, std::placeholders::_1);
	fastdelegate::FastDelegate<void(EventSPtr)>		memFunc4   = fastdelegate::MakeDelegate(&foo, &Foo::memFunc2);
    generic::delegate<void(EventSPtr)>              memFunc5   = generic::delegate<void(EventSPtr)>::from<Foo, &Foo::memFunc2>(&foo);

    std::function<void(EventSPtr)>                  staticClassFunc1 = std::bind(&Foo::staticMemFunc2, std::placeholders::_1);
    ssvu::FastFunc<void(EventSPtr)>                 staticClassFunc2 = ssvu::FastFunc<void(EventSPtr)>(&Foo::staticMemFunc2);
	fastdelegate_org::FastDelegate1<EventSPtr>      staticClassFunc3 = fastdelegate_org::FastDelegate1<EventSPtr>(&Foo::staticMemFunc2);
	fastdelegate::FastDelegate<void(EventSPtr)>		staticClassFunc4 = fastdelegate::MakeDelegate(&Foo::staticMemFunc2);
    generic::delegate<void(EventSPtr)>              staticClassFunc5 = generic::delegate<void(EventSPtr)>::from<&Foo::staticMemFunc2>();

    std::function<void(EventSPtr)>                  staticGlobalFunc1 = std::bind(&::staticGlobalFunc2, std::placeholders::_1);
    ssvu::FastFunc<void(EventSPtr)>                 staticGlobalFunc2 = ssvu::FastFunc<void(EventSPtr)>(&::staticGlobalFunc2);
	fastdelegate_org::FastDelegate1<EventSPtr>      staticGlobalFunc3 = fastdelegate_org::FastDelegate1<EventSPtr>(&::staticGlobalFunc2);
	fastdelegate::FastDelegate<void(EventSPtr)>		staticGlobalFunc4 = fastdelegate::MakeDelegate(&::staticGlobalFunc2);
    generic::delegate<void(EventSPtr)>              staticGlobalFunc5 = generic::delegate<void(EventSPtr)>::from<&::staticGlobalFunc2>();

    ::newLine();
    ::writeLine("[member function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) foo.memFunc2(event_sptr);
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc1(event_sptr);
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc2(event_sptr);
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc3(event_sptr);
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc4(event_sptr);
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) memFunc5(event_sptr);
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
    ::writeLine("[static class function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) Foo::staticMemFunc2(event_sptr);
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc1(event_sptr);
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc2(event_sptr);
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc3(event_sptr);
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc4(event_sptr);
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticClassFunc5(event_sptr);
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
    ::writeLine("[static global function]");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) ::staticGlobalFunc2(event_sptr);
    ::endBenchmark("raw");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc1(event_sptr);
    ::endBenchmark("std::function");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc2(event_sptr);
    ::endBenchmark("ssuv::FastFunc");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc3(event_sptr);
    ::endBenchmark("FastDelegate");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc4(event_sptr);
    ::endBenchmark("FastDelegate C++11");

    ::beginBenchmark();
    for (int i = 0; i < ITERATION_COUNT; ++i) staticGlobalFunc5(event_sptr);
    ::endBenchmark("SR Delegate C++11");

    ::newLine();
}

int main()
{
    std::clog << "Hello World!\n";

    std::clog << "######################################\n";
    ::benchmarkFunctionsWithNoParameters();
    std::clog << "######################################\n";
    ::benchmarkFunctionsWithParameters();
    std::clog << "######################################\n";

    bool ret{false};

    void (*func_raw1)(void) = &staticGlobalFunc;
    void (*func_raw2)(void) = &staticGlobalFunc;
    std::clog << "raw equality test : " << (func_raw1 == func_raw2) << '\n';

    generic::delegate<void(void)> func1 = generic::delegate<void(void)>::from<&staticGlobalFunc>();
    generic::delegate<void(void)> func2 = generic::delegate<void(void)>::from<&staticGlobalFunc>();
    generic::delegate<void(void)> func11 = generic::delegate<void(void)>::from<&Foo::staticMemFunc>();
    std::clog << "SR Delegate C++11 equality test : " << (func1 == func2) << '\n';
    std::clog << "SR Delegate C++11 inequality test : " << (func1 == func11) << '\n';

    Foo foo;
    generic::delegate<void(void)> func9 = generic::delegate<void(void)>::from<Foo, &Foo::memFunc>(&foo);
    generic::delegate<void(void)> func10 = generic::delegate<void(void)>::from<Foo, &Foo::memFunc>(&foo);
    std::clog << "SR Delegate C++11 equality test : " << (func9 == func10) << '\n';

    ssvu::FastFunc<void(void)> func3 = &staticGlobalFunc;
    ssvu::FastFunc<void(void)> func4 = &staticGlobalFunc;
    ssvu::FastFunc<void(void)> func13 = &Foo::staticMemFunc;
    std::clog << "FastFunc C++11 equality test : " << (func3 == func4) << '\n';
    std::clog << "FastFunc C++11 inequality test : " << (func3 == func13) << '\n';

	fastdelegate::FastDelegate<void(void)> func5 = &staticGlobalFunc;
	fastdelegate::FastDelegate<void(void)> func6 = &staticGlobalFunc;
	fastdelegate::FastDelegate<void(void)> func12 = &Foo::staticMemFunc;
    std::clog << "FastDelegate C++11 equality test : " << (func5 == func6) << '\n';
    std::clog << "FastDelegate C++11 inequality test : " << (func5 == func12) << '\n';

	fastdelegate::FastDelegate<void(EventSPtr)> func7 = &staticGlobalFunc2;
	fastdelegate::FastDelegate<void(EventSPtr)> func8 = &staticGlobalFunc2;
    std::clog << "FastDelegate C++11 equality test : " << (func7 == func8) << '\n';

    std::clog << "Press Enter to exit...\n";
    std::cin.get();
    return 0;
}

