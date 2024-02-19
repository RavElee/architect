#ifndef IOC_INIT_H
#define IOC_INIT_H

#include <commands/command.h>
#include <ioc.h>
#include <iostream>

namespace engine
{
    class register_dependency : public command
    {
        std::any &func;
        std::string_view &str;

    public:
        explicit register_dependency(std::string_view &str, std::any &func) : func(func), str(str)
        {
        }
        void execute() override
        {
            ioc::resolve<ioc::scope>("IoC.Scope.Current")->emplace(str, func);
        }
    };

    class clear_current_scope : public command
    {
        ioc::scope_ptr scope;

    public:
        explicit clear_current_scope(ioc::scope_ptr scope) : scope(scope)
        {
        }

        void execute() override
        {
            scope->clear();
            scope.reset();
        }
    };

    class set_current_scope : public command
    {
        ioc::scope_ptr scope;

    public:
        explicit set_current_scope(ioc::scope_ptr scope) : scope(scope)
        {
        }

        void execute() override
        {
            ioc::currentScope = scope;
        }
    };

    class ioc_init : public command
    {
    public:
        void execute() override
        {
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
                                        throw std::exception();
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
        }
    };
} // namespace engine

#endif // IOC_INIT_H
