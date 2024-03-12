
let mode = 'select';
let selectionStart = null;
let selectedShape = null;
let curShape = null;
let isDrawing = false;

function initialize(){

    console.log("Loaded");
    document.getElementById("lineButton").addEventListener('click', function() { 
        initialize();  
        quickDrawShape('line'); 
    });
    
    document.getElementById('circleButton').addEventListener('click', function() { 
        initialize(); 
        quickDrawShape('circle'); 
    });
    document.getElementById('rectangleButton').addEventListener('click', function() { 
        initialize();
        quickDrawShape('rectangle'); 
    });
    document.getElementById('triangleButton').addEventListener('click', function() { 
        initialize();
        quickDrawShape('triangle'); 
    });
    document.getElementById('polygonButton').addEventListener('click', function() { 
        initialize();
        quickDrawShape('polygon'); 
    });
    
    document.getElementById('translateButton').addEventListener('click', function() { 
        mode = 'translate';
        document.getElementById('mode').innerText = `Current Mode: Translate`;
    });
    document.getElementById('scaleButton').addEventListener('click', function() { 
        mode = 'scale'; 
        let text = `Current Mode: Scale`;
        document.getElementById('mode').innerText = text;
    });
    document.getElementById('rotateButton').addEventListener('click', function() { 
        mode = 'rotate';
        let text = `Current Mode: Rotate`;
        document.getElementById('mode').innerText = text;
    });
    document.getElementById('select').addEventListener('click', function() { 
        mode = 'select';
        let text = `Current Mode: Select`;
        document.getElementById('mode').innerText = text;
    });
    document.getElementById('reset').addEventListener('click', function() { 
        mode = 'select';
        document.getElementById('mode').innerText = `Current Mode: Select`;
        selectionStart = null;
        selectedShape = null;
        curShape = null;
        document.getElementById('selectedShapeInfo').innerText = `Selected Shape: none`;
        ctx1.clearRect(0, 0, canvas1.width, canvas1.height);
        initialize(); 
    });
    

    document.getElementById('draw').addEventListener('click', () => {
        mode = 'draw';
        let text = `Current Mode: Draw`;
        document.getElementById('mode').innerText = text;
    });
    document.getElementById('drawLineButton').addEventListener('click', () => {
        
        selectedShape = {
            type: 'line',
            xMin: 0,
            xMax: 0,
            yMin: 0,  // since y is the same for both points
            yMax: 0,
            area: 0
        };
    });
    document.getElementById('drawCircleButton').addEventListener('click', () => {
        selectedShape = {
            type: 'circle',
            xMin: 0, // centerX - radius
            xMax: 0, // centerX + radius
            yMin: 0, // centerY - radius
            yMax: 0,  // centerY + radius
            area: 0,
            radius: 0,
            centerX: 0,
            centerY: 0,
        };
    });
    document.getElementById('drawPolygonButton').addEventListener('click', () => {
        selectedShape = {
            type: 'polygon',
            xMin: 0,
            xMax: 0,
            yMin: 0,
            yMax: 0,
            area: 0,
            radius: 0, 
            centerX: 0,
            centerY: 0,
            numSides: 0
        };
    });
    document.getElementById('drawRectangleButton').addEventListener('click', () => {
        selectedShape = {
            type: 'rectangle',
            xMin: 0,
            xMax: 0,
            yMin: 0,
            yMax: 0,
            area: 0, 
            width: 0,
            height: 0
        };
    });
    document.getElementById('drawTriangleButton').addEventListener('click', () => {
        selectedShape = {
            type: 'triangle',
            xMin: 0,
            xMax: 0,
            yMin: 0,
            yMax: 0,
            area: 0,
            width: 0,
            height: 0,
            centerX: 0,
            centerY: 0
        };
    });

    document.body.addEventListener('mousedown', mouse_down);
    document.body.addEventListener('mouseup', mouse_up);
    document.body.addEventListener('mousemove', mouse_move);
        
    //Get the base layercanvas object
    canvas1 = document.getElementById("layer1");

    ctx1 = canvas1.getContext("2d");
    
    canvas2 = document.getElementById("layer2");

    ctx2 = canvas2.getContext("2d");	

    is_down = false;// mouse hasn't been pressed
}


