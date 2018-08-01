package de.wulkanat.www.nativewindowslauncher

class GLRenderNative(statusBarHeight: Int, navBarHeight: Int) {
    init {
        System.loadLibrary("GLRender")

        init(statusBarHeight, navBarHeight)
    }

    external fun on_surface_created()

    external fun on_surface_changed(width: Int, height: Int)

    external fun on_draw_frame()

    external fun init(mStatusBarHeightPixels: Int, mNavBarHeightPixels: Int)

    external fun onPause()

    external fun onResume()
}