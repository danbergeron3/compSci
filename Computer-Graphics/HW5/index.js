class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

function hermite(n, p1, p4, r1, r4) {
    let t = 0.0;
    const delta = 1.0 / n;
    let points = [p1];
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);

    // Gather all points
    for (let i = 1; i <= n; i++) {
        t = i * delta;
        const t2 = t * t;
        const t3 = t2 * t;
        const h1 = (2 * t3) - (3 * t2) + 1;
        const h2 = (-2 * t3) + (3 * t2);
        const h3 = t3 - (2 * t2) + t;
        const h4 = t3 - t2;                 

        const x = h1 * p1.x + h2 * p4.x + h3 * r1.x + h4 * r4.x;
        const y = h1 * p1.y + h2 * p4.y + h3 * r1.y + h4 * r4.y;

        points.push(new Point(x, y));
    }

    // Draw the curve
    for (let i = 0; i < points.length - 1; i++) {
        let x0 = points[i].x;
        let y0 = points[i].y;
        let x1 = points[i + 1].x;
        let y1 = points[i + 1].y;

        let dx = x1 - x0;
        let dy = y1 - y0;
        let steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);

        let Xinc = dx / steps;
        let Yinc = dy / steps;

        let X = x0;
        let Y = y0;

        for (let j = 0; j <= steps; j++) {
            setPixel(imageData, Math.round(X), Math.round(Y), 0, 0, 0, 255); 
            X += Xinc;
            Y += Yinc;
        }

        ctx.putImageData(imageData, 0, 0);
    }
}


function spline(n, p1, p2, p3, p4) {
    let t = 0.0;
    const delta = 1.0 / n;
    let points = [];
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);

    // Gather all points
    for (let i = 0; i <= n; i++) {
        t = i * delta;
        const t2 = t * t;
        const t3 = t2 * t;

        const x = (((1 - t3) / 6) * p1.x) + (((3 * t3 - 6 * t2 + 4) / 6) * p2.x) + 
        (((-3 * t3 + 3 * t2 + 3 * t + 1) / 6) * p3.x) + ((t3 / 6) * p4.x);
        const y = (((1 - t3) / 6) * p1.y) + (((3 * t3 - 6 * t2 + 4) / 6) * p2.y) + 
        (((-3 * t3 + 3 * t2 + 3 * t + 1) / 6) * p3.y) + ((t3 / 6) * p4.y);

        points.push(new Point(x, y));
    }

    // Draw the curve
    for (let i = 0; i < points.length - 1; i++) {
        let x0 = points[i].x;
        let y0 = points[i].y;
        let x1 = points[i + 1].x;
        let y1 = points[i + 1].y;

        let dx = x1 - x0;
        let dy = y1 - y0;
        let steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);

        let Xinc = dx / steps;
        let Yinc = dy / steps;

        let X = x0;
        let Y = y0;

        for (let j = 0; j <= steps; j++) {
            setPixel(imageData, Math.round(X), Math.round(Y), 0, 0, 0, 255);
            X += Xinc;
            Y += Yinc;
        }
        
        ctx.putImageData(imageData, 0, 0);
    }
}


function setPixel(imageData, x, y, r, g, b, a) {
    let index = (x + y * imageData.width) * 4;
    imageData.data[index + 0] = r;
    imageData.data[index + 1] = g;
    imageData.data[index + 2] = b;
    imageData.data[index + 3] = a;
}

function DDA(x0, y0, x1, y1) {
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);

    let dx = x1 - x0;
    let dy = y1 - y0;
    let steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);

    let Xinc = dx / steps;
    let Yinc = dy / steps;

    let X = x0;
    let Y = y0;

    for (let i = 0; i <= steps; i++) {
        setPixel(imageData, Math.round(X), Math.round(Y), 0, 0, 0, 255);
        X += Xinc;
        Y += Yinc;
    }

    ctx.putImageData(imageData, 0, 0);
}
// function DDA(x0, y0, x1, y1) {
//     let canvas = document.getElementById('canvas');
//     let ctx = canvas.getContext('2d');
//     ctx.fillStyle = 'black';

