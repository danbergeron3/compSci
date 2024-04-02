"use strict";

var canvas;
var gl;

var numVertices  = 54;

var pointsArray = [];
var colorsArray = [];        

var vertexColors = [
        vec4( 0.0, 0.0, 0.0, 1.0 ),  // black
        vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
        vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
        vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
        vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
        vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
        vec4( 0.0, 1.0, 1.0, 1.0 ),   // cyan
        vec4( 1.0, 1.0, 1.0, 1.0 ),  // white
    ];

// var near = -1;
// var far = 1;
var radius = 1;
var theta  = 0.0;
var phi    = 0.0;
var dr = 5.0 * Math.PI/180.0;

var left = -2.0;
var right = 2.0;
var bottom = -2.0;
var ytop = 2.0;
var near = -2.0;
var far = 2.0;

var modelViewMatrix, projectionMatrix;
var modelViewMatrixLoc, projectionMatrixLoc;
var eye;
const at = vec3(0.0, 0.0, 0.0);
const up = vec3(0.0, 1.0, 0.0);

function quad(a, b, c, d) {
    var vertices = [
        vec4( -0.25, -0.25,  0.25, 1.0 ), 
        vec4( -0.25,  0.25,  0.25, 1.0 ), 
        vec4(  0.25,  0.25,  0.25, 1.0 ), 
        vec4(  0.25, -0.25,  0.25, 1.0 ), 
        vec4( -0.25, -0.25, -0.25, 1.0 ),
        vec4( -0.25,  0.25, -0.25, 1.0 ),
        vec4(  0.25,  0.25, -0.25, 1.0 ),
        vec4(  0.25, -0.25, -0.25, 1.0 )
    ];


    var vertexColors = [
        [ 0.0, 0.0, 0.0, 1.0 ],  // black
        [ 1.0, 0.0, 0.0, 1.0 ],  // red
        [ 1.0, 1.0, 0.0, 1.0 ],  // yellow
        [ 0.0, 1.0, 0.0, 1.0 ],  // green
        [ 0.0, 0.0, 1.0, 1.0 ],  // blue
        [ 1.0, 0.0, 1.0, 1.0 ],  // magenta
        [ 0.0, 1.0, 1.0, 1.0 ],  // cyan
        [ 1.0, 1.0, 1.0, 1.0 ]   // white
    ];
    var indices = [ a, b, c, a, c, d ];

    for ( var i = 0; i < indices.length; ++i ) {
        pointsArray.push( vertices[indices[i]] );
        //colors.push( vertexColors[indices[i]] );
    
        // for solid colored faces use 
        colorsArray.push(vertexColors[a]);
        
    }
}
function colorTriangle()
{
    triangle( 0, 1, 2, 0 ); // black
    triangle( 3, 4, 5, 1 ); // green
    triangle( 0, 3, 2, 2 ); // quad
    triangle( 2, 3, 5, 2 ); // quad - red
    triangle( 1, 0, 3, 3 ); // quad
    triangle( 1, 4, 3, 3 ); // quad - blue
    
}

function triangle(a, b, c, surface_number) 
{
	// x y z 
    var vertices = [
        vec4(  0.0,  1.0/2,  0.25, 1.0 ),
        vec4( -0.25,  0.25,  0.25, 1.0 ),
        vec4(  0.25,  0.25,  0.25, 1.0 ),
        vec4(  0.0,  1.0/2, -0.25, 1.0 ), 
        vec4( -0.25,  0.25, -0.25, 1.0 ), 
        vec4(  0.25,  0.25, -0.25, 1.0 )
    ];

	var vertexColors = [
        [ 0.0, 0.4, 0.8, 1.0 ],  // black
        [ 0.0, 0.8, 0.4, 1.0 ],  // green
        [ 0.8, 0.0, 0.0, 1.0 ],  // red
        [ 0.0, 0.0, 0.8, 1.0 ]   // blue
    ];

    
    
    var indices = [ a, b, c ];

    for ( var i = 0; i < indices.length; ++i ) {
        pointsArray.push( vertices[indices[i]] );
//         colors.push( vertexColors[indices[i]] );
    
        // for solid colored faces use 
        colorsArray.push(vertexColors[surface_number]);
        
    }
}


function colorCube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}


window.onload = function init() {
    canvas = document.getElementById( "gl-canvas" );

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    colorCube();
	colorTriangle();


    gl.viewport( 0, 0, canvas.width, canvas.height );

    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    gl.enable(gl.DEPTH_TEST);


    //
    //  Load shaders and initialize attribute buffers
    //
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    var cBufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBufferId );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colorsArray), gl.STATIC_DRAW );
    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor);

    var vBufferId = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBufferId );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW );

    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );

    modelViewMatrixLoc = gl.getUniformLocation( program, "modelViewMatrix" );
    projectionMatrixLoc = gl.getUniformLocation( program, "projectionMatrix" );

