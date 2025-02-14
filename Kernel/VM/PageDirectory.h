/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/RefCounted.h>
#include <AK/RefPtr.h>
#include <Kernel/Forward.h>
#include <Kernel/VM/PhysicalPage.h>
#include <Kernel/VM/RangeAllocator.h>

namespace Kernel {

class PageDirectory : public RefCounted<PageDirectory> {
    friend class MemoryManager;

public:
    static RefPtr<PageDirectory> try_create_for_userspace(RangeAllocator const* parent_range_allocator = nullptr);
    static NonnullRefPtr<PageDirectory> must_create_kernel_page_directory();
    static RefPtr<PageDirectory> find_by_cr3(FlatPtr);

    ~PageDirectory();

    void allocate_kernel_directory();

    FlatPtr cr3() const
    {
#if ARCH(X86_64)
        return m_pml4t->paddr().get();
#else
        return m_directory_table->paddr().get();
#endif
    }

    RangeAllocator& range_allocator() { return m_range_allocator; }
    const RangeAllocator& range_allocator() const { return m_range_allocator; }

    RangeAllocator& identity_range_allocator() { return m_identity_range_allocator; }

    Space* space() { return m_space; }
    const Space* space() const { return m_space; }

    void set_space(Badge<Space>, Space& space) { m_space = &space; }

    RecursiveSpinLock& get_lock() { return m_lock; }

private:
    PageDirectory();

    Space* m_space { nullptr };
    RangeAllocator m_range_allocator;
    RangeAllocator m_identity_range_allocator;
#if ARCH(X86_64)
    RefPtr<PhysicalPage> m_pml4t;
#endif
    RefPtr<PhysicalPage> m_directory_table;
#if ARCH(X86_64)
    RefPtr<PhysicalPage> m_directory_pages[512];
#else
    RefPtr<PhysicalPage> m_directory_pages[4];
#endif
    HashMap<FlatPtr, RefPtr<PhysicalPage>> m_page_tables;
    RecursiveSpinLock m_lock;
};

}
