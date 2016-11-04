package org.dmlc.mxnet;

import android.util.Log;

public class Predictor {
    static {
      System.loadLibrary("predict");
    }

    public boolean FaceInit(String modelpath) { return nativeFaceInit(modelpath); }
    public boolean FaceState() { return nativeFaceState(); }
    public float[] FaceLandmark(byte[] facedata,int width,int height,int angle) { return nativeFaceLandmark(facedata,width,height,angle); }
    public String FaceFeatureLast()
    {
      return nativeFaceFeatureLast();
    }
    public float  FaceDistance(String f1, String f2){ return nativeFaceDistance(f1,f2); }

    private native static boolean nativeFaceInit(String modelpath);
    private native static boolean nativeFaceState();
    private native static float[] nativeFaceLandmark(byte[] facedata,int width,int height,int angle);
    private native static String nativeFaceFeatureLast();
    private native static float nativeFaceDistance(String f1, String f2);
}
