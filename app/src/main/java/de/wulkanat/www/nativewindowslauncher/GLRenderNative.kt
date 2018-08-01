package de.wulkanat.www.nativewindowslauncher

class GLRenderNative {
    init {
        System.loadLibrary("GLRender")

        init()
    }

    external fun on_surface_created()

    external fun on_surface_changed(width: Int, height: Int)

    external fun on_draw_frame()

    external fun init()

    external fun onPause()

    external fun onResume()
}