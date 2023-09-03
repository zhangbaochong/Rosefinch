#pragma once

namespace Rosefinch
{
    /**
     * An enumeration of indirect workload types
     */
    enum class IndirectCommandType
    {
        Draw = 0,    // Indirect Draw workload
        DrawIndexed, // Indirect DrawIndexed workload
        Dispatch     // Indirect Dispatch workload
    };

    /**
     * @class IndirectWorkload
     *
     * A structure encapsulating an indirect workload to execute
     */
    class IndirectWorkload
    {
    public:
        /**
         * IndirectWorkload isntance creation function. Implemented per api/platform to return
         * the correct internal implementation
         */
        static IndirectWorkload *CreateIndirectWorkload(const IndirectCommandType &type);
    
        IndirectWorkload() = default;

        virtual ~IndirectWorkload() = default;
    };
    
} // namepace Rosefinch