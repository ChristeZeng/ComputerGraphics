// //设置顶点着色器
// var vsSource = `
//     attribute vec4 Position;
//     void main()
//     {
//         gl_Position = Position;
//     }
// `;

// //设置片段着色器
// var fsSource = `
//     precision mediump float;
//     uniform vec4 u_FragColor;
//     void main()
//     {
//         gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
//     }
// `;
// 顶点着色器程序
var VSHADER_SOURCE =
  'attribute vec4 a_Position;\n' + // attribute variable
  'void main() {\n' +
  '  gl_Position = a_Position;\n' + // Set the vertex coordinates of the point
  '}\n';

// 片元着色器程序
var FSHADER_SOURCE =
  'precision mediump float;\n' +
  'uniform vec4 u_FragColor;\n' +  // uniform変数
  'void main() {\n' +
  '  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n' +
  '}\n';

function main()
{
    var canvas = document.getElementById('webgl');
    var gl = getWebGLContext(canvas);
    if(!gl)
    {
        alert("WebGL is not supported");
        return;
    }
    
    //初始化一个shader程序
    if(!initShaders(gl, vsSource, fsSource));
    {
        alert("Error: shader");
    }

    //Debug
    //alert('Yes');

    //建立顶点缓存
    initBuffers(gl);

    //清空为黑色
    gl.clearColor(0.0, 0.0, 0.0, 1.0); 
    //清空canvas
    gl.clear(gl.COLOR_BUFFER_BIT);

    //画出图形
    gl.drawArrays(gl.TRIANGLES, 0, 3);
    
}

function initBuffers(gl)
{

    //所画图形的坐标
    var vertices = [
        0, 0.5,   
        -0.5, -0.5,   
        0.5, -0.5
    ];

    //建立缓冲区对象
    var positionBuffer = gl.createBuffer();
    //将缓冲区对象绑定到目标
    gl.bindBuffer(gl.ARRAY_BUFFER, positionBuffer);
    //向缓冲区对象写入数据
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    
    var Position = gl.getAttribLocation(gl.program, 'Position');
    //将缓冲区对象分配给Position
    gl.vertexAttribPointer(Position, 2, gl.FLOAT, false, 0, 0);
    //连接Position与它分配到的缓冲区
    gl.enableVertexAttriArray(Position);
}