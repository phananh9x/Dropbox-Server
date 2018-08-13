var mongoose = require('mongoose'),
  	File = mongoose.model('File'),
    UserLog = mongoose.model('UserLog'),
  	Group = mongoose.model('Group');
var fs = require('fs');

exports.get = function(req, res, next) {
  	File.findById(req.params.imageId, function (err, data) {
	  if (err) 
		return res.status(400).send({
			success: false, 
			results: null,
			message: err
		});
	  return res.send({success: true, results: data});
	});
};

exports.create = function(req, res, next) {
	var filepath = './public/uploads/'+req.file.filename; // đường dẫn ủa file tải lên
    fs.readFile(filepath,'base64', function(err, buffer) { // đọc file từ đường dẫn trả về buffer
        if(err) {
            console.log("err", err);
        }
        else {
            fs.unlinkSync('./public/uploads/'+req.file.filename);
		    var splitedemail = req.user.user.email.split('.')[0];
		    var filename = req.file.filename;
		    var filepath = './public/uploads/'+splitedemail+'/'+req.file.filename; // tạo đường dẫn mới của file lưu theo từng user khác nhau
		    var fileparent = req.body.fileparent;
		    var isfile = req.body.isfile;
		    if(fileparent)
		        filepath=fileparent+'/'+filename
		    var filedata={
		        'filename': filename,
		        'filepath':filepath,
		        'fileparent': fileparent,
		        'isfile': isfile,
		        'owner':req.user.user.email,
		        'sharedcount':0,
		        'starred' : false
		    };
		    var newfile=new File();
		    newfile.filename = filename,
	        newfile.filepath = filepath,
	        newfile.fileparent = fileparent,
	        newfile.isfile = isfile,
	        newfile.owner = req.user.user.email,
	        newfile.sharedcount = 0,
	        newfile.starred = false
		    var log={
		        'filename':filename,
		        'filepath':filepath,
		        'isfile':isfile=='T'?"File":"Folder",
		        'action':'Upload File',
		        'actiontime': new Date()
		    };
		    fs.writeFile(filepath, new Buffer(buffer, 'base64'), function(err) { // ghi file vào đường dẫn mới
		        if(err)
		            console.log("err", err);
		        else {

		            newfile.save(function (err) { // lưu  thông tin file vào database

		                if (err) {
		                    console.log(err)
		                    return res.status(400).send({
								success: false, 
								results: null,
								message: err
							});
		                }
		                else {
		                    UserLog.update({'user': req.user.user.email}, {$push: {filelog: log}}, function (err) { // lưu thông tin user log 
		                        if (err) {
		                            throw err;
		                            return res.status(400).send({
										success: false, 
										results: null,
										message: err
									});
		                        }
		                        else {
		                            res.code = "200";
		                            res.value = {"filedata": filedata};
    								return res.send({success: true, results: filedata, value : filedata});// trả kết quả về cho client
		                        }

		                    });
		                }
		            });
		        }
		    });
        }
    });
};


exports.delete = function(req, res, next) {

	var filename = req.body.filename;
    var isfile = req.body.isfile;
    var filepath= req.body.filepath;
    var count = req.body.sharedcount;
    var owner = req.body.owner;
    var email=req.user.user.email;

    var log={
        'filename':filename,
        'filepath':filepath,
        'isfile':isfile=='T'?"File":"Folder",
        'action':'Delete File',
        'actiontime': new Date()
    };



    File.findOne({'filepath':filepath, 'owner':email}, function(err, file){
        if(err){
            throw err;
            return res.status(400).send({
				success: false, 
				results: null,
				message: 'Error deleting file!'
			});
        }

        if(file){

            if (isfile == 'F') {
                try {

                    rimraf.sync(filepath)
                }
                catch (err) {
                    return res.status(400).send({
						success: false, 
						results: null,
						message: 'Folder is not empty!'
					});
                }

            }
            else {
                fs.unlinkSync(filepath);
            }

            file.remove(function(err){
                if(err){
                    throw err;
                    return res.status(400).send({
						success: false, 
						results: null,
						message: "Error deleting file!"
					});
                }
                else{

                    UserLog.update({'user': email}, {$push: {filelog:log}}, function (err) {
                        if (err) {
                            throw err;
                        }
                        else {
                            res.value = "File Deleted Successfully!";
							return res.send({success: true, results: "File Deleted Successfully!"});

                        }

                    });

                }

            });

        }

        else{
            File.update({'filepath':filepath}, { $set:{sharedcount:count-1}, $pull: {sharedlist: email}}, function(err){

                if(err){
                    throw err;
                    return res.status(400).send({
						success: false, 
						results: null,
						message: "Error deleting file!"
					});
                }
                else{
                    UserLog.update({'user': email}, {$push: {filelog:log}}, function (err) {
                        if (err) {
                            throw err;
                            return res.status(400).send({
								success: false, 
								results: null,
								message: "Error deleting file!"
							});
                        }
                        else {
							return res.send({success: true, results: "File Deleted Successfully!"});
                        }

                    });

                }

            });
        }
    }); 
};


