#ifndef IOC_INIT_H
#define IOC_INIT_H

#include <commands/command.h>
#include <ioc.h>
#include <iostream>

namespace engine
{
    class ioc_init : public command
    {
        static bool isInit;

        class register_dependency : public command
        {
            std::any func;
            std::string_view str;

        public:
            explicit register_dependency(std::string_view str, std::any func) : func(func), str(str)
            {
            }
            void execute() override
            {
                // std::cout << "register dep: " << str << " f_name: " << func.type().name()<<std::endl;
                auto isEmplaced = ioc::resolve<ioc::scope>("IoC.Scope.Current")->emplace(str, func).second;
                if(!isEmplaced)
                    throw std::runtime_error(std::string(str)+std::string("has been already set"));
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

    public:
        void execute() override;
    };

    class ioc::scoped_ioc
    {
        ioc::scope_ptr scope;
    public:
        scoped_ioc()
        {
            scope = ioc::resolve<ioc::scope, ioc::scope_ptr>("IoC.Scope.Create", nullptr);
            ioc::resolve<command>("IoC.Scope.Current.Set", scope)->execute();
        }

        ~scoped_ioc()
        {
            auto parentScope = ioc::resolve<ioc::scope>("IoC.Scope.Parent");
            ioc::resolve<command>("IoC.Scope.Current.Set", parentScope)->execute();
            ioc::resolve<command>("IoC.Scope.Current.Clear", scope)->execute();
        }
    };

} // namespace engine

#endif // IOC_INIT_H
