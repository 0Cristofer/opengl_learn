//
// Created by crist on 14/01/2021.
//

#ifndef OPENGL_LEARN_TEST_HPP
#define OPENGL_LEARN_TEST_HPP

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
}

#endif //OPENGL_LEARN_TEST_HPP
