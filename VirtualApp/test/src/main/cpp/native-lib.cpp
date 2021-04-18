#include <jni.h>
#include <string>
#include <android/log.h>
#include <asm/unistd.h>
#include <fcntl.h>
#include <unistd.h>


//D:\Android\SDK\ndk\android-ndk-r20b\toolchains\llvm\prebuilt\windows-x86_64\sysroot\usr\include\asm-generic\unistd.h
//D:\Android\SDK\ndk\android-ndk-r20b\toolchains\llvm\prebuilt\windows-x86_64\sysroot\usr\include\unistd.h
#define LOG_TAG "Vlog"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_test_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    const char* path= "/data/data/com.example.test/test.data";
    FILE* file = fopen(path,"r");
    if(file==NULL){
        LOGE("file open failed");
    }
    char buffer[1024]={0};
    while(fread(buffer, sizeof(char),1024,file)!=0){
        LOGE("content:%s",buffer);
    }
    if(file!=NULL){
        fclose(file);
    }

    char fbuffer[1024]={0};

    int fd = 0;
    int ret = static_cast<int>(syscall(__NR_openat, fd, path, O_RDWR, 0));
    LOGE("ret:%d",ret);
    ret = open(path,O_RDWR);
    LOGE("A ret:%d",ret);

    /*读取文件的值*/
    int iR = 0;
    while(iR = read(ret, fbuffer, sizeof(fbuffer)-1))
    {
        LOGE("###%s\n", fbuffer);
        break;
    }


    return env->NewStringUTF(hello.c_str());
}
