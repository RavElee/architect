#ifndef IOC_H
#define IOC_H

#include <any>
// #include <string>
#include <functional>
#include <iostream>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace engine
{
    // invertion of control
    class ioc
    {
    public:
        using scope = std::unordered_map<std::string_view, std::any>;
        using scope_ptr = std::shared_ptr<scope>;


        template <class T, class... Args>
        using strategy = std::function<std::shared_ptr<T>(Args...)>;

        template <class T, class... Args>
        static std::shared_ptr<T> resolve(const std::string_view &dependency, Args... args)
        {
            auto scopeLocal = currentScope ? currentScope : rootScope;
            auto strategyLocal = scopeLocal->find(dependency);
            if (strategyLocal == scopeLocal->end())
                while (true)
                {
                    if (scopeLocal == rootScope)
                        throw std::exception();

                    scopeLocal = std::any_cast<strategy<ioc::scope>>(scopeLocal->at("IoC.Scope.Parent"))();
                    strategyLocal = scopeLocal->find(dependency);
                    if (strategyLocal != scopeLocal->end())
                        break;
                }
            return std::any_cast<strategy<T, Args...>>(strategyLocal->second)(args...);
        }

    // private:
        static scope_ptr rootScope;
        static thread_local scope_ptr currentScope;
    };
    ioc::scope_ptr ioc::rootScope = std::make_shared<ioc::scope>();
    thread_local ioc::scope_ptr ioc::currentScope = nullptr;

} // namespace engine
#endif // IOC_H
