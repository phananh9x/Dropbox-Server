'use strict';

var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

/**
 * File Schema
 */
var FileSchema = new Schema({
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
  filepath: {
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
  },
  fileparent: String,
  isfile: String,
  owner: String,
  sharedcount: Number,
  sharedlist : Array,
  starred : Boolean
});

mongoose.model('File', FileSchema);