var mongoose = require('mongoose'),
	config = require('../config'),
  User = mongoose.model('User'),
  File = mongoose.model('File'),
  Group = mongoose.model('Group'),
	UserLog = mongoose.model('UserLog');
var fs = require('fs');

exports.create = function(req, res) {
	var membercount = 0;
    var log = {
        'groupname': req.body.groupname,
        'action': 'Add Group',
        'actiontime': new Date()
    };

    var newgroup = new Group();
    newgroup.groupname = req.body.groupname;
    newgroup.membercount = membercount;
    newgroup.owner = req.user.user.email;
    newgroup.member=[];

    var groupdata = {};
    groupdata.groupname = req.body.groupname;
    groupdata.membercount = membercount;
    groupdata.owner = req.user.user.email;
    groupdata.members = [];

    Group.findOne({'groupname': req.body.groupname, 'owner': req.user.user.email}, function (err, group) {

        console.log("Group exists..")
        if (err) {
            throw err;
        }

        if (group) {
            res.code = "402";
            res.value = "Group name already exists!"
            callback(null, res);
        }

        else {

            newgroup.save(function (err) {

                if (err) {
                    return res.status(500).send({
			            success: false,
			            results: null,
			            message: err
			        });
                }
                else {
                    UserLog.update({'user': req.user.user.email}, {$push: {grouplog: log}}, function (err) {
                        if (err) {
                            throw err;
                            console.log("Error inserting last login....")
                            return res.status(500).send({
					            success: false,
					            results: null,
					            message: err
					        });
                        }
                        else {
                            console.log(groupdata);
                            let value = {"group": groupdata, "message": "Group created successfully!"}
						    return res.send({success: true, results: value, value});
                        }

                    });
                }
            });
        }
    });
};

exports.get = function(req, res) {
  	var groups = []
	Group.find({$or: [{'owner': req.user.user.email}, {'members.email': req.user.user.email}]}, function (err, groupsArr) {

	    if (err) {
	        throw err;
	    }

	    if (!groupsArr) {
	        return res.status(500).send({
	            success: false,
	            results: null,
	            message: err
	        });
	    }
	    else {
	        groups = groupsArr;
	        let value = {"groups": groups};
		    return res.send({success: true, results: value, value});
	    }

	});
}

exports.getMembers = function(req, res) {
	console.log("in file upload kafka")

    Group.findOne( {'groupname': req.body.groupname, 'owner': req.body.owner}, function (err, group) {

        if (err) {
            throw err;
        }

        if(!group){
            return res.status(500).send({
	            success: false,
	            results: null,
	            message: err
	        });
        }
        else {
            let value = {"members": group.members}
		    return res.send({success: true, results: value, value});
        }
    });
}

exports.deleteGroup = function(req, res) {
	var log={
        'groupname':req.body.groupname,
        'action':'Delete Group',
        'actiontime': new Date()
    };
    Group.remove({'groupname': req.body.groupname, 'owner': req.body.owner},function(err){
        if(err){
            throw err;
            return res.status(500).send({
	            success: false,
	            results: null,
	            message: err
	        });
        }
        else{

            UserLog.update({'user': req.body.owner}, {$push: {grouplog:log}}, function (err) {
                if (err) {
                    throw err;
                    return res.status(500).send({
			            success: false,
			            results: null,
			            message: err
			        });
                }
                else {
				    return res.send({success: true, results: 'Delete group success!!'});
                }

            });

        }

    });
}

exports.addMember = function(req, res) {
	console.log(req.body)
	var groupname = req.body.group.groupname;
    var count = req.body.group.membercount;
    var memberemail = req.body.member;
    var owner = req.body.group.owner;


    var log={
        'groupname':groupname,
        'action':'Add Member '+memberemail,
        'actiontime': new Date()
    };

    var memberdata = {}


    User.findOne( {'email': memberemail}, function (err, user) {

        console.log(user);
        if (err) {
            throw err;
        }

        if (!user) {
            return res.status(500).send({
	            success: false,
	            results: null,
	            message: 'User not available on dropbox!'
	        });
        }

        else {
            memberdata.firstname= user.firstname;
            memberdata.lastname=user.lastname;
            memberdata.email=memberemail;
            memberdata.group=groupname;

            Group.update({'groupname': groupname, 'owner': owner},
                {$set: {membercount: count+1}, $push: {'members': memberdata}},function(err){
                    if(err){
                        throw err;
                        return res.status(500).send({
				            success: false,
				            results: null,
				            message: 'Error adding member!'
				        });
                    }
                    else{
                        UserLog.update({'user': owner}, {$push: {grouplog:log}}, function (err) {
                            if (err) {
                                throw err;
                                return res.status(500).send({
						            success: false,
						            results: null,
						            message: 'Error updating member!'
						        });
                            }
                            else {
                                let value = {"member":memberdata, message: "Member added Successfully!"}
				    			return res.send({success: true, results: value, value});
	                        }
                        });
                    }
                });
        }
    })
}
exports.deleteMember = function(req, res) {
	 var log={
        'groupname':req.body.groupname,
        'action':'Delete Member '+req.body.member,
        'actiontime': new Date()
    };

    Group.update({'groupname': req.body.groupname, 'owner': req.body.owner}, {$pull: {'members':{'email': req.body.member}}}, { multi: true }, function (err) {
        if (err) {
            throw err;
            return res.status(500).send({
	            success: false,
	            results: null,
	            message: 'Error deleting member!'
	        });
        }
        else {

            UserLog.update({'user': req.body.owner}, {$push: {grouplog: log}}, function (err) {
                if (err) {
                    throw err;
                    return res.status(500).send({
			            success: false,
			            results: null,
			            message: 'Error deleting member!'
			        });

                }
                else {
                    let value = "Member deleted Successfully!"
    				return res.send({success: true, results: value, value});

                }

            });

        }

    });
}