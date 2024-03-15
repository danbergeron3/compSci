const express = require("express");
const router = express.Router();
require("dotenv").config();
const key = process.env.PERENNIALAPI_KEY_RAW;

router 
    .route("/")
    .get( async (req, res) => {
        try {
            const response = await fetch(`https://perenual.com/api/species-list?key=${key}&page=1`, 
            { method: 'GET' });
            const data = await response.json();
            res.status(200).json({data});
        } catch (err){
            res.status(500).json({message: err});
        }
     })
    .post((req, res) => {
        res.status(200).json({message: "Post pinged"});
    })
    .put((req, res) => {
        res.status(200).json({message: "Put pinged"});
    })
    .delete((req, res) => {
        res.status(200).json({message: "delete pinged"});
    })
    .patch((req, res) => {
        res.status(200).json({message: "Patch pingend"}); 
    })

    module.exports = router;