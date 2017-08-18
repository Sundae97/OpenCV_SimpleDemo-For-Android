#include <string>
#include "com_sundae_ndktest_MainActivity.h"
#include <opencv2/opencv.hpp>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_sundae_ndktest_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    hello += hello;
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jint JNICALL Java_com_sundae_ndktest_MainActivity_getStringLength(
        JNIEnv *env,
        jobject obj,
        jstring str){
    jboolean jbool;
    char* str1 = (char *) env->GetStringUTFChars(str , &jbool);
    size_t size = strlen(str1);
    return size;
}

JNIEXPORT jobjectArray JNICALL Java_com_sundae_ndktest_MainActivity_getBitmap
        (JNIEnv *env, jobject jobj , jint w , jint h , jint color){
    int width = w;
    int height = h;

    jclass jClass = env->FindClass("[I");
    if(jClass == NULL) return NULL;

    jobjectArray jObjArr = env->NewObjectArray(w , jClass , NULL);

    jint tmp[h];
    for(int i = 0; i<w ; i++)
    {
        jintArray intArr = env->NewIntArray(h);
        for(int k = 0; k<h ; k++)
            tmp[k] = color;

        env->SetIntArrayRegion(intArr , 0 , h , tmp);
        env->SetObjectArrayElement(jObjArr , i ,intArr);
        env->DeleteLocalRef(intArr);
    }
    return jObjArr;
}

JNIEXPORT jintArray JNICALL Java_com_sundae_ndktest_MainActivity_getGrayImage
        (JNIEnv *env, jobject jobj, jintArray _pixels, jint width, jint height){

    jint *pixels = env->GetIntArrayElements(_pixels , NULL);
    if(pixels==NULL){
        return NULL;
    }
    cv::Mat imgData(height , width , CV_8UC4 , pixels);

    uchar *ptr = imgData.ptr(0);

    for (int i = 0; i < width * height; i++) {
        int grayScale = (int) (ptr[4 * i + 2] * 0.299 + ptr[4 * i + 1] * 0.587
                               + ptr[4 * i + 0] * 0.114);
        ptr[4 * i + 1] = (uchar) grayScale;
        ptr[4 * i + 2] = (uchar) grayScale;
        ptr[4 * i + 0] = (uchar) grayScale;
    }

    int size = width * height;
    jintArray result = env->NewIntArray(size);
    env->SetIntArrayRegion(result, 0, size, pixels);
    env->ReleaseIntArrayElements(_pixels, pixels, 0);
    return result;

}

