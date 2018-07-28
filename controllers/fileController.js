var mongoose = require('mongoose'),
  	Image = mongoose.model('File'),
  	UserLog = mongoose.model('UserLog');
var fs = require('fs');

exports.get = function(req, res, next) {
  	Image.findById(req.params.imageId, function (err, data) {
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

    fs.readFile(filepath, function(err, buf) {
        if(err) {
            console.log(err);
        }
        else {
            var buffer = buf.toString('base64');
		    var res={}
		    var splitedemail = req.email.split('.')[0];
		    var filename = req.file.filename;
		    var filepath = './public/uploads/'+splitedemail+'/'+req.file.filename;
		    var fileparent = req.filedata.fileparent;
		    var isfile = req.filedata.isfile;


		    if(fileparent)
		        filepath=fileparent+'/'+filename


		    var filedata={
		        'filename': filename,
		        'filepath':filepath,
		        'fileparent': fileparent,
		        'isfile': isfile,
		        'owner':req.email,
		        'sharedcount':0,
		        'starred' : false
		    };
		    console.log(filedata)

		    var newfile=new File();
		    newfile.filename = filename,
	        newfile.filepath = filepath,
	        newfile.fileparent = fileparent,
	        newfile.isfile = isfile,
	        newfile.owner = req.email,
	        newfile.sharedcount = 0,
	        newfile.starred = false


		    var log={
		        'filename':filename,
		        'filepath':filepath,
		        'isfile':isfile=='T'?"File":"Folder",
		        'action':'Upload File',
		        'actiontime': new Date()
		    };

		    fs.writeFile(filepath, new Buffer(req.buffer, 'base64'), function(err) {
		        if(err)
		            console.log(err);
		        else {
		            console.log('File created');

		            newfile.save(function (err) {

		                if (err) {
		                    console.log(err)
		                    res.code = "401";

		                }
		                else {

		                    UserLog.update({'user': req.email}, {$push: {filelog: log}}, function (err) {
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
    								return res.send({success: true, results: res});
		                        }

		                    });
		                }
		            });
		        }
		    });
        }
    });
};