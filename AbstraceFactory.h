#ifndef __ABSTRACEFACTORY_H__
#define __ABSTRACEFACTORY_H__

#include <memory>
#include <typeindex>
#include <unordered_map>
#include <string>
#include <functional>

#include "Function_traits.h"
#include "Any.h"

class AbstraceFactory {
public:
    virtual ~AbstraceFactory() {
    }

    template<typename FactoryInstance>
    static void insertFactory(const std::string&& factoryName, FactoryInstance&& f) {
        auto func = to_function(std::forward<FactoryInstance>(f));
        s_factoryClassCon.emplace(factoryName, func);
    }

    template<typename Ret>
    static Ret getObject(const std::string& factoryName) {
        if(!s_factoryClassCon.count(factoryName)) {
            throw std::logic_error("NOT FIND FactoryName");
        }
        using functionType = std::function<Ret()>;
        auto f = s_factoryClassCon[factoryName].AnyCast<functionType>();
        return f();
    }

    template<typename Ret, typename... Args>
    static Ret getObject(const std::string& factoryName, Args&&... args) {
        if(!s_factoryClassCon.count(factoryName)) {
            throw std::logic_error("NOT FIND FactoryName");
        }
        using functionType = std::function<Ret(Args...)>;
        auto f = s_factoryClassCon[factoryName].AnyCast<functionType>();
        return f(std::forward<Args>(args)...);
    }
    
private:
    static std::unordered_map<std::string, Any> s_factoryClassCon;
};

#endif
