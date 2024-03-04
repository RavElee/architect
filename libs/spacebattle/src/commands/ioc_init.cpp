#include <commands/ioc_init.h>

namespace engine {
    bool ioc_init::isInit = false;

    void ioc_init::execute()
    {
        if(isInit)
            return;

        ioc::rootScope->emplace("IoC.Scope.Current.Set",
                                (ioc::strategy<command, ioc::scope_ptr>)
                                [](ioc::scope_ptr newScope) {
                                    return std::make_shared<set_current_scope>(newScope);
                                });

        ioc::rootScope->emplace("IoC.Scope.Current.Clear",
                                (ioc::strategy<command, ioc::scope_ptr>)
                                [](ioc::scope_ptr scope) {
                                    return std::make_shared<clear_current_scope>(scope);
                                });

        ioc::rootScope->emplace("IoC.Scope.Current",
                                (ioc::strategy<ioc::scope>)
                                []() {
                                    return ioc::currentScope ? ioc::currentScope : ioc::rootScope;
                                });

        ioc::rootScope->emplace("IoC.Scope.Parent",
                                (ioc::strategy<ioc::scope>)
                                []()->ioc::scope_ptr{
                                    // TODO: root scope doesn't have parent
                                    throw std::runtime_error("root scope doesn't have parent");
                                });

        ioc::rootScope->emplace("IoC.Scope.Create.Empty",
                                (ioc::strategy<ioc::scope>)
                                [](){
                                    return std::make_shared<ioc::scope>();
                                });

        ioc::rootScope->emplace("IoC.Scope.Create",
                                (ioc::strategy<ioc::scope, ioc::scope_ptr>)
                                [](ioc::scope_ptr parent = nullptr)->ioc::scope_ptr{
                                    auto creatingScope = ioc::resolve<ioc::scope>("IoC.Scope.Create.Empty");
                                    if (parent)
                                        creatingScope->emplace("IoC.Scope.Parent",
                                                               (ioc::strategy<ioc::scope>)
                                                               [parent]() ->ioc::scope_ptr {
                                                                   return parent;
                                                               });
                                    else
                                    {
                                        auto parentScope = ioc::resolve<ioc::scope>("IoC.Scope.Current");
                                        creatingScope->emplace("IoC.Scope.Parent",
                                                               (ioc::strategy<ioc::scope>)
                                                               [parentScope]()->ioc::scope_ptr{
                                                                   return parentScope;
                                                               });
                                    }
                                    return creatingScope;
                                });

        ioc::rootScope->emplace("IoC.Register",
                                (ioc::strategy<command, std::string_view, std::any>)
                                [](std::string_view str, std::any func) {
                                    return std::make_shared<register_dependency>(str, func);
                                });
        isInit = true;
    }
}