// display shape info
function displaySelectedShapeInfo(shape) {
    let info = `Selected Shape: ${shape.type}, Position: (x: (${shape.xMin}, ${shape.xMax}), 
        y: (${shape.yMin}, ${shape.yMax})), Size: ${shape.area}`;
    document.getElementById('selectedShapeInfo').innerText = info;
}

function getShapeWithinSelection(start, end) {
    
    // Determine the bounding box of the shape
    let bbox = selectedShape;
    if(bbox == null) {
        return;
    }
    // Check if the bounding box of the shape intersects with the selection box
    if (bbox.xMin < end.x && bbox.xMax > start.x &&
        bbox.yMin < end.y && bbox.yMax > start.y) {
        curShape = selectedShape;
        return curShape;
    }

    return null; // No shape found within the selection
}

// function to get canvas cordinates
function getCanvasRelativeCoords(event, canvas) {
    var rect = canvas.getBoundingClientRect();
    return {
        x: event.clientX - rect.left,
        y: event.clientY - rect.top
    };
}


function calculateScaleFactor(coords) {
    // Implement logic to calculate scale factor based on mouse movement
    return 1 + (coords.y - yDown) / 10000;
}

function calculateRotationAngle(coords) {
    let deltaY = coords.y - yDown; // Assuming rotation based on vertical mouse movement
    let angle = deltaY * 0.5; // Adjust sensitivity as needed
    return angle;
}

