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
    let d = 5.0 / 4.0 - radius;

    circlePoints(x, y);

    while (y > x) {
        if (d < 0) {
            d += 2.0 * x + 3.0;
        } else {
            d += 2.0 * (x - y) + 5.0;
            y--;
        }
        x++;
        circlePoints(x, y);
    }
}

// Example usage
let radius = 20;
midpointCircle(radius);
