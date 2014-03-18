package com.android.aeon;

public class AeonLib
{

     static
     {
         System.loadLibrary("aeonjni");
     }
     
     public static native void init(Object assetmanager, int width, int height);
     public static native void step();
}
