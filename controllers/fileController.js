var mongoose = require('mongoose'),
  	Image = mongoose.model('File');

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
	var path = "file/uploads/";
  	var img = new Image(req.files[0]);
  	img.path = path + img.filename;
	console.log(img);
	img.save(function(err, data) {
    if (err) 
    	return res.status(400).send({
			success: false, 
			results: null,
			message: err
		});
    return res.send({success: true, results: data});
  });
};