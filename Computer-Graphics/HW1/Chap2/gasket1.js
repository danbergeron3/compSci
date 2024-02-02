"use strict";

var gl;
var points;

var NumPoints = 50000;
var windowOffset = 40;
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
        if (shrink === true) {
            curPoints -= pointFactor;
            if (curPoints <= 0) {
                shrink = false;
            }
        } else {
            curPoints += pointFactor;
            if (curPoints >= NumPoints) {
                shrink = true;
            }
        }
        for ( var i = 0; points.length < curPoints; ++i ) {
            var j = Math.floor(Math.random() * 3);
            p = add( points[i], vertices[j] );
            p = scale( 0.5, p );
            points.push( p );
        }

        //
        //  Configure WebGL
        //
        if(shrink === true) {
            canvas_width = canvas_width - windowOffset;
            canvas_height = canvas_height - windowOffset;
            origin_x += windowOffset/2;   
            console.log("shrink x: " + origin_x);
        } else {
            if(canvas_width < canvas.width && canvas_height < canvas.height) {
                canvas_width = canvas_width + windowOffset;
                canvas_height = canvas_height + windowOffset;
                origin_x -= windowOffset/2;
                console.log("grow x: " + origin_x);   
                
            }
        }
        origin_y = 0;

        updateVeiwPort(canvas_width, canvas_height, origin_x, origin_y);
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
            var color = Math.random();
            randColor[i] = color;
        }
        // Get the uniform location for the custom color in the shader program
        var randColorUniformLocation = gl.getUniformLocation(program, "randColor");

        // Set the custom color in JavaScript
        gl.uniform4fv(randColorUniformLocation, randColor);
        console.log("Custom Color Location:", randColorUniformLocation);
        console.log("Custom Color Value:", randColor);
        render();
        
        console.log("render done");
    }

    function render() {
        gl.clear( gl.COLOR_BUFFER_BIT );
        gl.drawArrays( gl.POINTS, 0, points.length );
        
    } 

    function updateVeiwPort(w, h, x, y) {
        if (w <= 0 || h <= 0) {
            canvas_width = canvas.width;
            canvas_height = canvas.height;
            origin_x = 0;
            origin_y = 0;
            gl.viewport( origin_x, origin_y, canvas_width, canvas_height);
            return;
        }

        gl.viewport( x, y, w, h);

    }

    function loop(timestamp) {
        
        gasket1();
        // window.requestAnimationFrame(loop)
        setTimeout(loop, 78);
    }

    var canvas = document.getElementById( "gl-canvas" );
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }
    var canvas_width = canvas.width;
    var canvas_height = canvas.height;
    var origin_x = 0;
    var origin_y = 0;
    var lastRender = 0;
    var curPoints = NumPoints;
    let shrink = true;
    window.requestAnimationFrame(loop)
};




