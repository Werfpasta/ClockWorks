#if !defined(CW_INCLUDE_STD_NEW)
#define CW_INCLUDE_STD_NEW
void* operator new(size_t size){return malloc(size);}
void* operator new(size_t, void* ptr){return ptr;}  // Placement
void* operator new[](size_t const size){return operator new(size);}
void  operator delete(void*, void*) {} // Placement
void  operator delete(void* p) noexcept {/*free(p);*/}
void  operator delete[](void* p) noexcept {operator delete(p);}
#endif