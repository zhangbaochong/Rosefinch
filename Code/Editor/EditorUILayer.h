#pragma once
#include "Framework/Core/Layer/Layer.h"

namespace Rosefinch
{
    class EditorUILayer : public Layer
    {
    public:
        EditorUILayer();
        ~EditorUILayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(Event& event) override;
    };
}