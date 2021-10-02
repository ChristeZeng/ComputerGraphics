function main()
{
    /** @type {HTMLCanvasElement} */
    var canvas = document.getElementById('gl-canvas');
    var gl = canvas.getContext('webgl');
    if(!gl)
    {
        alert("WebGL is not supported");
        return;
    }
    
    //设置顶点着色器
    const vsSource = `
        attribute vec4 Position;
        void main()
        {
            gl_Position = Position;
        }
    `;

    //设置片段着色器
    const fsSource = `
        void main()
        {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    `;
    
    //初始化一个shader程序
    const shaderProgram = initShaderProgram(gl, vsSource, fsSource);
    
    const Param = 
    {
        program: shaderProgram,
        attribLocations: 
        {
            vertexPosition: gl.getAttribLocation(shaderProgram, 'Position'),
        },

    };

    //Debug
    alert('Yes');

    //建立顶点缓存
    const buffers = initBuffers(gl);
    //画出图形
    drawBasic(gl, buffers, Param);
    
}

function initBuffers(gl)
{
    //建立顶点缓存
    const positionBuffer = gl.createBuffer();
    //绑定缓存
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);

    //所画图形的坐标
    const vertices = [
        0, 0.5,   
        -0.5, -0.5,   
        0.5, -0.5
    ];

    //将数据填充到缓冲区
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    //返回一个缓存区的对象
    return {position: positionBuffer};
}

function drawBasic(gl, buffers, Param)
{
    gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
    gl.clear(gl.COLOR_BUFFER_BIT);
    
    
    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
    
    gl.vertexAttribPointer(Param.attribLocations.vertexPosition, 2, gl.FLOAT, false, 0, 0);
    alert("ShaderProgram2");
    gl.enableVertexAttriArray(Param.attribLocations.vertexPosition);
    alert("ShaderProgram2");
    //gl.useProgram(Param.shaderProgram);
    
    //利用TRIANGLE_STRIP参数三角拟合
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, 4);
}

//初始化着色器
function initShaderProgram(gl, vsSource, fsSource)
{
    
    const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
    const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

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



