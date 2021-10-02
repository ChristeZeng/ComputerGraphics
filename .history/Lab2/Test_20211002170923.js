function main()
{
    //获取canvas元素
    var canvas = document.getElementById('gl-canvas');
    //获取webgl上下文
    var gl = canvas.getContext("webgl");
    if(!gl)
    {
        alert("WebGL is not supported");
        return;
    }

    const vsSource = `
        attribute vec4 position;
        void main()
        {
            gl_Position = position;
        }
    `;

    const fsSource = `
        void main()
        {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
    `;
    
    //初始化着色器
    const shaderProgram = initShaderProgram(gl, vsSource, fsSource);
    
    var position = gl.getAttribLocation(shaderProgram, 'position');
    //设置顶点缓冲区
    const buffers = initBuffers(gl);
    //绘制图像
    drawBasic(gl, buffers, position, shaderProgram);
    
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

function initBuffers(gl)
{
    // var N = 100;
    // var vertices = [0.0, 0.0];
    // var r = 0.5;

    // for (var i = 0; i <= N; i++) 
    // {
    //     var theta = i * 2 * Math.PI / N;
    //     var x = r * Math.sin(theta);
    //     var y = r * Math.cos(theta);
    //     vertices.push(x, y);
    // }
    var vertices = [
        1.0, 1.0,
        1.0, -1.0,
        -1.0, 1.0,
        -1.0, -1.0,
    ];
    //创建缓冲区对象
    const positionBuffer = gl.createBuffer();
    //将缓冲区对象绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
    // 向缓冲区对象写入数据
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    return {
            position: positionBuffer,
            vertex: vertices
        };
}

function drawBasic(gl, buffers, position, shaderProgram)
{
    //将背景重置为黑色
    gl.clearColor(1.0, 1.0, 1.0, 1.0);  
    //清除canvas
    gl.clear(gl.COLOR_BUFFER_BIT);
    
    
    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
    gl.vertexAttribPointer(position, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(position);
    gl.useProgram(shaderProgram);
    
    //利用TRIANGLE_STRIP参数三角拟合
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, buffers.vertex.length / 2);
}