#pragma once

#include <iostream>
#include <memory>
#include <string>

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
    {
        return TestEvent::Type;
    }
    virtual std::string getName(void) const final
    {
        return "TestEvent";
    }

    int getData(void) const
    {
        return m_Data;
    }

}; // TestEvent class


extern void rawFreeFuncNoParamA(void);
extern void rawFreeFuncNoParamB(void);
extern void rawFreeFuncWithParamA(EventSPtr);
extern void rawFreeFuncWithParamB(EventSPtr);
inline void rawInlineFreeFuncNoParamA(void)
{
    std::clog << "inline free function A\n";
}
inline void rawInlineFreeFuncNoParamB(void)
{
    std::clog << "inline free function B\n";
}
inline void rawInlineFreeFuncWithParamA(EventSPtr evt)
{
    const auto name = evt->getName();
}
inline void rawInlineFreeFuncWithParamB(EventSPtr evt)
{
    const auto name = evt->getName();
}

class SingleInheritBaseClass
{
public:
    static void rawStaticMemFuncNoParamA(void);
    static void rawStaticMemFuncNoParamB(void);

    void rawMemFuncNoParamA(void);
    void rawMemFuncNoParamB(void);
    void rawMemFuncWithParamA(EventSPtr);
    void rawMemFuncWithParamB(EventSPtr);

};

class SingleInheritClass
    : public SingleInheritBaseClass
{
public:
    virtual void rawMemFuncNoParamA(void);
    virtual void rawMemFuncNoParamB(void);
    virtual void rawMemFuncWithParamA(EventSPtr);
    virtual void rawMemFuncWithParamB(EventSPtr);

};