#ifndef _POLYMORPHISM_DEMO_H_
#define _POLYMORPHISM_DEMO_H_

class Base
{
public:
    virtual void Foo() const;
};

class Derived1 : public Base
{
public:
    void Foo() const override;
};

class Derived2 : public Base
{
public:
    void Foo() const override;
};

class PolymorphismDemo
{
public:
    void Demo();
private:
    void SlicingDemo();
    void CallVirtualMethodOnBasePassedByValue(Base base);
    void CallVirtualMethodOnBasePassedByReference(const Base& base);
};

#endif // _POLYMORPHISM_DEMO_H_