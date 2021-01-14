//
// Created by crist on 14/01/2021.
//

#ifndef OPENGL_LEARN_TEST_HPP
#define OPENGL_LEARN_TEST_HPP

#include <vector>
#include <string>
#include <functional>
#include <iostream>

namespace Test
{
    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTestPointer);

        void OnImGuiRender() override;

        template<typename T>
        void RegisterTest(const std::string& name)
        {
            std::cout << "Registering test: " << name << std::endl;

            m_Tests.push_back(std::make_pair(name, []() { return new T(); }));
        }

    private:
        Test*& m_CurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
    };
}

#endif //OPENGL_LEARN_TEST_HPP
