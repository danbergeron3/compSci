class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
}

function printPoint(p) {
    console.log(`x=${p.x} y=${p.y}`);
}

function printTXY(t, x, y) {
    console.log(`t=${t} x=${x} y=${y}`);
}

function hermite(n, p1, p4, r1, r4) {
    let t, x, y;
    const delta = 1.0 / n;

    console.log("HERMITE:");
    console.log("p1: ", printPoint(p1));
    console.log("p4: ", printPoint(p4));
    console.log("r1: ", printPoint(r1));
    console.log("r4: ", printPoint(r4));
    console.log("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    printTXY(t, x, y);

    for (let i = 0; i < n; i++) {
        t += delta;
        const t2 = t * t;
        const t3 = t2 * t;

        x = ((2 * t3) - (3 * t2) + 1) * p1.x + ((-2 * t3) + (3 * t2)) * p4.x + (t3 - (2 * t2) + t) * r1.x + (t3 - t2) * r4.x;
        y = ((2 * t3) - (3 * t2) + 1) * p1.y + ((-2 * t3) + (3 * t2)) * p4.y + (t3 - (2 * t2) + t) * r1.y + (t3 - t2) * r4.y;
        printTXY(t, x, y);
    }
    console.log("\n\n");
}

function bezier(n, p1, p2, p3, p4) {
    let t, x, y;
    const delta = 1.0 / n;

    console.log("BEZIER:");
    console.log("p1: ", printPoint(p1));
    console.log("p2: ", printPoint(p2));
    console.log("p3: ", printPoint(p3));
    console.log("p4: ", printPoint(p4));
    console.log("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    printTXY(t, x, y);

    for (let i = 0; i < n; i++) {
        t += delta;
        const t2 = t * t;
        const t3 = t2 * t;
        const q1 = (1 - t);
        const q2 = q1 * q1;
        const q3 = q2 * q1;

        x = q3 * p1.x + (3 * t * q2) * p2.x + (3 * t2 * q1) * p3.x + t3 * p4.x;
        y = q3 * p1.y + (3 * t * q2) * p2.y + (3 * t2 * q1) * p3.y + t3 * p4.y;
        printTXY(t, x, y);
    }
    console.log("\n\n");
}

function spline(n, p1, p2, p3, p4) {
    let t, x, y;
    const delta = 1.0 / n;

    console.log("SPLINE:");
    console.log("p1: ", printPoint(p1));
    console.log("p2: ", printPoint(p2));
    console.log("p3: ", printPoint(p3));
    console.log("p4: ", printPoint(p4));
    console.log("\n");

    x = p1.x;
    y = p1.y;
    t = 0.0;
    for (let i = 0; i < n; i++) {
        t += delta;
        const t2 = t * t;
        const t3 = t2 * t;

        x = (((1 - t3) / 6) * p1.x) + (((3 * t3 - 6 * t2 + 4) / 6) * p2.x) + (((-3 * t3 + 3 * t2 + 3 * t + 1) / 6) * p3.x) + ((t3 / 6) * p4.x);
        y = (((1 - t3) / 6) * p1.y) + (((3 * t3 - 6 * t2 + 4) / 6) * p2.y) + (((-3 * t3 + 3 * t2 + 3 * t + 1) / 6) * p3.y) + ((t3 / 6) * p4.y);

        printTXY(t, x, y);
    }
    console.log("\n\n");
}

// Example usage
let n = 100;
let p1 = new Point(10, 20);
let p4 = new Point(100, 40);
let r2 = new Point(30, 30);
let r3 = new Point(20, 70);

hermite(n, p1, p4, r2, r3);
bezier(n, p1, p4, r2, r3);
spline(n, p1, p4, r2, r3);