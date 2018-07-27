'use strict';

var mongoose = require('mongoose'),
  bcrypt = require('bcrypt'),
  Schema = mongoose.Schema;

/**
 * User Schema
 */
var UserSchema = new Schema({
  fullName: {
    type: String,
    trim: true,
    required: true
  },
  image: {
    type: String
  },
  email: {
    type: String,
    unique: true,
    lowercase: true,
    trim: true,
    required: true
  },
  hash_password: {
    type: String
  },
  gender: Boolean,
  birthday: {
    type: Date
  },
  phone: {
    type: String  
  },
  address: {
    type: String
  },
  created: {
    type: Date,
    default: Date.now
  },
  contactno: String,
  interests: String,
  lastlogintime: Date
});

UserSchema.methods.comparePassword = function(password) {
  return bcrypt.compareSync(password, this.hash_password);
};


mongoose.model('User', UserSchema);