//
// Created by crist on 14/01/2021.
//

#ifndef OPENGL_LEARN_TESTCLEARCOLOR_HPP
#define OPENGL_LEARN_TESTCLEARCOLOR_HPP

#include "Test.hpp"

namespace Test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor() override;

        void OnUpdate(float deltaTime) override;

        void OnRender() override;

        void OnImGuiRender() override;

    private:
        float m_ClearColor[4];
    };
}



#endif //OPENGL_LEARN_TESTCLEARCOLOR_HPP
