#include <list>
#include <iostream>
#include <algorithm>

class Subject;

class Observer
{
public:
    // pointer to Subject is passed so ConcreteObserver can distinct ConcreteSubjects
    virtual void update(Subject*) = 0;
};

class Subject
{
public:
    void registerObserver(Observer* const o)
    {
        std::list<Observer*>::const_iterator it = std::find(observers_.begin(), observers_.end(), o);
        if(it != observers_.end())
            throw std::runtime_error("Observer already registered");
        observers_.push_back(o);
    }

    void unregisterObserver(Observer* const o)
    {  
        std::list<Observer*>::const_iterator it = std::find(observers_.begin(), observers_.end(), o);
        if(it != observers_.end())
            observers_.remove(o);      
    }

    void notify()
    {
        std::list<Observer*>::const_iterator it = observers_.begin();
        for(; it != observers_.end(); ++it)
            (*it)->update(this);
    }

protected:
    std::list<Observer*> observers_;
};

// Concrete Subject 1
class PropertyOwner1 : public Subject
{
    int property1_;
    float property2_;

public:

    PropertyOwner1() : property1_(0), property2_(0.0f){}

    void property1(int n)
    {
        if(n != property1_)
        {
            property1_ = n;
            std::cout << "\nPropertyOwner1: property1's new value is: " << property1_ << std::endl;          
            notify();       
        }    
    }      
    
    int property1() const { return property1_;}      
    void property2(float n)    
    {       
        if(n != property2_)       
        {          
            property2_ = n;          
            std::cout << "\nPropertyOwner1: property2's new value is: " << property2_ << std::endl;          
            notify();       
        }    
    }     
    
    float property2() const { return property2_;} 
};  

// Concrete Subject 2 
class PropertyOwner2 : public Subject 
{    
    bool property1_;    
    double property2_;  
public:     
    PropertyOwner2() : property1_(false), property2_(0.0){}     
    void property1(bool n)    
    {       
        if(n != property1_)       
        {          
            property1_ = n;          
            std::cout << "\nPropertyOwner2: property1's new value is: " << property1_ << std::endl;          
            notify();       
        }
    }      
    
    bool property1() const { return property1_;}      
    void property2(double n)    
    {       
        if(n != property2_)       
        {          
            property2_ = n;          
            std::cout << "\nPropertyOwner2: property2's new value is: " << property2_ << std::endl;          
            notify();       
        }    
    }     
    
    double property2() const { return property2_;} 
};  

// Concrete Observer 
// observes changes in property1 of PropertyOwner1 and  
// property2 of PropertyOwner2 
class PropertyObserver1 : public Observer 
{    
    // ConcreteObserver knows about ConcreteSubjects    
    PropertyOwner1* pPropertyOwner1_;    
    PropertyOwner2* pPropertyOwner2_;  
public:     
    PropertyObserver1(PropertyOwner1* pConcreteSubject1, PropertyOwner2* pPropertyOwner2) :        
        pPropertyOwner1_(pConcreteSubject1), pPropertyOwner2_(pPropertyOwner2){}     
    void update(Subject* pSubject)    
    {       
        if(pSubject == pPropertyOwner1_)       
        {          
            int property1 = pPropertyOwner1_->property1();
            std::cout << "\tPropertyObserver1: PropertyOwner1 property1's value is: " << property1 << std::endl;       
        }       
        else if(pSubject == pPropertyOwner2_)       
        {          
            double property2 = pPropertyOwner2_->property2();
            std::cout << "\tPropertyObserver1: PropertyOwner2 property2's value is: " << property2 << std::endl;       
        }    
    } 
};  

// Concrete Observer 
// observes changes in property2 of PropertyOwner1 and  
// property1 of PropertyOwner2 
class PropertyObserver2 : public Observer 
{         
    PropertyOwner1* pPropertyOwner1_; 	
    PropertyOwner2* pPropertyOwner2_;  	
public:  		
    PropertyObserver2(PropertyOwner1* pPropertyOwner1, PropertyOwner2* pPropertyOwner2) :  		
        pPropertyOwner1_(pPropertyOwner1), pPropertyOwner2_(pPropertyOwner2){}  	
    void update(Subject* pSubject) 	
    { 		
        if(pSubject == pPropertyOwner1_) 		
        { 			
            float property2 = pPropertyOwner1_->property2();
            std::cout << "\tPropertyObserver2: PropertyOwner1 property2's value is: " << property2 << std::endl; 		
        } 		
        else if(pSubject == pPropertyOwner2_) 		
        { 			
            bool property1 = pPropertyOwner2_->property1();
            std::cout << "\tPropertyObserver2: PropertyOwner2 property1's value is: " << property1 << std::endl; 		
        } 	
    } 
};  

int main(int argc, char** argv) 
{         
    PropertyOwner1 propertyOwner1; 	
    PropertyOwner2 propertyOwner2;  	
    PropertyObserver1 propertyObserver1(&propertyOwner1, &propertyOwner2); 	
    PropertyObserver2 propertyObserver2(&propertyOwner1, &propertyOwner2);  	
    // register observers 	
    propertyOwner1.registerObserver(&propertyObserver1); 	
    propertyOwner1.registerObserver(&propertyObserver2); 	
    propertyOwner2.registerObserver(&propertyObserver1); 	
    propertyOwner2.registerObserver(&propertyObserver2);  	
    propertyOwner1.property1(1); 	
    propertyOwner1.property2(1.2f);  	
    propertyOwner2.property1(true);
    propertyOwner2.property2(3.4);
    // unregister observer1
    propertyOwner1.unregisterObserver(&propertyObserver1);
    propertyOwner1.property1(2);	
    propertyOwner1.property2(4.5);
}