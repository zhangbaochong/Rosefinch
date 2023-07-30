module;

export module Editor;
import <iostream>;

namespace Rosefinch
{
    export class Editor
    {
    public:
        Editor() {}
        virtual ~Editor() {}

        void Run()
        {
            std::cout << "Editor Run" << std::endl;
        }
    };
}