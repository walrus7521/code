#include <libkern/libkern.h>
#include <mach/mach_types.h>

kern_return_t MyFirstKernelExtensionStart(kmod_info_t *ki, void *d) {
    printf(“Hello, World!\n”);
    return KERN_SUCCESS;
}

kern_return_t MyFirstKernelExtensionStop(kmod_info_t *ki, void *d) {
    printf(“Goodbye, World!\n”);
    return KERN_SUCCESS;
}