function applyTransformation(shape, transformType, value) {
    if (shape == null) return;

    switch (transformType) {
        case 'scale':
            // Example of scaling (this will depend on shape type)
            // For rectangles or similar shapes:
            if (shape.type === 'rectangle') {
                shape.width *= value;
                shape.height *= value;

                // ensure it fits 
                if(shape.width < 100 || shape.height < 100) {
                    shape.width = 100;
                    shape.height = 100;
                } else if (shape.width > canvas1.width 
                    || shape.height > canvas1.height) {
                        shape.height = canvas1.width - 100;
                        shape.height = canvas1.height - 100;
                }
                // Update bounding box
                shape.xMax = shape.xMin + shape.width;
                shape.yMax = shape.yMin + shape.height;
                // Update area
                shape.area = shape.width * shape.height;
            }
            // For circles:
            if (shape.type === 'circle') {
                shape.radius *= value;
                if(shape.radius > canvas1.width) {
                    shape.radius = canvas1.width -100;
                }
                if(shape.radius < 25) {
                    shape.radius = 25;
                }
                // Update bounding box
                shape.xMin = shape.centerX - shape.radius;
                shape.xMax = shape.centerX + shape.radius;
                shape.yMin = shape.centerY - shape.radius;
                shape.yMax = shape.centerY + shape.radius;
                // Update area
                shape.area = Math.PI * Math.pow(shape.radius, 2);
            }


            // For triangles:
            if (shape.type === 'triangle') {
                // Assuming the width of the triangle is the length of its base
                // Estimate centroid (center point) of the triangle
                const currentCentroidX = (shape.xMin + shape.xMax) / 2;
                const currentCentroidY = shape.yMax;  // Assuming yMax is the base of the triangle

                // Scale width and height
                const oldWidth = shape.xMax - shape.xMin;
                const oldHeight = shape.yMax - shape.yMin; // Assuming yMin is at the top of the triangle
                const newWidth = oldWidth * value;
                const newHeight = oldHeight * value;

                // Reposition bounding box to keep the centroid in the same position
                shape.xMin = currentCentroidX - newWidth / 2;
                shape.xMax = currentCentroidX + newWidth / 2;
                shape.yMax = currentCentroidY;  // yMax remains the same as the base of the triangle
                shape.yMin = currentCentroidY - newHeight; // Adjust yMin based on the new height

                // Update area
                shape.area = (newWidth * newHeight) / 2
            }

            // For polygons:
            if (shape.type === 'polygon') {
                shape.radius *= value;

                // Update bounding box
                shape.xMin = shape.centerX - shape.radius;
                shape.xMax = shape.centerX + shape.radius;
                shape.yMin = shape.centerY - shape.radius;
                shape.yMax = shape.centerY + shape.radius;
                // Update area, assuming it's a regular polygon
                const numSides = shape.numSides;

                shape.area = (numSides * Math.pow(shape.radius, 2) * Math.sin((2 * Math.PI) / numSides)) / 2;
            }
    
            break;

        case 'rotate':
            if (shape.type === 'line') {
                const radians = value * Math.PI / 180; // Convert rotation angle to radians
        
                // Calculate the center (midpoint) of the line
                const centerX = (shape.xMin + shape.xMax) / 2;
                const centerY = (shape.yMin + shape.yMax) / 2;
        
                // Define the endpoints of the line
                let start = { x: shape.xMin, y: shape.yMin };
                let end = { x: shape.xMax, y: shape.yMax };
        
                // Function to rotate a point around the center
                const rotatePoint = (point) => {
                    let translatedX = point.x - centerX;
                    let translatedY = point.y - centerY;
                    return {
                        x: translatedX * Math.cos(radians) - translatedY * Math.sin(radians) + centerX,
                        y: translatedX * Math.sin(radians) + translatedY * Math.cos(radians) + centerY
                    };
                };
        
                // Rotate each endpoint
                start = rotatePoint(start);
                end = rotatePoint(end);
        
                // Update the shape properties
                shape.xMin = start.x;
                shape.yMin = start.y;
                shape.xMax = end.x;
                shape.yMax = end.y;
            }
            if (shape.type === 'rectangle') {
                console.log('rotate shape here')
                const radians = value * Math.PI / 180; // Convert rotation angle to radians

                // Calculate the center point of the rectangle
                const centerX = shape.centerX;
                const centerY = shape.centerY;

                // Function to rotate a point around the center
                const rotatePoint = (x, y) => {
                    let translatedX = x - centerX;
                    let translatedY = y - centerY;
                    return {
                        x: translatedX * Math.cos(radians) - translatedY * Math.sin(radians) + centerX,
                        y: translatedX * Math.sin(radians) + translatedY * Math.cos(radians) + centerY
                    };
                };

                // Calculate the corners of the rectangle before rotation
                let halfWidth = shape.width / 2;
                let halfHeight = shape.height / 2;
                let corners = [
                    { x: centerX - halfWidth, y: centerY - halfHeight }, // Top-left
                    { x: centerX + halfWidth, y: centerY - halfHeight }, // Top-right
                    { x: centerX - halfWidth, y: centerY + halfHeight }, // Bottom-left
                    { x: centerX + halfWidth, y: centerY + halfHeight }  // Bottom-right
                ];

                // Rotate each corner around the center
                shape.corners = corners.map(corner => rotatePoint(corner.x, corner.y));
                console.log('Corners:', shape.corners.map(corner => `(${corner.x.toFixed(2)}, ${corner.y.toFixed(2)})`).join(', '));
                // Update shape properties based on the new corners
                
                
            }
            if (shape.type === 'triangle') {
                const radians = value * Math.PI / 180; // Convert rotation angle to radians

                // Calculate the vertices of the triangle
                const vertex1 = { x: shape.centerX, y: shape.centerY - shape.height }; // Top vertex
                const vertex2 = { x: shape.centerX - shape.width / 2, y: shape.centerY }; // Bottom left
                const vertex3 = { x: shape.centerX + shape.width / 2, y: shape.centerY }; // Bottom right

                // Function to rotate a point around the center
                const rotatePoint = (x, y, centerX, centerY) => {
                    let translatedX = x - centerX;
                    let translatedY = y - centerY;
                    return {
                        x: translatedX * Math.cos(radians) - translatedY * Math.sin(radians) + centerX,
                        y: translatedX * Math.sin(radians) + translatedY * Math.cos(radians) + centerY
                    };
                };

                // Rotate each vertex of the triangle
                shape.vertex1 = rotatePoint(vertex1.x, vertex1.y, shape.centerX, shape.centerY);
                shape.vertex2 = rotatePoint(vertex2.x, vertex2.y, shape.centerX, shape.centerY);
                shape.vertex3 = rotatePoint(vertex3.x, vertex3.y, shape.centerX, shape.centerY);

            }
            if (shape.type === 'polygon') {
                const radians = value * Math.PI / 180; // Convert rotation angle to radians

                // Calculate vertices of the polygon
                let vertices = [];
                for (let i = 0; i < shape.numSides; i++) {
                    const angle = 2 * Math.PI / shape.numSides * i;
                    const x = shape.centerX + shape.radius * Math.cos(angle);
                    const y = shape.centerY + shape.radius * Math.sin(angle);
                    vertices.push({ x, y });
                }

                // Function to rotate a point around the center
                const rotatePoint = (x, y, centerX, centerY) => {
                    let translatedX = x - centerX;
                    let translatedY = y - centerY;
                    return {
                        x: translatedX * Math.cos(radians) - translatedY * Math.sin(radians) + centerX,
                        y: translatedX * Math.sin(radians) + translatedY * Math.cos(radians) + centerY
                    };
                };

                // Rotate each vertex
                shape.vertices = vertices.map(vertex => rotatePoint(vertex.x, vertex.y, shape.centerX, shape.centerY));
            }
        break;
        case 'translate':
            // Calculate the new center position
            let newCenterX = x;
            let newCenterY = y;

            // Calculate the deltas needed to move the shape's center to the new position
            let deltaX = newCenterX - shape.centerX;
            let deltaY = newCenterY - shape.centerY;

            console.log(`deltaX: ${deltaX} deltaY: ${deltaY}`);

            // Adjust the position of the shape
            shape.xMin += deltaX;
            shape.xMax += deltaX;
            shape.yMin += deltaY;
            shape.yMax += deltaY;

            // Update the center position of the shape
            shape.centerX += deltaX;
            shape.centerY += deltaY;
            
    // For other shape types, similar logic can be applied based on their properties
        break;
        // Add other cases like 'translate' if needed
    }
}

