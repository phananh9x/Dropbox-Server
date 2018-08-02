var mongoose = require('mongoose'),
	config = require('../config'),
	jwt = require('jsonwebtoken'),
	bcrypt = require('bcrypt'),
  User = mongoose.model('User'),
  File = mongoose.model('File'),
	UserLog = mongoose.model('UserLog');
var fs = require('fs');

exports.register = function(req, res) {
  if (!req.body.image) {
    if (req.body.gender == "true") {
      req.body.image = config.avatarDefaultMale;
    }else {
      req.body.image = config.avatarDefaultFeMale;
    }
  }
  var newUser = new User(req.body);
  var userLog = new UserLog();
  userLog.user = req.body.email;
  newUser.hash_password = bcrypt.hashSync(req.body.password, 10);
  newUser.save(function(err, user) {
    if (err)
      return res.status(500).send({
        success: false,
        results: null,
        message: err
      });
    user.hash_password = undefined;
    userLog.save(function(err) {
      if (err) {
          throw err;
          return res.status(500).send({
                success: false,
                results: null,
                message: err
              });
      }
      else {
          var splitemail = req.body.email.split('.')[0];
          var dir = './public/uploads/' + splitemail;
          if (!fs.existsSync(dir)) {
              fs.mkdirSync(dir);
          }
          return res.send({success: true, results: user});
      }
  });
  });
};

exports.get = function(req, res) {
  var user={}
  var email = req.user.user.email ;
  var userdetails={
      firstname: '',
      lastname: '',
      email: '',
      contactno: '',
      interests:'',
      lastlogin:'',
      files :[],
      filelog:[],
      grouplog:[]

  }
  User.findOne({email: email }, function(err, user) {
    if (err) 
      return res.status(400).send({
        success: false, 
        results: null,
        message: "Failed to get user details"
      });
    File.find( {$or: [ {'owner': email, 'fileparent':''}, {'sharedlist': email}]} , function (err, filesArr) {
      if (err) {
          throw err;
          return res.status(400).send({
            success: false, 
            results: null,
            message: "Failed to get user details"
          });
      }
      UserLog.findOne({'user': email}, function (err, log) {
        if (err) {
            throw err;
            return res.status(400).send({
              success: false, 
              results: null,
              message: "Failed to get user details"
            });
        }

        if (!user) {
            return res.status(400).send({
              success: false, 
              results: null,
              message: "Failed to get user details"
            });
        }
        userdetails.firstname = user.firstname;
        userdetails.lastname = user.lastname;
        userdetails.email = user.email;
        userdetails.contactno = user.contactno;
        userdetails.interests = user.interests;
        userdetails.lastlogin = user.lastlogintime;
        userdetails.filelog = log.filelog;
        userdetails.grouplog = log.grouplog;
        userdetails.files = filesArr;
        return res.send({success: true, results: userdetails});
      });
    });
  });
};

exports.sign_in = function(req, res) {
  User.findOne({
    email: req.body.email
  }, function(err, user) {
    if (err)
      return res.status(500).send({
        success: false,
        results: null,
        message: err
      });
    if (!user || !user.comparePassword(req.body.password)) {
      return res.status(500).send({
        success: false,
        results: null,
        message: 'Authentication failed. Invalid user or password.'
      });
    }
    User.update({'email': req.body.email},{lastlogintime: new Date()}, function (err) {
      if (err) {
          throw err;
          console.log("Error inserting last login....")
          return res.status(500).send({
            success: false,
            results: null,
            message: 'Error inserting last login....'
          });
      }
      else {
        console.log("last login inserted....")
        return res.send({success: true, results: {
          token: jwt.sign({ user },
          config.secret) ,
          fullName:user.fullName,
          _id: user._id,
          email: user.email,
          phone: user.phone,
          address: user.address,
          gender: user.gender,
          birthday: user.birthday,
          image: user.image}});
        }
  });
    
  });
};

exports.update = function(req, res) {
  User.findOneAndUpdate({_id : req.user.user._id }, req.body, {new: true}, function (err, data) {
    if (err)
      return res.status(400).send({
        success: false,
        results: null,
        message: err
      });
    return res.send({success: true, results: data});
  });
};


exports.delete = function(req, res) {
  User.findByIdAndRemove({_id : req.params.userId}, function (err, data) {
    if (err)
      return res.status(400).send({
        success: false,
        results: null,
        message: err
      });
    return res.send({success: true, results: data});
  });
};



exports.loginRequired = function(req, res, next) {
  if (req.user) {
    next();
  } else {
    return res.status(500).send({
      success: false,
      results: null,
      message: 'Unauthorized user!'
    });
  }
};
