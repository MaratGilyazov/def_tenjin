#if defined(DM_PLATFORM_ANDROID)
#include <dmsdk/sdk.h>
#include "tenjin.h"

static JNIEnv* Attach()
{
    JNIEnv* env;
    JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
    vm->AttachCurrentThread(&env, NULL);
    return env;
}

static bool Detach(JNIEnv* env)
{
    bool exception = (bool) env->ExceptionCheck();
    env->ExceptionClear();
    JavaVM* vm = dmGraphics::GetNativeAndroidJavaVM();
    vm->DetachCurrentThread();
    return !exception;
}

namespace {
    struct AttachScope
    {
        JNIEnv* m_Env;
        AttachScope() : m_Env(Attach())
        {
        }
        ~AttachScope()
        {
            Detach(m_Env);
        }
    };
}

static jclass GetClass(JNIEnv* env, const char* classname)
{
    jclass activity_class = env->FindClass("android/app/NativeActivity");
    jmethodID get_class_loader = env->GetMethodID(activity_class,"getClassLoader", "()Ljava/lang/ClassLoader;");
    jobject cls = env->CallObjectMethod(dmGraphics::GetNativeAndroidActivity(), get_class_loader);
    jclass class_loader = env->FindClass("java/lang/ClassLoader");
    jmethodID find_class = env->GetMethodID(class_loader, "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;");

    jstring str_class_name = env->NewStringUTF(classname);
    jclass outcls = (jclass)env->CallObjectMethod(cls, find_class, str_class_name);
    env->DeleteLocalRef(str_class_name);
    return outcls;
}

void Tenjin_Init(const char*api_key, bool gdpr_consent)
{
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    jclass cls = GetClass(env, "com.anvil.tenjin.Tenjin");
    jmethodID method = env->GetStaticMethodID(cls, "Init", "(Landroid/app/Activity;Ljava/lang/String;Z)V");

    jstring key = env->NewStringUTF(api_key);
    
    env->CallStaticObjectMethod(cls, method, dmGraphics::GetNativeAndroidActivity(), key, gdpr_consent ? JNI_TRUE : JNI_FALSE);

    env->DeleteLocalRef(key);
}

void Tenjin_CustomEvent(const char*event_name)
{
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    jclass cls = GetClass(env, "com.anvil.tenjin.Tenjin");
    jmethodID method = env->GetStaticMethodID(cls, "CustomEvent", "(Ljava/lang/String;)V");
    
    jstring eventName = env->NewStringUTF(event_name);

    env->CallStaticObjectMethod(cls, method, eventName);

    env->DeleteLocalRef(eventName);
}

void Tenjin_CustomEventWithValue(const char*event_name, const char*event_value)
{
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    jclass cls = GetClass(env, "com.anvil.tenjin.Tenjin");
    jmethodID method = env->GetStaticMethodID(cls, "CustomEventWithValue", "(Ljava/lang/String;Ljava/lang/String;)V");

    jstring eventName = env->NewStringUTF(event_name);
    jstring eventValue = env->NewStringUTF(event_value);

    env->CallStaticObjectMethod(cls, method, eventName, eventValue);

    env->DeleteLocalRef(eventName);
    env->DeleteLocalRef(eventValue);
}

void Tenjin_PurchaseEvent(const char* product_id, const char* currency_code, const int quantity, const double price)
{
    AttachScope attachscope;
    JNIEnv* env = attachscope.m_Env;

    jclass cls = GetClass(env, "com.anvil.tenjin.Tenjin");
    jmethodID method = env->GetStaticMethodID(cls, "PurchaseEvent", "(Ljava/lang/String;Ljava/lang/String;ID)V");

    jstring productId = env->NewStringUTF(product_id);
    jstring currencyCode = env->NewStringUTF(currency_code);

    env->CallStaticObjectMethod(cls, method, productId, currencyCode, quantity, price);

    env->DeleteLocalRef(productId);
    env->DeleteLocalRef(currencyCode);
}

#endif