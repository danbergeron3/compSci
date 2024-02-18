"use strict";

var gl;
var points;

var NumPoints = 50000;

var pointFactor = 5000;
var randColor = [0.0, 0.0, 0.0, 1.0];

window.onload = function init()
{
    
    function gasket1() {
        //
        //  Initialize our data for the Sierpinski Gasket
        //
        // First, initialize the corners of our gasket with three points.

        var vertices = [
            vec2( -1, -1 ),
            vec2(  0,  1 ),
            vec2(  1, -1 )
        ];

        // Specify a starting point p for our iterations
        // p must lie inside any set of three vertices

        var u = add( vertices[0], vertices[1] );
        var v = add( vertices[0], vertices[2] );
        var p = scale( 0.25, add( u, v ) );
        

        // And, add our initial point into our array of points

        points = [ p ];

        // Compute new points
        // Each new point is located midway between
        // last point and a randomly chosen vertex
        
        for ( var i = 0; points.length < curPoints; ++i ) {
            var j = Math.floor(Math.random() * 3);
            p = add( points[i], vertices[j] );
            p = scale( 0.5, p );
            points.push( p );
        }

       // updateVeiwPort(canvas_width, canvas_height, origin_x, origin_y);
        gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

        //  Load shaders and initialize attribute buffers
        var program = initShaders( gl, "vertex-shader", "fragment-shader" );
        gl.useProgram( program );

        // Load the data into the GPU

        var bufferId = gl.createBuffer();
        gl.bindBuffer( gl.ARRAY_BUFFER, bufferId );
        gl.bufferData( gl.ARRAY_BUFFER, flatten(points), gl.STATIC_DRAW );

        // Associate out shader variables with our data buffer

        var vPosition = gl.getAttribLocation( program, "vPosition" );
        gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
        gl.enableVertexAttribArray( vPosition );
        
        // make random RGB values 
        for(let i = 0; i < 3; i++) {
            randColor[i] = rgb[i];
        }
        // Get the uniform location for the custom color in the shader program
        var randColorUniformLocation = gl.getUniformLocation(program, "randColor");

        // Set the custom color in JavaScript
        gl.uniform4fv(randColorUniformLocation, randColor);

        render();
        
    }

    function render() {
        gl.clear( gl.COLOR_BUFFER_BIT );
        gl.drawArrays( gl.POINTS, 0, points.length );
        
    } 

    // game loop
    function loop(timestamp) {
        
        gasket1();
        // window.requestAnimationFrame(loop)
        setTimeout(loop, time);
        str = "Status: Done";
        setTimeout(statChanger, 2000);
    }

    function statChanger() {
        status.textContent = str;
    }
    var canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
    var origin_x = 0;
    var origin_y = 0;
    var curPoints = NumPoints;

    let rgb = [0 , 0 , 0];
    let r = document.getElementById("rbutton");
    let g = document.getElementById("gbutton");
    let b = document.getElementById("bbutton");
    let picker = document.getElementById("rbutton2");

    let viewPortSlider = document.getElementById("vsize");
    let canvas_width = viewPortSlider.value;
    let canvas_height = viewPortSlider.value;
    gl.viewport( 0, 0, canvas_width, canvas_height);
    
    let timeSlider = document.getElementById("speed");
    let time = timeSlider.value;

    let pointSlider = document.getElementById("npoints");

    let status = document.getElementById("stat");
    let str = "Status";
    statChanger();
    pointSlider.addEventListener("input", () => {
        curPoints = pointSlider.value;
        str = "Status: Changing Points";
        statChanger();
        
    });

    timeSlider.addEventListener("input", () => {
        time = timeSlider.value;
        str = "Status: Changing Animation Speed";
        statChanger();
    });

    viewPortSlider.addEventListener("input", () => {
        console.log("x: " + origin_x);
        canvas_width = (viewPortSlider.value);
        canvas_height =(viewPortSlider.value);
        origin_y = 0;
        origin_x = 0; 
        gl.viewport(origin_x, origin_y, canvas_width, canvas_height);
        str = "Status: Changing Animation Size";
        statChanger();
    });

    picker.addEventListener("input", (event) => {
        var selectedColor = event.target.value;

        str = "Status: Applying Color to Shader";
        statChanger();
        // Parse the color value to extract individual RGB components
        var red = parseInt(selectedColor.substr(1, 2), 16);
        var green = parseInt(selectedColor.substr(3, 2), 16);
        var blue = parseInt(selectedColor.substr(5, 2), 16);

        rgb = [(parseFloat(red, 10)/255), (parseFloat(green, 10)/255), (parseFloat(blue, 10)/255)];
        
    });

    r.addEventListener("input", () => {
        str = "Status: Changing R Value in Shader";
        statChanger();
        setTimeout(1000);

        let g = document.getElementById("gbutton");
        let b = document.getElementById("bbutton");

        if (r.value > 255 || r.value < 0) {
            return;
        }

        if(r.value === "") {
            r.value = 0;
        }
        if(g.value === "") {
            g.value = 0;
        }
        if(b.value === "") {
            b.value = 0;
        }
        
        console.log(`Red: ${r.value} Green: ${g.value} Blue: ${b.value}`);
        rgb[0] = parseFloat(r.value, 10)/255;
        console.log(rgb[0]);
        console.log(rgb);
    });

    g.addEventListener("input", () => {
        str = "Status: Changing G Value in Shader";
        statChanger();
        setTimeout(1000);

        let r = document.getElementById("rbutton");
        let b = document.getElementById("bbutton");

        if (g.value > 255 || g.value < 0) {
            return;
        }

        if(r.value === "") {
            r.value = 0;
        }
        if(g.value === "") {
            g.value = 0;
        }
        if(b.value === "") {
            b.value = 0;
        }
        console.log(`Red: ${r.value} Green: ${g.value} Blue: ${b.value}`);
        rgb[1] = parseFloat(g.value, 10)/255;
        console.log(rgb);
    });

    b.addEventListener("input", () => {
        
        str = "Status: Changing B Value in Shader";
        statChanger();
        setTimeout(1000);

        let r = document.getElementById("rbutton");
        let g = document.getElementById("gbutton");
        if ( b.value > 255  || b.value < 0) {
            return;
        }

        if(r.value === "") {
            r.value = 0;
        }
        if(g.value === "") {
            g.value = 0;
        }
        if(b.value === "") {
            b.value = 0;
        }
        
        console.log(`Red: ${r.value} Green: ${g.value} Blue: ${b.value}`);
        rgb[2] = parseFloat(b.value, 10)/255;
        console.log(rgb);
    });

    window.requestAnimationFrame(loop)
};




