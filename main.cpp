#include <concepts>
#include <string>
#include <type_traits>
#include <iostream>

template <typename T>
concept ComplexConcept = requires (T obj)
{
    { obj.hash() } -> std::convertible_to<long>;
    { obj.toString() } -> std::same_as<std::string>;
    requires (!std::has_virtual_destructor<T>());
};

class Test
{
    public:
    Test() {}
    ~Test() {}
    //virtual ~Test() = default;

    int hash()
    {
       return 'S';
    }

    std::string toString()
    {
        return "This method returns <std::string>";
    }
};

int main()
{
    static_assert(ComplexConcept<Test>);
    
    Test t;
    std::cout << "This method returns an <int> that is converted " 
        << "to a <long>\n\tfrom an ASCII character 'S' - " << t.hash() << "\n";
    std::cout << t.toString() << "\n";

    return 0;
}