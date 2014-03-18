package com.android.aeon;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.content.Context;
import android.content.res.AssetManager;
import android.opengl.GLSurfaceView;

public class AeonRenderer implements GLSurfaceView.Renderer
{
	public AeonRenderer(Context context)
	{
		m_context = context;
		m_assetmanager = m_context.getAssets();
	}
	
    public void onDrawFrame(GL10 gl)
    {
    	AeonLib.step();
    }

    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
    	AeonLib.init(m_assetmanager, width, height);
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        // Do nothing.
    }
    
    Context m_context;
    AssetManager m_assetmanager;
}