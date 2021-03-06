#include <jni.h>
#include <string.h>
#include <stdlib.h>

#include "JniEx.h"


JNIEXPORT jbyteArray JNICALL Java_JniEx_incBytes(JNIEnv *env, jclass cls, jbyteArray bs)
{
    int len = (int)((*env)->GetArrayLength(env, bs));
    unsigned char* bytes = (unsigned char*)malloc(len*sizeof(unsigned char));
    jbyteArray res;
    unsigned char* arrPtr = (unsigned char*)((*env)->GetByteArrayElements(env, bs, 0));
    memcpy(bytes, arrPtr, len);
    int i;
    for (i = 0; i < len; i++) {
       bytes[i]++; 
    }
    sleep(5);
    res = (*env)->NewByteArray(env, len);
    (*env)->SetByteArrayRegion(env, res, 0, len, (jbyte*)bytes);
    (*env)->ReleaseByteArrayElements(env, bs, arrPtr, 0);
    free(bytes);
    return res;    
}
  
