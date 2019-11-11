
#include <dlfcn.h>
#include "overload.hpp"

typedef void (*func_t)(int);

void Foo_dl()
{
    void *handle = dlopen("./libc.so", RTLD_LAZY);
    func_t foo_ptr = NULL;
    if (NULL == handle)
    {
        puts("open failed\n");
    }

    foo_ptr = (func_t)dlsym(handle, "_Z3Fooi");
    if (NULL == foo_ptr)
    {
        puts("dlsym failed\n");
    }

    foo_ptr(7);

    dlclose(handle);
}