
let mode = 'select';
let selectionStart = null;
let selectedShape = null;
let currentShape = null;

function initialize(){

    console.log("Loaded");
    document.getElementById("lineButton").addEventListener('click', function() { 
        initialize();  
        drawShape('line'); 
    });
    
    document.getElementById('circleButton').addEventListener('click', function() { 
        initialize(); 
        drawShape('circle'); 
    });
    document.getElementById('rectangleButton').addEventListener('click', function() { 
        initialize();
        drawShape('rectangle'); 
    });
    document.getElementById('triangleButton').addEventListener('click', function() { 
        initialize();
        drawShape('triangle'); 
    });
    document.getElementById('polygonButton').addEventListener('click', function() { 
        initialize();
        drawShape('polygon'); 
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
    document.getElementById('rotateOriginButton').addEventListener('click', function() { 
        mode = 'rotateOrigin';
        let text = `Current Mode: Rotate Origin`;
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
        currentShape = null;
        document.getElementById('selectedShapeInfo').innerText = `Selected Shape: none`;
        initialize(); 
    });
    
    document.body.addEventListener('mousedown', mouse_down);
    document.body.addEventListener('mouseup', mouse_up);
    document.body.addEventListener('mousemove', mouse_move);
        
    //Get the base layercanvas object
    canvas1 = document.getElementById("layer1");

    ctx1 = canvas1.getContext("2d");
    
    ctx1.fillStyle = "grey";

    ctx1.fillRect(0, 0, canvas1.width, canvas1.height);

    //Get the top layer canvas object
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
    let bbox = currentShape;
    if(bbox == null) {
        return;
    }
    // Check if the bounding box of the shape intersects with the selection box
    if (bbox.xMin < end.x && bbox.xMax > start.x &&
        bbox.yMin < end.y && bbox.yMax > start.y) {
        return currentShape;
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

// callback for mouse down events
function mouse_down(event) {
    let coords = getCanvasRelativeCoords(event, canvas1);
    if (coords.x >= 0 && coords.x <= canvas1.width && coords.y >= 0 && coords.y <= canvas1.height) {
        

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
    if (is_down && selectedShape) {
        console.log("applying transforamtion");
    }
    if(is_down)	{
        ctx2.clearRect(0, 0, canvas2.width, canvas2.height);

        // elastic band
        ctx2.strokeStyle = "yellow";
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
    if (xUp >= 0 && xUp <= canvas1.width && yUp >= 0 && yUp <= canvas1.height) {
        is_down = false;

        ctx2.clearRect(0, 0, canvas2.width, canvas2.height);
    
        let end = { x: xUp, y: yUp };
        console.log(mode);
        if(mode === 'select' ) {
            let selectedShape = getShapeWithinSelection(selectionStart, end);
            console.log('Curr Shape ' + selectedShape);
            if (selectedShape) {
                displaySelectedShapeInfo(selectedShape);
            }
        }
    }
    displayCoords = "X: "+ xUp + " Y: " + yUp +" is_down = " + is_down;

    document.getElementById("val3").innerHTML = displayCoords;
   
}

function drawShape(shape) {
    console.log(`drawShape called with shape: ${shape}`);

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
            currentShape = {
                type: 'line',
                xMin: Math.min(100, 50),
                xMax: Math.max(100, 50),
                yMin: 75,  // since y is the same for both points
                yMax: 75,
                area: Math.sqrt(Math.pow(100 - 50, 2) + Math.pow(75 - 75, 2))
            }
            break;
        case 'circle':
            ctx1.fillStyle = "red";
            const degToRad = (degrees) => (Math.PI / 180) * degrees;
            ctx1.arc(100, 100, 50, degToRad(0), degToRad(360), true);
            ctx1.fill();
            
            currentShape = {
                type: 'circle',
                xMin: 100 - 50, // centerX - radius
                xMax: 100 + 50, // centerX + radius
                yMin: 100 - 50, // centerY - radius
                yMax: 100 + 50,  // centerY + radius
                area: Math.PI * 50 * 50
            };
            break;
        case 'rectangle':
            ctx1.fillStyle = "red";
            ctx1.fillRect(20, 20, 150, 100);
            currentShape = {
                type: 'rectangle',
                xMin: 20,
                xMax: 20 + 150,
                yMin: 20,
                yMax: 20 + 100,
                area: 150 * 100 
            };
            break;
        case 'triangle':
            const length = 50;
            const height = length * (Math.sqrt(3)/2);
            const startX = 100;
            const startY = 75; 
        
            ctx1.fillStyle = "red";
            ctx1.beginPath();
            ctx1.moveTo(startX, startY);
            ctx1.lineTo(startX + length / 2, startY + height); 
            ctx1.lineTo(startX - length / 2, startY + height); 
            ctx1.lineTo(startX, startY);
            ctx1.closePath();
            ctx1.stroke();
            ctx1.fill();
            
            currentShape = {
                type: 'triangle',
                xMin: startX - length / 2,
                xMax: startX + length / 2,
                yMin: startY,
                yMax: startY + height,
                area: (length * height) / 2
            };

            break;
        case 'polygon':
            const numSides = 5; // Number of sides for the polygon, e.g., 5 for a pentagon
            const centerX = 100; // X-coordinate of the polygon's center
            const centerY = 100; // Y-coordinate of the polygon's center
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
            currentShape = {
                type: 'polygon',
                xMin: centerX - radius,
                xMax: centerX + radius,
                yMin: centerY - radius,
                yMax: centerY + radius,
                area: area
            };
            break;
        default:
            console.log(`Shape ${shape} not recognized`);
            return;
    }
    console.log('Current Shape' + currentShape);
    ctx1.fill(); // Or ctx1.fill() if you want solid shapes
}

function applyTransform(transformType) {
    console.log(`applyTransform called with transform: ${transform}`);
    
}

