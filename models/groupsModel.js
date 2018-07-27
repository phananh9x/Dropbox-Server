'use strict';
var mongoose = require('mongoose'),
  Schema = mongoose.Schema;


var GroupSchema   = new Schema({
    groupname: String,
    membercount: Number,
    owner: String,
    members: Array
});
mongoose.model('Group', GroupSchema);