exports.makefolder = function(req, res, next) {
	var splitedemail = req.user.user.email.split('.')[0];

    var filename = req.body.foldername;

    var filepath = !req.body.fileparent ? './public/uploads/'+splitedemail+'/'+filename : req.body.fileparent+"/" + filename;
    var fileparent = req.body.fileparent;
    var isfile = req.body.isfile;


    var folderdata={
        'filename': filename,
        'filepath':filepath,
        'fileparent': fileparent,
        'isfile': isfile,
        'owner':req.user.user.email,
        'sharedcount':0,
        'starred' : false
    };

    var newfolder=new File();
    newfolder.filename = filename,
        newfolder.filepath = filepath,
        newfolder.fileparent = fileparent,
        newfolder.isfile = isfile,
        newfolder.owner = req.user.user.email,
        newfolder.sharedcount = 0

    var log={
        'filename':filename,
        'filepath':filepath,
        'isfile':isfile=='T'?"File":"Folder",
        'action':'Create Folder',
        'actiontime': new Date()
    };

    // var dir = './public/uploads/'+splitedemail+'/'+filename;
    var dir = filepath;

    if (!fs.existsSync(dir)){

        fs.mkdirSync(dir);
    }

    newfolder.save( function (err, data) {

        if(err){
        	return res.status(400).send({
				success: false, 
				results: null,
				message: "Error making folder!"
			});
        }
        else {

            UserLog.update({'user': req.user.user.email}, {$push: {filelog:log}}, function (err) {
                if (err) {
                    throw err;
                    return res.status(400).send({
						success: false, 
						results: null,
						message: "Error making folder!"
					});
                }
                else {
                    var value = {"folderdata":data, "message": "Folder created successfully!"};
					return res.send({success: true, results: value, value : value});

                }

            });
        }

    });
};


exports.makeStar = function(req, res, next) {
	// console.log(req.body)
	// var filepath = msg.file.filepath;
    // var starred = msg.file.starred;


   //  File.update( {'filepath' : filepath}, {$set:{'starred':starred}} , function (err) {

   //      if (err) {
   //          throw err;
   //          return res.status(400).send({
			// 	success: false, 
			// 	results: null,
			// 	message: err
			// });
   //      }

   //      else {

   //          res.code = "200";
   //          res.value = {'starred':starred}
   //          callback(null, res);
   //      }

   //  });
	
};

exports.getFiles = function(req, res, next) {
	File.findOne({_id: req.params.folderId}, function (err, folder) {
		var email=req.user.user.email;
	    var filepath=folder.filepath;
	    var files=[];

	    File.find( {'fileparent' : filepath} , function (err, filesArr) {

	        if (err) {
	            throw err;
	        }

	        if(!filesArr){
	            return res.status(400).send({
					success: false, 
					results: null,
					message: "File not found!"
				});
	        }
	        else {
	            files=filesArr;
	            let value = {"files": files};
                value.filepath = filepath;
				return res.send({success: true, results: value, value});
	        }

	    });
	});
	
};

exports.shareFile = function(req, res, next) {
    var userEmail=req.user.user.email;
    var shareEmail= req.body.shareEmail;

    var file=req.body.filedata;
    var count = file.sharedcount;
    var filename = file.filename;
    var filepath = file.filepath;
    var fileparent = file.fileparent;
    var isfile = file.isfile;

    var log={
        'filename':filename,
        'filepath':filepath,
        'isfile':isfile=='T'?"File":"Folder",
        'action':'Share File',
        'actiontime': new Date()
    };


    File.update({'filepath':filepath}, { $set:{sharedcount:count+1}, $push: {sharedlist: shareEmail}}, function(err){

        if(err){
            throw err;
            let value = {"shareEmail":shareEmail}
            return res.status(400).send({
                success: false, 
                results: value,
                value
            });

        }
        else{

            UserLog.update({'user': userEmail}, {$push: {filelog:log}}, function (err) {
                if (err) {
                    throw err;
                    return res.status(400).send({
                        success: false, 
                        results: value,
                        message: "Error inserting last login...."
                    });
                }
                else {
                    return res.send({success: true, results: "Success"});

                }

            });
        }
    });

}

exports.shareFileInGroup = function(req, res, next) {
	var userEmail=req.user.user.email;
    var group= req.body.group;

    var file=req.body.file;
    var count = file.sharedcount;
    var filename = file.filename;
    var filepath = file.filepath;
    var fileparent = file.fileparent;
    var isfile = file.isfile;

    var log={
        'filename':filename,
        'filepath':filepath,
        'isfile':isfile=='T'?"File":"Folder",
        'action':'Share File with group '+group,
        'actiontime': new Date()
    };


    Group.findOne( {'groupname': group, 'owner': userEmail}, function (err, groupData) {

        if (err) {
            console.log(err)
            throw err;
        }

        if(!group){
        	return res.status(400).send({
				success: false, 
				results: null,
				message: "Group not found!"
			});
        }
        else {
            var membersArr = groupData.members;

            for(var i=0; i<membersArr.length; i++){

                count+=1;
                File.update({'filepath':filepath}, { $set:{sharedcount:count+1}, $push: {sharedlist: membersArr[0].email}}, function(err){

                    if(err){
                        throw err;
                        let value = {"group":group}
						return res.send({success: true, results: value, value});
                    }

                });
            }

            UserLog.update({'user': userEmail}, {$push: {filelog:log}}, function (err) {
                if (err) {
                    throw err;
                    return res.status(400).send({
						success: false, 
						results: null,
						message: "UserLog not found!"
					});
                }
                else {
                    let value = {"sharedcount":count}
					return res.send({success: true, results: value, value});
                }
            });
        }
    });
}
