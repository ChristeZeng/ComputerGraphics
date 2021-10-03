const red    = [220.0/255.0, 47.0/225.0, 31.0/225.0];
const blue   = [0, 107.0/225.0, 176.0/225.0];
const yellow = [239.0/255.0, 169.0/225.0, 13.0/225.0];
const black  = [29.0/255.0, 24.0/225.0, 21.0/225.0];
const green  = [5.0/255.0, 147.0/225.0, 65.0/225.0];

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

    var vsSource = `
        attribute vec4 position;
        void main()
        {
            gl_Position = position;
        }
    `;

    var fsSource = `
        precision mediump float;
        uniform vec3 color;
        void main()
        {
            gl_FragColor = vec4(color, 1.0);
        }
    `;
    
    //初始化着色器
    var shaderProgram = initShaderProgram(gl, vsSource, fsSource);
    if(!shaderProgram)
    {
        alert("Error: initshader");
        return;
    }
    //获取变量
    gl.useProgram(shaderProgram);
    var position = gl.getAttribLocation(shaderProgram, 'position');
    var color = gl.getUniformLocation(shaderProgram, 'color');
    
    draw();

    function draw()
    {
        //将背景重置为白色
        gl.clearColor(1.0, 1.0, 1.0, 1.0);  
        //清除canvas
        gl.clear(gl.COLOR_BUFFER_BIT);
        
        //计算顶点坐标位置
        var N = 100;
        var vertices = [];
        var r_inner = 0.1;
        var r_outter = 0.12;
        
        for (var i = 0; i <= N; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = -0.26 + r_inner * Math.sin(theta);
            var y_inner = r_inner * Math.cos(theta);
            var x_outter = -0.26 + r_outter * Math.sin(theta);
            var y_outter = r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, blue);
        
        vertices = [];
        for (var i = 0; i <= N; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = r_inner * Math.sin(theta);
            var y_inner = r_inner * Math.cos(theta);
            var x_outter = r_outter * Math.sin(theta);
            var y_outter = r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, black);
        
        vertices = [];
        for (var i = 0; i <= N; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = 0.26 + r_inner * Math.sin(theta);
            var y_inner = r_inner * Math.cos(theta);
            var x_outter = 0.26 + r_outter * Math.sin(theta);
            var y_outter = r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, red);

        vertices = [];
        for (var i = 0; i <= N; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = -0.13 + r_inner * Math.sin(theta);
            var y_inner = -0.11 + r_inner * Math.cos(theta);
            var x_outter = -0.13 + r_outter * Math.sin(theta);
            var y_outter = -0.11 + r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, yellow);

        vertices = [];
        for (var i = 0; i <= 100; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = 0.13 + r_inner * Math.sin(theta);
            var y_inner = -0.11 + r_inner * Math.cos(theta);
            var x_outter = 0.13 + r_outter * Math.sin(theta);
            var y_outter = -0.11 + r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, green);
        
        vertices = [];
        for (var i = 20; i <= 30; i++) 
        {
            var theta = i * 2 * Math.PI / N;
            var x_inner = -0.26 + r_inner * Math.sin(theta);
            var y_inner = r_inner * Math.cos(theta);
            var x_outter = -0.26 + r_outter * Math.sin(theta);
            var y_outter = r_outter * Math.cos(theta);
            vertices.push(x_inner, y_inner);
            vertices.push(x_outter, y_outter);
        }

        drawRing(vertices, blue);
           
    }

    function drawRing(vertices, colors)
    {
        //设置画笔为黑色
        gl.uniform3f(color, colors[0], colors[1], colors[2]);

        //创建缓冲区对象
        var positionBuffer = gl.createBuffer();
        //将缓冲区对象绑定到目标
        gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
        // 向缓冲区对象写入数据
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        
        gl.vertexAttribPointer(position, 2, gl.FLOAT, false, 0, 0);
        gl.enableVertexAttribArray(position);
        //利用TRIANGLE_STRIP参数三角拟合
        gl.drawArrays(gl.TRIANGLE_STRIP, 0, vertices.length / 2);
    }
    //gl.uniform3f(color, 1.0, 0.0, 0.0);
    //设置顶点缓冲区
    //const buffers = initBuffers(gl, vertices);
    //绘制图像
    //drawBasic(gl, buffers, position, shaderProgram);
    
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

function initBuffers(gl, vertices)
{
    // for (var i = 0; i <= N; i++) 
    // {
    //     var theta = i * 2 * Math.PI / N;
    //     var x_inner = 0.8 + r_inner * Math.sin(theta);
    //     var y_inner = r_inner * Math.cos(theta);
    //     var x_outter = 0.8 + r_outter * Math.sin(theta);
    //     var y_outter = r_outter * Math.cos(theta);
    //     vertices.push(x_inner, y_inner);
    //     vertices.push(x_outter, y_outter);
    // }
    
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
    gl.clearColor(0.0, 0.0, 0.0, 1.0);  
    //清除canvas
    gl.clear(gl.COLOR_BUFFER_BIT);
    
    
    gl.uniform3f(color, 1.0, 0.0, 0.0);

    gl.bindBuffer(gl.ARRAY_BUFFER, buffers.position);
    gl.vertexAttribPointer(position, 2, gl.FLOAT, false, 0, 0);
    gl.enableVertexAttribArray(position);
    gl.useProgram(shaderProgram);
    
    //利用TRIANGLE_STRIP参数三角拟合
    gl.drawArrays(gl.TRIANGLE_STRIP, 0, buffers.vertex.length / 2);
}