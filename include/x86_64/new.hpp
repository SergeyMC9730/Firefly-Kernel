#pragma once

inline void *operator new(size_t, void *p)     throw() { return p; }
inline void *operator new[](size_t, void *p)   throw() { return p; }
//later
inline void  operator delete  ([[maybe_unused]] void *, [[maybe_unused]] void *) throw() { };
//later
inline void  operator delete[](void *, void *) throw() { };