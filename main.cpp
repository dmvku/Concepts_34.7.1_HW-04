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
    /*virtual ~Test() = default; bad destructor

    std::string hash()
    {
        return "Bad function";
    }

    bool toString()
    {
        return false; // bad function
    }*/

    int hash()
    {
        return 'S';
    }
    
    std::string toString()
    {
        return "This method returns <std::string>";
    }


};

template <ComplexConcept T>
void outClass(T& obj)
{
    std::cout << "This method returns an <int> from an ASCII character 'S' - "
        << obj.hash() << "\nthat can be converted to a <long>.\n\n";
    std::cout << obj.toString() << "\n";
}

int main()
{
    static_assert(ComplexConcept<Test>);
    
    Test t;
    outClass(t);

    return 0;
}