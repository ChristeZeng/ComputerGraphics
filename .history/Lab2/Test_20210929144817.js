function main()
{
    const canvas = document.querySelector("#glcanvas");
    const gl = canvas.getContext("webgl");
    if(!gl)
    {
        alert("No WebGL");
        return;
    }

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);
}