function redrawCanvas(shape) {
    ctx1.clearRect(0, 0, canvas1.width, canvas1.height);

    if (mode === 'rotate') {
        if (shape.type === 'rectangle'){
            drawRotatedRectangle(ctx1, shape);
        } else if (shape.type === 'triangle') {
            ctx1.beginPath();
            ctx1.moveTo(shape.vertex1.x, shape.vertex1.y);
            ctx1.lineTo(shape.vertex2.x, shape.vertex2.y);
            ctx1.lineTo(shape.vertex3.x, shape.vertex3.y);
            ctx1.closePath(); // Closes the path back to the first vertex
            ctx1.stroke();
        } else if (shape.type === 'polygon') {
            drawRotatedPolygon(ctx1, shape);       
        }
    } else {
        // draw other shapes
        drawShape(shape);
    }
}

function drawShape(shape) {
    switch (shape.type) {
        case 'line':
            // Draw line
            ctx1.beginPath();
            ctx1.moveTo(shape.xMin, shape.yMin);
            ctx1.lineTo(shape.xMax, shape.yMax);
            ctx1.stroke();
            break;
        case 'circle':
            // Draw circle
            ctx1.beginPath();
            ctx1.arc(shape.centerX, shape.centerY, shape.radius, 0, 2 * Math.PI);
            ctx1.fill();
            break;
        case 'rectangle':
            // Draw rectangle
            ctx1.fillRect(shape.xMin, shape.yMin, shape.width, shape.height);
            break;
        case 'triangle':
            
            drawTriangle(shape.xMin, shape.yMin, shape.xMax, shape.yMax);
            break;
        case 'polygon':
            // Draw polygon
            ctx1.beginPath();
            const numSides = shape.numSides;
            for (let i = 0; i <= numSides; i++) {
                const angle = 2 * Math.PI / numSides * i;
                const x = shape.centerX + shape.radius * Math.cos(angle);
                const y = shape.centerY + shape.radius * Math.sin(angle);
                
                if (i === 0) {
                    ctx1.moveTo(x, y);
                } else {
                    ctx1.lineTo(x, y);
                }
            }
            ctx1.closePath();
            ctx1.fill();
            break;
    }
}

function drawLine(ctx1, x1, y1, x2, y2) {
    ctx1.beginPath();
    ctx1.moveTo(x1, y1);
    ctx1.lineTo(x2, y2);
    ctx1.stroke();
    
}

function drawRectangle(ctx1, x1, y1, x2, y2) {
    ctx1.clearRect(0, 0, canvas1.width, canvas1.height); // Clear the canvas
    ctx1.beginPath();
    var width = x2 - x1;
    var height = y2 - y1;
    ctx1.rect(x1, y1, width, height);
    ctx1.stroke();
    let dimensions =  {
        height: height,
        width: width
    };
    ctx1.fill();
    return dimensions;
}

function drawRotatedPolygon(ctx, shape) {
    if (shape.type === 'polygon' && shape.vertices) {
        ctx.beginPath();
        ctx.moveTo(shape.vertices[0].x, shape.vertices[0].y);
        for (let i = 1; i < shape.vertices.length; i++) {
            ctx.lineTo(shape.vertices[i].x, shape.vertices[i].y);
        }
        ctx.closePath();
        ctx.stroke();
    }
}

