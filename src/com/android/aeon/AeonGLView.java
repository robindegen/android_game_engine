package com.android.aeon;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;

class AeonGLView extends GLSurfaceView
{
    public AeonGLView(Context context)
    {
        super(context);
        
        m_context = context;
        
        init(false, 0, 0);
    }

    public AeonGLView(Context context, boolean translucent, int depth, int stencil)
    {
        super(context);
        
        m_context = context;
        
        init(translucent, depth, stencil);
    }

    private void init(boolean translucent, int depth, int stencil)
    {
        if (translucent)
        {
            this.getHolder().setFormat(PixelFormat.TRANSLUCENT);
        }
        
        setEGLContextFactory(new AeonContextFactory());
        
        setEGLConfigChooser( translucent ?
                             new AeonConfigChooser(8, 8, 8, 8, depth, stencil) :
                             new AeonConfigChooser(5, 6, 5, 0, depth, stencil) );
        
        setRenderer(new AeonRenderer(m_context));
    }
    
    Context m_context;
}
