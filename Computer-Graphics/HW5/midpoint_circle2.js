function circlePoints(x, y) {
    console.log(`x=${x}, y=${y}`);
    console.log(`x=${y}, y=${x}`);
    console.log(`x=${y}, y=${-x}`);
    console.log(`x=${x}, y=${-y}`);
    console.log(`x=${-x}, y=${-y}`);
    console.log(`x=${-y}, y=${-x}`);
    console.log(`x=${-y}, y=${x}`);
    console.log(`x=${-x}, y=${y}`);
}

function midpointCircle(radius) {
    let x = 0;
    let y = radius;
    let d = 1 - radius;
    circlePoints(x, y);

    while (y > x) {
        if (d < 0) {
            d = d + 2 * x + 3;
        } else {
            d = d + 2 * (x - y) + 5;
            y--;
        }
        x++;
        circlePoints(x, y);
    }
}

let radius = 20;
midpointCircle(radius);
