#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include "JNIFoo.h"

JNIEXPORT jstring JNICALL Java_JNIFoo_nativeFoo (JNIEnv *env, jobject obj)
{
  int i;
  int ds_ret = 0;
  char * newstring;

  jstring ret = 0;

  newstring = (char *) malloc(30);

  if(newstring == NULL) 
  {      
      return ret;
  }

  memset(newstring, 0, 30);  
  
  newstring = "foo: yo wusup JNI.\\n";
   

  ret = (*env)->NewStringUTF(env, newstring);

  //free(newstring); // this hammers the runtime
  return ret;
}

