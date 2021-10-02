function main()
{
    var canvas = document.getElementById("gl-canvas");
    var gl = canvas.getContext("webgl");
    if(!gl)
    {
        alert("WebGL is not supported");
        return;
    }

    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);
}

const vsSource = `
    attribute vec2 position;
    void main()
    {
    gl_Position = vec4(position, 0.0, 1.0);
    }
`;

const fsSource = `
    precision mediump float;
    uniform vec3 color;
    void main()
    {
        gl_FragColor = vec4(color, 1.0);
    }
`;

//初始化着色器
function initShaderProgram(gl, vsSource, fsSource)
{
    const vertexShader = loadShader(gl, gl.vertexShader, vsSource);
    const fragmentShader = loadShader(gl. gl.fragmentShader, fsSource);

    //创建着色器程序
    const shaderProgram = gl.createProgram();
    gl.attachShader(shaderProgram, vertexShader);
    gl.attachShader(shaderProgram, fragmentShader);
    gl.linkProgram(shaderProgram);

    if(!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS))
    {
        alert("Error");
        return null;
    }
    
}