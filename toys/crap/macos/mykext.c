#include <mach/mach_types.h>
#include <libkern/libkern.h>

/*
 * ind: /Library/Caches/com.google.SoftwareUpdate.0: Permission denied
/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/System/Library/Frameworks/Kernel.framework/Versions/A/Headers/libkern/libkern.h

 * https://craftware.xyz/tips/Building-kernel-extension.html
*/


kern_return_t mykext_start(kmod_info_t * ki, void *d);
kern_return_t mykext_stop(kmod_info_t *ki, void *d);

kern_return_t mykext_start(kmod_info_t * ki, void *d)
{
    printf("Hello World!\n");
    
    return KERN_SUCCESS;
}

kern_return_t mykext_stop(kmod_info_t *ki, void *d)
{
    printf("Goodbye World!\n");
    
    return KERN_SUCCESS;
}