function drawTriangle(x1, y1, x2, y2) {
    const length = x2 - x1;
    const height = y2 - y1;

    ctx1.clearRect(0, 0, canvas1.width, canvas1.height); // Clear canvas
    ctx1.fillStyle = "red";
    ctx1.beginPath();
    ctx1.moveTo(x1, y1);
    ctx1.lineTo(x1 + length, y1 + height);
    ctx1.lineTo(x1 - length, y1 + height);
    ctx1.closePath();
    ctx1.stroke();
    ctx1.fill();
    selectedShape = {
        type: 'triangle',
        xMin: x1,
        xMax: x2,
        yMin: y1,
        yMax: y2,
        area: (length * height)/2, // Area formula for this specific triangle configuration
        width: length, // Total width from xMin to xMax
        height: height, // Height as provided
        centerX: (x1 + (x1 + length) + (x1 - length)) / 3, // Average x of all vertices
        centerY: (y1 + (y1 + height) + (y1 + height)) / 3 // Average y of all vertices
    };
}

function rubberBand(x, y) {
    switch(selectedShape.type) {
        case 'line':
            drawLine(ctx1, selectionStart.x, selectionStart.y, x, y);
            
            selectedShape.xMin = selectionStart.x;
            selectedShape.xMax = x;
            selectedShape.yMin = selectionStart.y;
            selectedShape.yMax = y;
            selectedShape.centerX = (selectionStart.x + x) / 2;
            selectedShape.centerY = (selectionStart.y + y) / 2;
            area = 0;

        break;
        case 'rectangle':
            
            let dimensions = drawRectangle(ctx1, selectionStart.x, selectionStart.y, x, y);
            selectedShape.xMin = selectionStart.x;
            selectedShape.xMax = x;
            selectedShape.yMin = selectionStart.y;
            selectedShape.yMax = y;
            selectedShape.area = dimensions.height * dimensions.width;
            selectedShape.width = dimensions.width;
            selectedShape.height = dimensions.height;
            selectedShape.centerX = (selectedShape.xMin + selectedShape.xMax) / 2;
            selectedShape.centerY = (selectedShape.yMin + selectedShape.yMax) / 2;
        
        break;
        case 'circle':
            let radius = Math.sqrt(Math.pow(x - selectionStart.x, 2) + Math.pow(y - selectionStart.y, 2));
            ctx1.clearRect(0, 0, canvas1.width, canvas1.height);
            ctx1.beginPath();
            ctx1.arc(selectionStart.x, selectionStart.y, radius, 0, Math.PI * 2, false);
            ctx1.stroke(); 
            
            selectedShape.xMin = selectionStart.x - radius;
            selectedShape.xMax = selectionStart.x + radius;
            selectedShape.yMin = selectionStart.y - radius;
            selectedShape.yMax = selectionStart.y + radius;
            selectedShape.area = Math.PI * Math.pow(radius, 2);
            selectedShape.radius = radius;
            selectedShape.centerX = selectionStart.x;
            selectedShape.centerY = selectionStart.y;
        break;
        case 'triangle':
            drawTriangle(selectionStart.x, selectionStart.y, x, y);     
        break;
        case 'polygon':
            const numSides = 5;
            let dx = x - selectionStart.x;
            let dy = y - selectionStart.y;
            let rad = Math.sqrt(dx * dx + dy * dy); // Dynamic radius based on mouse position

            ctx1.clearRect(0, 0, canvas1.width, canvas1.height); // Clear the canvas

            ctx1.beginPath();
            for (let i = 0; i <= numSides; i++) {
                const angle = 2 * Math.PI / numSides * i;
                const px = selectionStart.x + rad * Math.cos(angle);
                const py = selectionStart.y + rad * Math.sin(angle);
                if (i === 0) {
                    ctx1.moveTo(px, py);
                } else {
                    ctx1.lineTo(px, py);
                }
            }
            ctx1.closePath();
            ctx1.stroke();

            let polygonArea = (numSides * Math.pow(rad, 2) * Math.sin((2 * Math.PI) / numSides)) / 2;

            selectedShape = {
                type: 'polygon',
                xMin: selectionStart.x - rad,
                xMax: selectionStart.x + rad,
                yMin: selectionStart.y - rad,
                yMax: selectionStart.y + rad,
                area: polygonArea,
                radius: rad,
                centerX: selectionStart.x,
                centerY: selectionStart.y,
                numSides: numSides
            };
        break;
    }
}