//     let dx = x1 - x0;
//     let dy = y1 - y0;
//     let steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);

//     let Xinc = dx / steps;
//     let Yinc = dy / steps;

//     let X = x0;
//     let Y = y0;

//     for (let i = 0; i <= steps; i++) {
//         ctx.fillRect(Math.round(X), Math.round(Y), 1, 1); // Drawing a pixel at the rounded (X,Y) position
//         X += Xinc;
//         Y += Yinc;
//     }
// }

function bezier(n, p1, p2, p3, p4) {
    let t = 0.0;
    const delta = 1.0 / n;
    let points = [p1];
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);

    // Gather points
    for (let i = 1; i <= n; i++) {
        t = i * delta;
        const t2 = t * t;
        const t3 = t2 * t;
        const q1 = (1 - t);
        const q2 = q1 * q1;
        const q3 = q2 * q1;

        const x = q3 * p1.x + (3 * t * q2) * p2.x + (3 * t2 * q1) * p3.x + t3 * p4.x;
        const y = q3 * p1.y + (3 * t * q2) * p2.y + (3 * t2 * q1) * p3.y + t3 * p4.y;

        points.push(new Point(x, y));
    }

    // Draw curve
    for (let i = 0; i < points.length - 1; i++) {
            let x0 = points[i].x;
            let y0 = points[i].y;
            let x1 = points[i + 1].x;
            let y1 = points[i + 1].y;
        
            let dx = x1 - x0;
            let dy = y1 - y0;
            let steps = Math.abs(dx) > Math.abs(dy) ? Math.abs(dx) : Math.abs(dy);

            let Xinc = dx / steps;
            let Yinc = dy / steps;

            let X = x0;
            let Y = y0;

            for (let i = 0; i <= steps; i++) {
                setPixel(imageData, Math.round(X), Math.round(Y), 0, 0, 0, 255);
                X += Xinc;
                Y += Yinc;
            }

            ctx.putImageData(imageData, 0, 0);
            }
    
}

function circlePoints(x, y, centerX, centerY, imageData) {
    setPixel(imageData, centerX + x, centerY + y, 0, 0, 0, 255);
    setPixel(imageData, centerX - x, centerY + y, 0, 0, 0, 255);
    setPixel(imageData, centerX + x, centerY - y, 0, 0, 0, 255);
    setPixel(imageData, centerX - x, centerY - y, 0, 0, 0, 255);
    setPixel(imageData, centerX + y, centerY + x, 0, 0, 0, 255);
    setPixel(imageData, centerX - y, centerY + x, 0, 0, 0, 255);
    setPixel(imageData, centerX + y, centerY - x, 0, 0, 0, 255);
    setPixel(imageData, centerX - y, centerY - x, 0, 0, 0, 255);
}


function midpointCircle(radius) {
    let x = 0;
    let y = radius;
    let d = 1 - radius;
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);
    let centerX = canvas.width / 2;
    let centerY = canvas.height / 2;

    circlePoints(x, y, centerX, centerY, imageData);

    while (y > x) {
        if (d < 0) {
            d = d + 2 * x + 3;
        } else {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        circlePoints(x, y, centerX, centerY, imageData);
    }

    ctx.putImageData(imageData, 0, 0);
}




