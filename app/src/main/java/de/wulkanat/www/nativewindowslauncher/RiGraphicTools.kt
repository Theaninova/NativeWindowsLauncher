package de.wulkanat.www.nativewindowslauncher

import android.opengl.GLES20

class RiGraphicTools {
    companion object {
        var sp_SolidColor: Int = 0

        val vs_SolidColor =
                "uniform    mat4        uMVPMatrix;" +
                        "attribute  vec4        vPosition;" +
                        "void main() {" +
                        "  gl_Position = uMVPMatrix * vPosition;" +
                        "}"

        val fs_SolidColor =
                "precision mediump float;" +
                        "void main() {" +
                        "  gl_FragColor = vec4(1,0,0,1);" +
                        "}"

        fun loadShader(type: Int, shaderCode: String): Int {

            // create a vertex shader type (GLES20.GL_VERTEX_SHADER)
            // or a fragment shader type (GLES20.GL_FRAGMENT_SHADER)
            val shader = GLES20.glCreateShader(type)

            // add the source code to the shader and compile it
            GLES20.glShaderSource(shader, shaderCode)
            GLES20.glCompileShader(shader)

            // return the shader
            return shader
        }
    }
}