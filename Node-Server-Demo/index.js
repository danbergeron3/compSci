const express = require('express');
const app = express();
const bodyParser = require('body-parser');
require('dotenv').config();

const host = '0.0.0.0'; // Or your specific IP address
const port = 3000; // Use any free por
// default route
app.get("/", (req, res) => {
    console.log("Get request to server: no target route");
    // sends back a json object
    res.status(200).json({message: "server pinged"});
});

app.put("/", (req, res) =>{
    console.log("Put request to server: no target route");
    res.status(200).json({message: "server pinged"});
})

app.patch("/", (req, res) => {
    console.log("Patch request to server: no target route");
    res.status(200).json({message: "server pinged"});
});

app.post("/", (req, res) => {
    console.log("Post request to server: no target route");
    res.status(200).json({message: "server pinged"});
});

app.delete("/", (req, res) => {
    console.log("Delete request to server: no target route");
    res.status(200).json({message: "server pinged"});
});


// allows json to be used in routes 
app.use(express.urlencoded({extended: true}));
app.use(express.json());

const apiRoute = require('./routes/api');
app.use('/api', apiRoute);

const databaseRouter = require('./routes/database');
app.use('/database', databaseRouter);

// listens to requests on specified ports
app.listen(port, () => {
    console.log("Listening on port: " + port);
});