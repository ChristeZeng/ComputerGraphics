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
        precision mediump float;
        uniform vec4 u_FragColor;
        void main()
        {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    `;
    
    //初始化一个shader程序
    const shaderProgram = initShaders(gl, vsSource, fsSource);

    //Debug
    alert('Yes');

    //建立顶点缓存
    initBuffers(gl);

    gl.clearColor(0.0, 0.0, 0.0, 1.0);  // Clear to black, fully opaque
    gl.clear(gl.COLOR_BUFFER_BIT);

    //画出图形
    gl.drawArrays(gl.TRIANGLE, 0, 3);
    
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
    var position = gl.getAttribLocation(gl.program, 'Position');
    
    gl.vertexAttribPointer(position, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttriArray(position);
}

// function drawBasic(gl, buffers, Param)
// {
    
    
    
    
    
//     //gl.useProgram(Param.shaderProgram);
    
//     //利用TRIANGLE_STRIP参数三角拟合
    
// }

// //初始化着色器
// function initShaderProgram(gl, vsSource, fsSource)
// {
    
//     const vertexShader = loadShader(gl, gl.VERTEX_SHADER, vsSource);
//     const fragmentShader = loadShader(gl, gl.FRAGMENT_SHADER, fsSource);

//     //创建着色器程序
//     const shaderProgram = gl.createProgram();
//     gl.attachShader(shaderProgram, vertexShader);
//     gl.attachShader(shaderProgram, fragmentShader);
//     gl.linkProgram(shaderProgram);

//     if(!gl.getProgramParameter(shaderProgram, gl.LINK_STATUS))
//     {
//         alert("Error");
//         return null;
//     }

//     return shaderProgram;
// }

// function loadShader(gl, type, source)
// {
//     const shader = gl.createShader(type);

//     gl.shaderSource(shader, source);
//     gl.compileShader(shader);
//     if(!gl.getShaderParameter(shader, gl.COMPILE_STATUS))
//     {
//         alert("Error: Compile");
//         gl.deleteShader(shader);
//         return null;
//     }
//     return shader;
// }



