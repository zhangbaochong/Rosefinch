#pragma once

#include "Framework/Core/Base.h"
#include "Framework/Function/Render/RHI/PipelineDesc.h"

namespace Rosefinch
{
    // Per platform/API implementation of PipelineObject
    class PipelineObjectInternal;

    /**
     * @class PipelineObject
     * 
     * The pipeline object instance used to execute GPU workloads
    */
    class PipelineObject
    {
    public:
        /**
         * PipelineObject instance creation function. Implemented per api/platform to return 
         * the correct internal resource type
        */
        static PipelineObject* CreatePipelineObject(const char* pipelineObjectName, const PipelineDesc* desc, std::vector<const char*>* pAdditionalParameters=nullptr);

        virtual ~PipelineObject() = default;

        /**
         * Return the PipelineType, Graphics or Compute
        */
        PipelineType GetPipelineType() const { return m_Type; }

        /**
         * Return the PipelineDesc description used to create the pipeline.
        */
        const PipelineDesc& GetDesc() { return m_Desc; }

        const char* GetName() const { return m_Name.c_str(); }

        virtual PipelineObjectInternal* GetImpl() = 0;
        virtual const PipelineObjectInternal* GetImpl() const = 0;

    private:
        NO_COPY(PipelineObject)
        NO_MOVE(PipelineObject)

    protected:
        PipelineObject(const char* pipelineObjectName) : m_Name(pipelineObjectName) {}
        PipelineObject() = delete;

        std::string m_Name = "";
        PipelineType m_Type = PipelineType::Undefined;
        PipelineDesc m_Desc;
    };

} // namespace Rosefinch