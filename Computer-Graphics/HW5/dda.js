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
        setPixel(imageData, Math.round(X), Math.round(Y), 0, 0, 0, 255); // Set black pixel
        X += Xinc;
        Y += Yinc;
    }

    ctx.putImageData(imageData, 0, 0); // Put the image data back on the canvas
}

// Example usage
// let x0 = 10;
// let y0 = 10;
// let x1 = 150;
// let y1 = 100;

// DDA(x0, y0, x1, y1);

// Example usage
// let x0 = 1;
// let y0 = 2;
// let x1 = 20;
// let y1 = 8;

// DDA(x0, y0, x1, y1);