package com.android.aeon;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;
import android.util.Log;

public class AeonContextFactory implements GLSurfaceView.EGLContextFactory
{
    private static int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
    public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig)
    {
        Log.w("aeon", "creating OpenGL ES 2.0 context");
        
        checkEglError("Before eglCreateContext", egl);
        
        int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE };
        EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);
        
        checkEglError("After eglCreateContext", egl);
        
        return context;
    }

    public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context)
    {
        egl.eglDestroyContext(display, context);
    }
    
    public static void checkEglError(String prompt, EGL10 egl)
    {
        int error;
        while ((error = egl.eglGetError()) != EGL10.EGL_SUCCESS)
        {
            Log.e("aeon", String.format("%s: EGL error: 0x%x", prompt, error));
        }
    }
}