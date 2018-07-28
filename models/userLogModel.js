'use strict';
var mongoose = require('mongoose'),
  Schema = mongoose.Schema;

/**
 * User Log Schema
 */
var UserLogSchema = new Schema({
  user: String,
  filelog:Array,
  grouplog:Array
});

mongoose.model('UserLog', UserLogSchema);