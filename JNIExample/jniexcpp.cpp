#include <jni.h>
#include <cstring>
#include <cstdlib>

#include "JniEx.h"


JNIEXPORT jbyteArray JNICALL Java_JniEx_incBytes(JNIEnv *env, jclass cls, jbyteArray bs)
{
    int len = (int)(env->GetArrayLength(bs));
    unsigned char* bytes = new unsigned char[len];
    jbyteArray res;
    memcpy(bytes, (void*)(env->GetByteArrayElements(bs, 0)), len);
    int i;
    for (i = 0; i < len; i++) {
       bytes[i]++; 
    }
    res = env->NewByteArray(len);
    env->SetByteArrayRegion(res, 0, len, (jbyte*)bytes);
    delete [] bytes;
    return res;    
}
  
