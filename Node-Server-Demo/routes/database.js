const express = require("express");
const router = express.Router();
const mongoose = require("mongoose");
require("dotenv").config();
const PlantModel = require("../models/plant-schema");
const uri = process.env.PLANTDB_URL;
const plantAPI = process.env.PERENNIALAPI_KEY;
const key = process.env.PERENNIALAPI_KEY_RAW;
const clientOptions = { serverApi: { version: '1', strict: true, deprecationErrors: true } };


router.get("/", async (req, res) => {
    const id = req.query.id;
    try {
        await mongoose.connect(uri, clientOptions);
    } catch(error) {
        console.error("Error connecting to database: ", error);
        res.status(500).json({message: "Failed to retrieve document"});
    }
    
    console.log("You are in plantCatalog.js");
    try {
        // this is a crud operation
        const data = await PlantModel.find({ id: 1 });
        if (!data || data.length === 0) {
            res.status(500).json({data});
        } else {
            console.log('Query succeeded:', data);
            console.log("Sending Json Data");
            res.status(200).json({data});
        }
        
    } catch(error) {
        console.error("Error fetching data:", error);
        res.status(500).json({message: "Failed to retrieve documents"});
    } finally {
        await mongoose.disconnect();
    }
});

router 
    .route("/")
    .post((req, res) => {
        res.status(200).json({message: "Need to define schema"});
    })
    .put((req, res) => {
        res.status(200).json({message: "Need to define schema"});
    })
    .delete((req, res) => {
        res.status(200).json({message: "Delete Pinged "});
    })
    .patch((req, res) => {
        res.status(200).json({message: "Need to define Schema"}); 
    });

module.exports = router;
