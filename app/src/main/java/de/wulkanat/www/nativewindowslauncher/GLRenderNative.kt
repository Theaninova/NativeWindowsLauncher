package de.wulkanat.www.nativewindowslauncher

class GLRenderNative {
    init {
        System.loadLibrary("GLRender")
    }

    external fun on_surface_created()

    external fun on_surface_changed(width: Int, height: Int)

    external fun on_draw_frame()
}