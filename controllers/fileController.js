var mongoose = require('mongoose'),
  	File = mongoose.model('File'),
  	UserLog = mongoose.model('UserLog');
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
	var filepath = './public/uploads/'+req.file.filename;
    fs.readFile(filepath,'base64', function(err, buffer) {
        if(err) {
            console.log("err", err);
        }
        else {
		    var splitedemail = req.user.user.email.split('.')[0];
		    var filename = req.file.filename;
		    var filepath = './public/uploads/'+splitedemail+'/'+req.file.filename;
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

		    fs.writeFile(filepath, new Buffer(buffer, 'base64'), function(err) {
		        if(err)
		            console.log("err", err);
		        else {
		            console.log('File created');

		            newfile.save(function (err) {

		                if (err) {
		                    console.log(err)
		                    return res.status(400).send({
								success: false, 
								results: null,
								message: err
							});
		                }
		                else {

		                    UserLog.update({'user': req.user.user.email}, {$push: {filelog: log}}, function (err) {
		                        if (err) {
		                            throw err;
		                            console.log("Error inserting last login....")
		                            return res.status(400).send({
										success: false, 
										results: null,
										message: err
									});
		                        }
		                        else {
		                            res.code = "200";
		                            res.value = {"filedata": filedata};
		                            console.log(filedata)
    								return res.send({success: true, results: filedata, value : filedata});
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
	console.log(req.body)

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
                console.log(filepath)
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
                            console.log("Success")
                            res.value = "File Deleted Successfully!";
							return res.send({success: true, results: "File Deleted Successfully!"});

                        }

                    });

                }

            });

        }

        else{
			console.log(owner);
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
	console.log(req.body)
	var splitedemail = req.user.user.email.split('.')[0];

    var filename = req.body.foldername;

    var filepath = './public/uploads/'+splitedemail+'/'+filename;
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

    var dir = './public/uploads/'+splitedemail+'/'+filename;

    if (!fs.existsSync(dir)){

        fs.mkdirSync(dir);
    }

    newfolder.save( function (err) {

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
                    var value = {"folderdata":folderdata, "message": "Folder created successfully!"};
					return res.send({success: true, results: value, value : value});

                }

            });
        }

    });
};


exports.makeStart = function(req, res, next) {
	console.log(req.body)
	
};

exports.getFiles = function(req, res, next) {
	File.findOne({_id: req.params.folderId}, function (err, folder) {
		console.log('folder', folder)
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
	        	console.log(filesArr)
	            files=filesArr;
	            let value = {"files": files};
				return res.send({success: true, results: value, value});
	        }

	    });
	});
	
};
