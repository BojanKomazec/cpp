// Bojan Komazec, 2017
// Demo project to show use of some modern C++ features.
// 
// Topics covered:
//
// auto
// lambda
// lvalue, prvalue, xvalue, glvalue, rvalue
// std::function
// std::move
// std::shared_ptr

#include <iostream>
#include <memory>
#include <fstream>
#include <vector>

class DemoSharedPtr
{
    class A
    {

    private:

        std::shared_ptr<int> m_pInt;

    public:

        A(std::shared_ptr<int> pInt)
        {
            m_pInt = pInt;
        }
    };

public:

    void Demo()
    {
        auto pInt = std::shared_ptr<int>(new int(123));

        {
            A a1(pInt);
            std::cout << "std::shared_ptr use_count() = " << pInt.use_count() << std::endl;            
        }
        
        std::cout << "std::shared_ptr use_count() = " << pInt.use_count() << std::endl;
    }
};

class DemoFileRead
{

public:

    void Demo()
    {
        char const* file_name = "test.txt";

        std::ifstream dataset(file_name);
        if (!dataset)
            throw std::runtime_error(std::string(file_name) + ": error: can't open dataset!");

        ReadRecord(dataset);        
    }

private:

    std::vector<uint8_t> ReadRecord( std::istream & stream )
    {
        if (!stream)
            return std::vector<uint8_t>();

        std::vector<uint8_t> result(4);
        stream.read(reinterpret_cast<char*>(result.data()), 4);

        return std::move(result);
    }
};

int main()
{
    std::cout << "main()" << std::endl;

    DemoSharedPtr d;
    d.Demo();

    return 0;
}


