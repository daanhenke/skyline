#pragma once

#include <common/numeric.hh>

void* operator new(size_t count);
void operator delete(void* ptr) noexcept;

void* operator new[](size_t count);
void operator delete[](void* ptr) noexcept;