// callback for mouse down events
function mouse_down(event) {
    let coords = getCanvasRelativeCoords(event, canvas1);
    if (coords.x >= 0 && coords.x <= canvas1.width && coords.y >= 0 && coords.y <= canvas1.height) {
        if(mode === 'draw') {
            isDrawing = true;
        }

        xDown = coords.x;
        yDown = coords.y;
        
        is_down = true;

        selectionStart = { x: xDown, y: yDown };
        let displayCoords = "X: "+ xDown + " Y: " + yDown + " is_down = " + is_down;

        document.getElementById("val1").innerHTML = displayCoords;
    }
}


// callback for mouse move events
function mouse_move(event) {
    let coords = getCanvasRelativeCoords(event, canvas1);
    x = coords.x;
    y = coords.y;
    // console.log("mouse down:" + is_down + "shape: " + selectedShape);
    if (isDrawing && is_down) { // Clears the canvas
        ctx1.clearRect(0, 0, canvas1.width, canvas1.height)
        rubberBand(x,y);
    }
    if (is_down && curShape && mode != 'select' && mode != 'draw') {
        
        if (mode === 'scale') {
            let scaleFactor = calculateScaleFactor(coords);
            applyTransformation(selectedShape, 'scale', scaleFactor);
        } else if (mode === 'rotate') {
            let angle = calculateRotationAngle(coords);
            applyTransformation(selectedShape, 'rotate', angle);
            
        } else if (mode === 'translate') {
            // Check if the bounding box of the shape intersects with the selection box
            applyTransformation(selectedShape, 'translate', 0);
            
        }
        redrawCanvas(selectedShape);
    
    }
    if(is_down)	{
        ctx2.clearRect(0, 0, canvas2.width, canvas2.height);

        // elastic band
        ctx2.strokeStyle = "black";
        ctx2.strokeRect(xDown,yDown, x-xDown, y-yDown);
    }

    let displayCoords = "X: "+ x + " Y: " + y +" is_down = " + is_down;	
    document.getElementById("val2").innerHTML = displayCoords;
}


// callback for mouse up events
function mouse_up(event) {
    
    var coords = getCanvasRelativeCoords(event, canvas1);
    
    xUp = coords.x;
    yUp = coords.y;

    if (isDrawing) {
        ctx1.clearRect(0, 0, canvas1.width, canvas1.height)
        rubberBand(xUp, yUp);
        isDrawing = false;
    }

    if (xUp >= 0 && xUp <= canvas1.width && yUp >= 0 && yUp <= canvas1.height) {
        is_down = false;

        ctx2.clearRect(0, 0, canvas2.width, canvas2.height);
    
        let end = { x: xUp, y: yUp };
        console.log(mode);
        console.log(selectedShape);
        if(mode === 'select' ) {
            let curShape = getShapeWithinSelection(selectionStart, end);
            console.log('Curr Shape ' + curShape);
            if (curShape) {
                displaySelectedShapeInfo(curShape);
            }
        }
    }
    displayCoords = "X: "+ xUp + " Y: " + yUp +" is_down = " + is_down;

    document.getElementById("val3").innerHTML = displayCoords;
   
}

function drawRotatedRectangle(ctx, shape) {
    console.log("rotating rec")
    if (shape.type === 'rectangle' && shape.corners && shape.corners.length === 4) {
        ctx.beginPath();
        // Move to the first corner
        ctx.moveTo(shape.corners[0].x, shape.corners[0].y);

        ctx.lineTo(shape.corners[2].x, shape.corners[2].y);
        ctx.lineTo(shape.corners[3].x, shape.corners[3].y);
        ctx.lineTo(shape.corners[1].x, shape.corners[1].y);

        // Close the path to complete the rectangle
        ctx.closePath();

        // Stroke or fill the rectangle as desired
        ctx.stroke(); // To only draw the outline
        // ctx.fill(); // To fill the rectangle
    }
}