function midpointEllipse(a, b) {
    let canvas = document.getElementById('canvas');
    let ctx = canvas.getContext('2d');
    let imageData = ctx.createImageData(canvas.width, canvas.height);
    
    let x = 0;
    let y = b;
    let d1 = (b * b) - (a * a * b) + (0.25 * a * a);

    // Function to draw points for all four quadrants
    function drawEllipsePoints(x, y) {
        // Central point of ellipse to be adjusted based on your requirements
        let centerX = canvas.width / 2;
        let centerY = canvas.height / 2;

        setPixel(imageData, centerX + x, centerY + y, 0, 0, 0, 255);
        setPixel(imageData, centerX - x, centerY + y, 0, 0, 0, 255);
        setPixel(imageData, centerX + x, centerY - y, 0, 0, 0, 255);
        setPixel(imageData, centerX - x, centerY - y, 0, 0, 0, 255);
    }

    drawEllipsePoints(x, y);

    // Region 1
    while ((a * a * (y - 0.5)) > (b * b * (x + 1))) {
        if (d1 < 0) {
            d1 += (b * b * (2 * x + 3));
        } else {
            d1 += (b * b * (2 * x + 3)) + (a * a * (-2 * y + 2));
            y--;
        }
        x++;
        drawEllipsePoints(x, y);
    }

    // Region 2
    let d2 = ((b * b * (x + 0.5) * (x + 0.5)) + (a * a * (y - 1) * (y - 1))) - (a * a * b * b);
    while (y > 0) {
        if (d2 < 0) {
            d2 += (b * b * (2 * x + 2)) + (a * a * (-2 * y + 3));
            x++;
        } else {
            d2 += (a * a * (-2 * y + 3));
        }
        y--;
        drawEllipsePoints(x, y);
    }

    ctx.putImageData(imageData, 0, 0);
}

function drawBezierCurveFromInput() {
    // Retrieve control points and number of segments from input fields
    let p1 = new Point(parseInt(document.getElementById('bezierX1').value), parseInt(document.getElementById('bezierY1').value));
    let p2 = new Point(parseInt(document.getElementById('bezierX2').value), parseInt(document.getElementById('bezierY2').value));
    let p3 = new Point(parseInt(document.getElementById('bezierX3').value), parseInt(document.getElementById('bezierY3').value));
    let p4 = new Point(parseInt(document.getElementById('bezierX4').value), parseInt(document.getElementById('bezierY4').value));
    let n = parseInt(document.getElementById('bezierSegments').value);

    bezier(n, p1, p2, p3, p4);
}

function drawHermiteCurveFromInput() {
    let p1 = new Point(parseInt(document.getElementById('hermiteX1').value), parseInt(document.getElementById('hermiteY1').value));
    let p4 = new Point(parseInt(document.getElementById('hermiteX4').value), parseInt(document.getElementById('hermiteY4').value));
    let r1 = new Point(parseInt(document.getElementById('hermiteRX1').value), parseInt(document.getElementById('hermiteRY1').value));
    let r4 = new Point(parseInt(document.getElementById('hermiteRX4').value), parseInt(document.getElementById('hermiteRY4').value));
    let n = parseInt(document.getElementById('hermiteSegments').value);

    hermite(n, p1, p4, r1, r4);
}

function drawMidpointCircleFromInput() {
    let radius = parseInt(document.getElementById('radius').value);
    midpointCircle(radius);
}

window.onload = function() {
    document.getElementById('bezierButton').addEventListener('click', drawBezierCurveFromInput);

    document.getElementById('drawHermiteButton').addEventListener('click', drawHermiteCurveFromInput);
    document.getElementById('drawSplineButton').addEventListener('click', function() {
        let p1 = new Point(parseInt(document.getElementById('splineX1').value), parseInt(document.getElementById('splineY1').value));
        let p2 = new Point(parseInt(document.getElementById('splineX2').value), parseInt(document.getElementById('splineY2').value));
        let p3 = new Point(parseInt(document.getElementById('splineX3').value), parseInt(document.getElementById('splineY3').value));
        let p4 = new Point(parseInt(document.getElementById('splineX4').value), parseInt(document.getElementById('splineY4').value));
        let n = parseInt(document.getElementById('splineSegments').value);
    
        spline(n, p1, p2, p3, p4);
    });
    document.getElementById('drawEllipseButton').addEventListener('click', function() {
        
        let a = parseInt(document.getElementById('ellipseA').value);
        let b = parseInt(document.getElementById('ellipseB').value);
    
        midpointEllipse(a, b);
    });
    
    document.getElementById('drawCircleButton').addEventListener('click', drawMidpointCircleFromInput);
}