// sliders for viewing parameters

    document.getElementById("depthSlider").onchange = function(event) {
        far = event.target.value/2;
        near = -event.target.value/2;
    };

    document.getElementById("radiusSlider").onchange = function(event) {
       radius = event.target.value;
    };
    document.getElementById("thetaSlider").onchange = function(event) {
        theta = event.target.value* Math.PI/180.0;
    };
    document.getElementById("phiSlider").onchange = function(event) {
        phi = event.target.value* Math.PI/180.0;
    };
    document.getElementById("heightSlider").onchange = function(event) {
        ytop = event.target.value/2;
        bottom = -event.target.value/2;
    };
    document.getElementById("widthSlider").onchange = function(event) {
        right = event.target.value/2;
        left = -event.target.value/2;
    };
    document.getElementById("animateButton").onclick = function() {
        var lineP1 = [parseFloat(document.getElementById("lineX1").value), 
                        parseFloat(document.getElementById("lineY1").value), 
                        parseFloat(document.getElementById("lineZ1").value)];
        var lineP2 = [parseFloat(document.getElementById("lineX2").value), 
                        parseFloat(document.getElementById("lineY2").value), 
                        parseFloat(document.getElementById("lineZ2").value)];
        var circleCenter = [parseFloat(document.getElementById("circleX").value), 
                            parseFloat(document.getElementById("circleY").value), 
                            parseFloat(document.getElementById("circleZ").value)];
        var circleRadius = parseFloat(document.getElementById("circleRadius").value);
    
        var linePoints = getLinePoints(lineP1, lineP2, 100);
        var circlePoints = getCirclePoints(circleCenter, circleRadius, 100);
    
        // Combine line and circle points for full path
        var pathPoints = linePoints.concat(circlePoints);
        
        animateCamera(pathPoints);
    };

    //render();
}


var render = function() {
        gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);
        eye = vec3(radius*Math.sin(phi), radius*Math.sin(theta),
             radius*Math.cos(phi));

        modelViewMatrix = lookAt(eye, at , up);
        projectionMatrix = ortho(left, right, bottom, ytop, near, far);

        gl.uniformMatrix4fv( modelViewMatrixLoc, false, flatten(modelViewMatrix) );
        gl.uniformMatrix4fv( projectionMatrixLoc, false, flatten(projectionMatrix) );

        gl.drawArrays( gl.TRIANGLES, 0, numVertices );
        requestAnimFrame(render);
}

var render2 = function(eye) {
    gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // Use the eye parameter for the camera position
    modelViewMatrix = lookAt(eye, at, up);
    projectionMatrix = ortho(left, right, bottom, ytop, near, far);

    gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(modelViewMatrix));
    gl.uniformMatrix4fv(projectionMatrixLoc, false, flatten(projectionMatrix));

    gl.drawArrays(gl.TRIANGLES, 0, numVertices);
}

function getLinePoints(p1, p2, numPoints) {
    var linePoints = [];
    for (let i = 0; i <= numPoints; i++) {
        var t = i / numPoints;
        var x = p1[0] + t * (p2[0] - p1[0]);
        var y = p1[1] + t * (p2[1] - p1[1]);
        var z = p1[2] + t * (p2[2] - p1[2]);
        linePoints.push([x, y, z]);
    }
    return linePoints;
}

function getCirclePoints(center, radius, numPoints) {
    var circlePoints = [];
    for (let i = 0; i <= numPoints; i++) {
        var angle = 2 * Math.PI * i / numPoints;
        var x = center[0] + radius * Math.cos(angle);
        var y = center[1] + radius * Math.sin(angle);
        var z = center[2];
        circlePoints.push([x, y, z]);
    }
    return circlePoints;
}

function animateCamera(pathPoints) {
    var index = 0;
    var animate = function() {
        if (index < pathPoints.length) {
            eye = vec3(pathPoints[index][0], pathPoints[index][1], pathPoints[index][2]);
            console.log("Eye value:", eye);
            index++;

            // Update the model view matrix with the new eye position
            modelViewMatrix = lookAt(eye, at, up);
            gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(modelViewMatrix));

            // Render the scene with the new camera position
            render2(eye);

            // Wait for a second, then request the next frame of the animation
            if (index < pathPoints.length) {
                setTimeout(function() {
                    requestAnimationFrame(animate);
                }, 100);
            }
        }
    };
    animate();
}

document.getElementById("animateButton").onclick = function() {
    var lineP1 = [parseFloat(document.getElementById("lineX1").value), 
                    parseFloat(document.getElementById("lineY1").value), 
                    parseFloat(document.getElementById("lineZ1").value)];
    var lineP2 = [parseFloat(document.getElementById("lineX2").value), 
                    parseFloat(document.getElementById("lineY2").value), 
                    parseFloat(document.getElementById("lineZ2").value)];
    var circleCenter = [parseFloat(document.getElementById("circleX").value), 
                        parseFloat(document.getElementById("circleY").value), 
                        parseFloat(document.getElementById("circleZ").value)];
    var circleRadius = parseFloat(document.getElementById("circleRadius").value);

    var linePoints = getLinePoints(lineP1, lineP2, 100);
    var circlePoints = getCirclePoints(circleCenter, circleRadius, 100);

    var pathPoints = linePoints.concat(circlePoints);
    
    animateCamera(pathPoints);
};