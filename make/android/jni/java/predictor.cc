#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <jni.h>


////////////////////////////////////////////////.h//////////////////////////////////////
#ifndef _Included_org_dmlc_mxnet_Predictor
#define _Included_org_dmlc_mxnet_Predictor
#ifdef __cplusplus
extern "C" {
#endif


JNIEXPORT jboolean JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceInit
  (JNIEnv *env, jclass, jstring jmodelpath);

JNIEXPORT jboolean JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceState
  (JNIEnv *env, jclass);

JNIEXPORT jfloatArray JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceLandmark
  (JNIEnv *env, jclass, jbyteArray jfacedata, jint jwidth, jint jheight, jint angle);

JNIEXPORT jstring JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceFeatureLast
  (JNIEnv *env, jclass);

JNIEXPORT jfloat JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceDistance
  (JNIEnv *env, jclass, jstring jf1, jstring jf2);


#ifdef __cplusplus
}
#endif
#endif
////////////////////////////////////////////////.h//////////////////////////////////////

using namespace std;
bool faceinit(const char * modelpath);
bool faceinitstate();
std::vector<float> facelandmark(uint8_t * facedata,int width,int height,int angle);
string facefeaturelast();
float facedistance(string & s1, string & s2);



JNIEXPORT jboolean JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceInit
  (JNIEnv *env, jclass, jstring jmodelpath)
{
	const char *modelpath = env->GetStringUTFChars(jmodelpath, JNI_FALSE);
	bool ret /*= faceinit(modelpath)*/;
	env->ReleaseStringUTFChars(jmodelpath, modelpath);
	return (jboolean)ret;
}

JNIEXPORT jboolean JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceState
  (JNIEnv *env, jclass)
{
	return true/*(jboolean)faceinitstate()*/;
}

JNIEXPORT jfloatArray JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceLandmark
  (JNIEnv *env, jclass, jbyteArray jfacedata, jint jwidth, jint jheight, jint angle)
{
	jbyte* facedata = env->GetByteArrayElements(jfacedata, 0);
	std::vector<float> data /*= facelandmark((unsigned char *)facedata,(int)jwidth,(int)jheight,(int)angle)*/;
	env->ReleaseByteArrayElements(jfacedata, facedata, 0);

	int size = data.size();
	jfloatArray joutput = env->NewFloatArray(size);
    jfloat *out = env->GetFloatArrayElements(joutput, NULL);

    for (int i=0; i<size; i++) out[i] = data[i];
    env->ReleaseFloatArrayElements(joutput, out, 0);
	return joutput;
}

JNIEXPORT jstring JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceFeatureLast
  (JNIEnv *env, jclass)
{
	string feature /*= facefeaturelast()*/;
	jstring jfeature;
	jfeature = env->NewStringUTF(feature.c_str());
	return jfeature;
}


JNIEXPORT jfloat JNICALL Java_org_dmlc_mxnet_Predictor_nativeFaceDistance
  (JNIEnv *env, jclass, jstring jf1, jstring jf2)
{
	const char *pf1 = env->GetStringUTFChars(jf1, JNI_FALSE);
	const char *pf2 = env->GetStringUTFChars(jf2, JNI_FALSE);
	string f1(pf1);
	string f2(pf2);
	env->ReleaseStringUTFChars(jf1, pf1);
	env->ReleaseStringUTFChars(jf2, pf2);

	return 0.0/*(jfloat)facedistance(f1,f2)*/;
}



















