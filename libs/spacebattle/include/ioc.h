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
        friend class ioc_init;

    public:
        class scoped_ioc;

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
                        throw std::runtime_error(std::string(dependency) + std::string("dependency doesn't register"));

                    scopeLocal = std::any_cast<strategy<ioc::scope>>(scopeLocal->at("IoC.Scope.Parent"))();
                    strategyLocal = scopeLocal->find(dependency);
                    if (strategyLocal != scopeLocal->end())
                        break;
                }
            // std::cout << "dep: "<< dependency << " strategy.second: " << strategyLocal->second.type().name() <<
            // std::endl;
            return std::any_cast<strategy<T, Args...>>(strategyLocal->second)(args...);
        }

    private:
        static scope_ptr rootScope;
        static thread_local scope_ptr currentScope;
    };

#define IOC_REGISTER(dependency_name, lambda)                                                                          \
    engine::ioc::resolve<engine::command, std::string_view, std::any>("IoC.Register", dependency_name, lambda)         \
        ->execute();

#define QUOTE(x) #x
#define LAMBDA_HELPER(base, ...) (engine::ioc::strategy<base, __VA_ARGS__>)

#define IOC_REGISTER_ADAPTER(base_name)                                 \
    engine::ioc::resolve<engine::command, std::string_view, std::any>(  \
        "IoC.Register", QUOTE(base_name##_adapter),                     \
        LAMBDA_HELPER(base_name, engine::uobject &)[](engine::uobject & obj) { \
            return std::make_shared<base_name##_adapter>(obj);          \
        })                                                              \
    ->execute();

#define IOC_RESOLVE_ADAPTER(base_name, object) ioc::resolve<base_name, uobject &>(QUOTE(base_name##_adapter), object)






} // namespace engine
#endif // IOC_H
