function main()
{
    var canvas = document.getElementById("gl-canvas");
    var gl = canvas.getContext("webgl");
    if(!gl)
    {
        alert("WebGL is not supported");
        return;
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

    const shaderProgram = initShaderProgram(gl, vsSource, fsSource);
    gl.useProgram(shaderProgram);

    var position = gl.getAttribLocation(shaderProgram, 'position');
    var color = gl.getUniformLocation(shaderProgram, 'color');
    
    //设置白色背景
    gl.clearColor(0.0, 0.0, 0.0, 1.0);
    gl.clear(gl.COLOR_BUFFER_BIT);
    
    //黑色的点
    gl.uniform3f(color, 0.0, 0.0, 0.0);
    const vertex = [
        1.0, 1.0,
        -1.0, 1.0,
        1.0, -1.0,
        -1.0, -1.0,
    ];

    drawBasic(gl, position);
}


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

    return shaderProgram;
}

function loadShader(gl, type, source)
{
    const shader = gl.createShader(type);

    gl.shaderSource(shader, source);
    gl.compileShader(shader);
    if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
    {
        alert("Error: Compile");
        gl.deleteShader(shader);
        return null;
    }
    return shader;
}

function drawBasic(gl, position)
{

    position = new Float32Array(position);
    //创建缓冲对象并存储在顶点缓冲器
    const positionBuffer = gl.createBuffer();
    //绑定上下文
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
    //建立对象的顶点
    gl.bufferData(gl.ARRAY_BUFFER, position, gl.STATIC_DRAW);

    gl.vertexAttribPointer(position, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttriArray(position);
    //利用TRIANGLE_STRIP参数三角拟合
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, position.length() / 2);
}