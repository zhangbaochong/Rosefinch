module;

export module Editor;
import <iostream>;
import Log;

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

            Log log;
            log.log();
        }
    };
}