function quickDrawShape(shape) {
    console.log(`drawShape called with shape: ${shape}`);
    ctx1.clearRect(0, 0, canvas1.width, canvas1.height);
    ctx1.beginPath();

    // Set the drawing color to orange
    ctx1.strokeStyle = 'red';
    ctx1.fillStyle = 'orange';

    ctx1.beginPath();

    switch (shape) {
        case 'line':
            ctx1.fillStyle = "red";
            ctx1.beginPath();
            ctx1.moveTo(100, 75); // Move to the starting point
            ctx1.lineTo(50, 75);     // Draw a line to the ending point
            ctx1.stroke();

            selectedShape = {
                type: 'line',
                xMin: Math.min(100, 50),
                xMax: Math.max(100, 50),
                yMin: 75,  // since y is the same for both points
                yMax: 75,
                area: 0,
                centerX: (100 + 50) / 2,
                centerY: 75
            };
            break;
        case 'circle':
            ctx1.fillStyle = "red";
            const degToRad = (degrees) => (Math.PI / 180) * degrees;
            ctx1.arc(100, 100, 50, degToRad(0), degToRad(360), true);
            ctx1.fill();
            
            selectedShape = {
                type: 'circle',
                xMin: 100 - 50, // centerX - radius
                xMax: 100 + 50, // centerX + radius
                yMin: 100 - 50, // centerY - radius
                yMax: 100 + 50,  // centerY + radius
                area: Math.PI * 50 * 50,
                radius: 50,
                centerX: 100,
                centerY: 100,
            };

            break;
        case 'rectangle':
            ctx1.fillStyle = "red";
            ctx1.fillRect(200, 200, 150, 100);

            selectedShape = {
                type: 'rectangle',
                xMin: 200,
                xMax: 200 + 150,
                yMin: 200,
                yMax: 200 + 100,
                area: 150 * 100, 
                width: 150,
                height: 100,
                centerX: (200 + (200 + 150)) / 2,
                centerY: (200 + (200 + 100)) / 2 
            };
            break;
        case 'triangle':
            const length = 50;
            const height = length * (Math.sqrt(3)/2);
            const startX = 100;
            const startY = 75; 
            centerX = (startX + (startX + length / 2) + (startX - length / 2)) / 3;
            centerY = (startY + (startY + height) + (startY + height)) / 3;

            ctx1.fillStyle = "red";
            ctx1.beginPath();
            ctx1.moveTo(startX, startY);
            ctx1.lineTo(startX + length / 2, startY + height); 
            ctx1.lineTo(startX - length / 2, startY + height); 
            ctx1.lineTo(startX, startY);
            ctx1.closePath();
            ctx1.stroke();
            ctx1.fill();
           
            selectedShape = {
                type: 'triangle',
                xMin: startX - length / 2,
                xMax: startX + length / 2,
                yMin: startY,
                yMax: startY + height,
                area: (length * height) / 2,
                width: length,
                height: height,
                centerX: centerX,
                centerY: centerY
            };

            break;
        case 'polygon':
            const numSides = 5; // Number of sides for the polygon, e.g., 5 for a pentagon
            centerX = 100; // X-coordinate of the polygon's center
            centerY = 100; // Y-coordinate of the polygon's center
            const radius = 50; // Radius of the circumcircle of the polygon
            
            ctx1.fillStyle = "red";
            ctx1.beginPath();
            for (let i = 0; i <= numSides; i++) {
                const angle = 2 * Math.PI / numSides * i;
                const x = centerX + radius * Math.cos(angle);
                const y = centerY + radius * Math.sin(angle);
                if (i === 0) {
                    ctx1.moveTo(x, y);
                } else {
                    ctx1.lineTo(x, y);
                }
            }
            ctx1.closePath();
            ctx1.stroke();
            const area = (numSides * Math.pow(radius, 2) * Math.sin((2 * Math.PI) / numSides)) / 2; 
            selectedShape = {
                type: 'polygon',
                xMin: centerX - radius,
                xMax: centerX + radius,
                yMin: centerY - radius,
                yMax: centerY + radius,
                area: area,
                radius: radius, 
                centerX: centerX,
                centerY: centerY,
                numSides: numSides
            };
            break;
        default:
            console.log(`Shape ${shape} not recognized`);
            return;
    }
    console.log('Current Shape' + selectedShape);
    ctx1.fill(); // Or ctx1.fill() if you want solid shapes
}

function applyTransform(transformType) {
    console.log(`applyTransform called with transform: ${transform}`);
    
}

