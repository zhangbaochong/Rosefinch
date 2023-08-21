#pragma once
#include "Framework/Core/Layer/Layer.h"

namespace Rosefinch
{
    class EditorLayer : public Layer
    {
    public:
        EditorLayer();
        ~EditorLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate(float deltaTime) override;
        virtual void OnEvent(Event& event) override;

    private:
        
    };
}