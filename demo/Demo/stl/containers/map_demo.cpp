#include "../../include/stl/containers/map_demo.h"
#include <map>
#include <string>
#include <cassert>
#include <exception>
#include <iostream>

namespace 
{

std::map<std::string, int> CreatePersonsMap() {
    return std::map<std::string, int> {
        { "Amy", 1 },
        { "Bryan", 2 },
        { "Chloe", 3}
    };
}

}

void MapDemo::Demo() 
{
    Initialization();
    Querying();
}

void MapDemo::Initialization()
{
    auto persons = CreatePersonsMap();

    assert(persons["Bryan"] == 2);
}

void MapDemo::Querying()
{
    auto persons = CreatePersonsMap();

    // 
    // std::map::find() 
    // 

    // std::map::find() returns std::map::end() if the key doesn't exist and
    // no extra key is added.
    
    // key "Tilly" does not exist in map
    assert(persons.find("Tilly") == persons.end());
    
    try {

        //
        // std::map::operator[] 
        // T& operator[](const key_type& x)
        //
        
        // map::operator[] searches the map for a value corresponding to the 
        // given key, and returns a reference to it. If it can't find one it 
        // creates a default constructed element for it.
        auto tilly_id = persons["Tilly"];

        // key "Tilly" now exists in map!
        std::cout << "tilly_id: " << tilly_id << std::endl; // 0
        assert(persons.find("Tilly") != persons.end());
    } catch(const std::exception& e) {
        std::cout << "Exception thrown: " << e.what() << std::endl;
    }

    //
    // std::map::at()
    //

    // key "Milly" does not exist in map
    assert(persons.find("Milly") == persons.end());

    try {
        auto milly_id = persons.at("Milly");
    } catch(const std::exception& e) {
        // exception message: invalid map<K, T> key (VC++)
        std::cout << "Exception thrown: " << e.what() << std::endl;
    }

}
