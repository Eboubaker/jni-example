#include <jni.h>      // JNI header provided by JDK
#include <stdio.h>    // C Standard IO Header
#include "bot_Decompress.h" // Generated
#include "miniz.h"

unsigned char *zipDecompress(unsigned char *inCompressedData,
                             int inCompressedDataLength,
                             int inExpectedResultDataLength, char* error)
{

    unsigned char *dataBuffer =
        new unsigned char[inExpectedResultDataLength];

    mz_ulong actualDataLength = inExpectedResultDataLength;

    int cmp_status = uncompress(dataBuffer, &actualDataLength,
                                inCompressedData, inCompressedDataLength);

    if (cmp_status != Z_OK)
    {
        sprintf(error, "zipDecompress failed: %d\n", cmp_status);
        delete[] dataBuffer;
        return NULL;
    }
    if ((int)actualDataLength != inExpectedResultDataLength)
    {
        sprintf(error, "zipDecompress expecting %d result bytes, got %d\n", inExpectedResultDataLength, (int)actualDataLength);
        delete[] dataBuffer;
        return NULL;
    }

    return dataBuffer;
}


JNIEXPORT jbyteArray JNICALL Java_bot_Decompress_bytes(JNIEnv * env, jclass klass, jbyteArray jbytes, jint size, jint expectedSize)
{
    jboolean isCopy;
    unsigned char *chars = (unsigned char *)env->GetByteArrayElements(jbytes, &isCopy);
    char *error;
    unsigned char *decompressed = zipDecompress(chars, size, expectedSize, error);
    env->ReleaseByteArrayElements(jbytes, (jbyte *)chars, 0);
    if(decompressed == NULL){
        jclass ioExceptionClass = env->FindClass("java/io/IOException");
        env->ThrowNew(ioExceptionClass, error);
        return NULL;
    }
    jbyteArray res = env->NewByteArray(expectedSize);
    env->SetByteArrayRegion(res, 0, expectedSize, (jbyte*)decompressed);
    return res;
}