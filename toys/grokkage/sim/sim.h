#ifndef __sim_h__
#define __sim_h__

//#ifdef __cplusplus
//extern "C" {
//#endif


enum {
    ERROR_SUCCESS,
    ERROR_NO_DEVS,
    ERROR_PENDING
};


int sim_startup();
int add_device(struct device *dev);


//#ifdef __cplusplus
//}  //extern "C"
//#endif

#endif
