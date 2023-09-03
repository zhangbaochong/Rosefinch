#pragma once
#include "Framework/Core/Base.h"

namespace Rosefinch
{
    /**
     * @class Ring
     *
     * This is the typical ring buffer, it is used by resources that will be reused.
     * For example the constant buffer pool.
     */
    class Ring
    {
    public:
        /**
         * Ring buffer creation. Pass in the max supported size
         */
        void Create(uint32_t totalSize)
        {
            m_Head = 0;
            m_AllocatedSize = 0;
            m_TotalSize = totalSize;
        }

        /**
         * Get the ring buffer's currently allocated size
         */
        uint32_t GetSize() { return m_AllocatedSize; }

        /**
         * Get the ring buffer's head location
         */
        uint32_t GetHead() { return m_Head; }

        /**
         * Get the ring buffer's tail location
         */
        uint32_t GetTail() { return (m_Head + m_AllocatedSize) % m_TotalSize; }

        /**
         * Helper to avoid allocating chunks that wouldn't fit contiguously in the ring
         */
        uint32_t PaddingToAvoidOver(uint32_t size)
        {
            int32_t tail = GetTail();
            if ((tail + size) > m_TotalSize)
            {
                return (m_TotalSize - tail);
            }
            else
            {
                return 0;
            }
        }

        /**
         * Allocation a new entry at the tail end of the ring buffer. Assert if we exceed the ring 
         * buffer's capacity
        */
        bool Alloc(uint32_t size, uint32_t* pOut)
        {
            RosefinchAssert(ASSERT_CRITICAL, m_AllocatedSize + size <= m_TotalSize, "Ring buffer capacity exceeded. Cannot allocate, please grow the ring buffer size.");
            if (m_AllocatedSize + size <= m_TotalSize)
            {
                if (pOut)
                {
                    *pOut = GetTail();
                }
                m_AllocatedSize += size;
                return true;
            }

            return false;
        }

        /**
         * Free memory from the head of the ring buffer
        */
        bool Free(uint32_t size)
        {
            if (m_AllocatedSize >= size)
            {
                m_Head = (m_Head + size) % m_TotalSize;
                m_AllocatedSize -= size;
                return true;
            }

            return false;
        }

    private:
        uint32_t m_Head;
        uint32_t m_AllocatedSize;
        uint32_t m_TotalSize;
    };

    /**
     * @class RingWithTabs
     * 
     * This class can be thought as ring buffer inside a ring buffer. The outer ring is for 
     * the frames and the internal one is for the resources that were allocated for that frame.
     * The size of the out ring is typically the number of back buffers.
     * 
     * When the outer ring is full, for the next allocation it automatically frees the entries
     * of the oldest frame and makes those entries available for the next frame. This happens
     * when you call BeginFrame.
    */
    class RingWithTabs
    {
    public:
        /**
         * Ring buffer creation. Takes the number of back buffers to support and
         * the amount of memory to support per frame.
        */
        void Create(uint32_t numberOfBackBuffers, uint32_t memTotalSize)
        {
            m_BackBufferIndex = 0;
            m_NumberOfBackBuffers = numberOfBackBuffers;

            // Init mem per frame tracker
            m_MemAllocatedInFrame = 0;
            for (int i = 0; i < 4; ++i)
            {
                m_AllocatedMemPerBackBuffer[i] = 0;
            }
            m_Mem.Create(memTotalSize);
        }

        /**
         * Destroy the ring buffer
        */
        void Destroy()
        {
            m_Mem.Free(m_Mem.GetSize());
        }

        /**
         * Allocate a new entry at the tail end of the ring buffer for the current frame.
         * Assert if we exceed the ring buffer's capacity.
        */
        bool Alloc(uint32_t size, uint32_t* pOut)
        {
            uint32_t padding = m_Mem.PaddingToAvoidOver(size);
            if (padding > 0)
            {
                m_MemAllocatedInFrame += padding;

                if (m_Mem.Alloc(padding, NULL) == false) // Alloc thunk to avoid crossover, ignore offset
                {
                    return false; // No mem, cannot allocate padding
                }
            }

            if (m_Mem.Alloc(size, pOut) == true)
            {
                m_MemAllocatedInFrame += size;
                return true;
            }

            return false;
        }

        /**
         * Set up the ring buffer for current frame allocations
        */
        void BeginFrame()
        {
            m_AllocatedMemPerBackBuffer[m_BackBufferIndex] = m_MemAllocatedInFrame;
            m_MemAllocatedInFrame = 0;

            m_BackBufferIndex = (m_BackBufferIndex + 1) % m_NumberOfBackBuffers;

            // Free all the entries for the oldest buffer in one go
            uint32_t memToFree = m_AllocatedMemPerBackBuffer[m_BackBufferIndex];
            m_Mem.Free(memToFree);
        }

    private:
        // Internal ring buffer
        Ring m_Mem;

        // This is the external ring buffer (could have reused the Ring class though)
        uint32_t m_BackBufferIndex;
        uint32_t m_NumberOfBackBuffers;

        uint32_t m_MemAllocatedInFrame;
        uint32_t m_AllocatedMemPerBackBuffer[4];
    };
}