#include "include/lambda_demo.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

namespace {
    class Engine {
    public:
        typedef void (*TemperatureChangedEventHandlerType)(int temperature);

        void SetTemperature(int temperature){
            temperature_ = temperature;
            handler_(temperature_);
        }

        void SetTemperatureChangedEventHandler(
            TemperatureChangedEventHandlerType handler) {
                handler_ = handler;
            }

    private:
        int temperature_ = 0;
        int pressure_ = 0;
        TemperatureChangedEventHandlerType handler_;
    };

    class EngineMonitor {
    public:
        // Member function used as a callback in this example has to be declared
        // as 'static' in order to loose 'this' as the first argument so can 
        // match the desired callback function type.
        static void TemperatureChanged(int temperature) {
            if (temperature > 80) {
                std::cout 
                    << "EngineMonitor::TemperatureChanged(): Temperature above the threshold!" 
                    << std::endl;
            }
        }
    };

    void TemperatureChanged2(int temperature) {
        if (temperature > 80) {
            std::cout 
                << "TemperatureChanged2(): Temperature above the threshold!" 
                << std::endl;
        }
    }

    class C {
    public:
        int operator()(std::string s) {
            return s.length();
        }
    };
}

void LambdaDemo::Demo()
{
    int length = C()("test");
    assert(length == 4);

    DefineAndCallFunctionInOneGo();
    PassLambdaAsFunctionArgumentDemo();
    EventHandlerDemo();
}

// [...] - capture clause (capture list) - defines which variables from the 
//         outer scope can be accessible from the lambda and how (by value or by
//         reference)
// (...) - argument list - lambda arguments
// {...} - lambda function body
void LambdaDemo::DefineAndCallFunctionInOneGo()
{
    // define and execute
    [](){ 
        std::cout << "Lambda_1" << std::endl;
    }();

    // this is allowed
    [](){}();

    // we can save lambda in an object and invoke it later
    auto lambda2 = [](int i){ std::cout << "Lambda_2: " << i << std::endl; };
    lambda2(222);

    // lambda captures local variable by value
    int j = 333;
    [j]() mutable {
        // (!)
        // if 'mutable' is ommitted: 
        // error: increment of read-only variable ‘j’
        std::cout << "Lambda_3: " << ++j << std::endl;
        assert(j == 334); 
    }(); 
    assert(j == 333);

    // lambda captures local variable by reference
    int k = 444;
    [&k](){ 
        std::cout << "Lambda_4: " << ++k << std::endl;
        assert(k == 445); 
    }(); 
    assert(k == 445);

    // lambda returns a value (non-void type)
    auto l = [](){ return 5; }();
    assert(l == 5);
}

void LambdaDemo::PassLambdaAsFunctionArgumentDemo()
{
    std::vector<int> v = { 3, 6, 1, 8, 2, 9 };
    std::sort(v.begin(), v.end());
    for(auto i : v) {
        std::cout << i << " ";
    }

    std::cout << std::endl;
}

void LambdaDemo::EventHandlerDemo()
{
    Engine engine;
    engine.SetTemperatureChangedEventHandler(EngineMonitor::TemperatureChanged);
    engine.SetTemperature(12);
    engine.SetTemperature(81);
    engine.SetTemperatureChangedEventHandler(TemperatureChanged2);
    engine.SetTemperature(82);

    // set lambda as an event handler
    engine.SetTemperatureChangedEventHandler(
        [](int temperature){
            if (temperature > 80) {
                std::cout 
                    << "lambda(): Temperature above the threshold!" 
                    << std::endl;
            }
        });
    engine.SetTemperature(83);
}

//void LambdaDemo::Functor() {
//}