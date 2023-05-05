#ifndef  __FUNCTION_TRAITS_H__
#define __FUNCTION_TRAITS_H__

#include <functional>
#include <tuple>

//转换为std::function和函数指针
template<typename T>
struct Function_traits;

//普通函数
template<typename Ret, typename... Args>
struct Function_traits<Ret(Args...)>
{
    enum {
        arity = sizeof...(Args)
    };
    typedef Ret function_type(Args...);
    typedef Ret return_type;
    using stl_function_type = std::function<function_type>;
    typedef Ret(*pointer)(Args...);

    template<size_t I>
    struct args {
        static_assert(I < arity, "index is out of range, index must less than sizeof Args");
        using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
    };
};

//函数指针
template<typename Ret, typename... Args>
struct Function_traits<Ret(*)(Args...)> : Function_traits<Ret(Args...)> {};

//std::function
template<typename Ret, typename... Args>
struct Function_traits<std::function<Ret(Args...)>> : Function_traits<Ret(Args...)> {};

//member function
#define FUNCTION_TAITS(...) \
    template<typename ReturnType, typename ClassType, typename... Args>\
    struct Function_traits<ReturnType(ClassType::*)(Args...) __VA_ARGS__> : Function_traits<ReturnType(Args...)> {}; \

FUNCTION_TAITS()
FUNCTION_TAITS(const)
FUNCTION_TAITS(volatile)
FUNCTION_TAITS(const volatile)

//函数对象
template<typename Callable>
struct Function_traits : Function_traits<decltype(&Callable::operator())> {};

template<typename Function>
typename Function_traits<Function>::stl_function_type to_function(const Function &lambda) {
    return static_cast<typename Function_traits<Function>::stl_function_type> (lambda);
}

template<typename Function>
typename Function_traits<Function>::stl_function_type to_function(Function&& lambda) {
    return static_cast<typename Function_traits<Function>::stl_function_type>(std::forward<Function>(lambda));
}

template<typename Function>
typename Function_traits<Function>::pointer to_function_pointer(const Function &lambda) {
    return static_cast<typename Function_traits<Function>::pointer>(lambda);
}
#endif
