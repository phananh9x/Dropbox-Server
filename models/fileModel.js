'use strict';

var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

/**
 * Image Schema
 */
var ImageSchema = new Schema({
  fieldname: {
    type: String,
  },
  originalname: {
    type: String,
  },
  encoding: {
    type: String,
  },
  mimeptype: {
    type: String,
  },
  destination: {
    type: String,
  },
  filename: String,
  path: {
    type: String,
  },
  size: {
    type: Number,
  },
  created_at: {
    type: Date,
  },
  updated_at: {
    type: Date,
  }
});

mongoose.model('File', ImageSchema);