
const mongoose = require("mongoose")

const PlantModel = new mongoose.Schema({
    id: {
        type: Number
    },
    page: {
        type: Number
    },
    binomial_name: {
        type: String,
        required: true,
    },
    name: {
        type: String,
        required: true,
    },
    daily_watering: {
        type: String,
        required: true,
        min: 0,
    },
    zone: {
        hardy:{
            type: Number,
            min: 0
        },
        season: {
            type: String
        },
    },
    light:{
        type: [String],
        required: true,
    },
    care_level:{ 
        type: String
    },
    image_urls:[String],
    description: String,
    watering_description: String,
    sunlight_description: String,
    pruning_description: String,
    hardiness_url: String
});

// Exports the schema to other files and set are collection to Plants
module.exports = mongoose.model("PlantModel", PlantModel);


 