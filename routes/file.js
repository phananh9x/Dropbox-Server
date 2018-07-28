var express = require('express');
var	userHandlers = require('../controllers/userController.js');
var	fileHandlers = require('../controllers/fileController.js');
var multer  = require('multer');

var storage = multer.diskStorage({
    destination: (req, file, cb) => {
      	cb(null, 'public/file/uploads')
    },
    filename: (req, file, cb) => {
	    cb(null, file.fieldname + '-' + Date.now() + '-' + file.originalname)
    }
});
var upload = multer({storage: storage});
var router = express.Router();

router.get('/:fileId',userHandlers.loginRequired, fileHandlers.get);
router.post('/upload', upload.any(),userHandlers.loginRequired, fileHandlers.create);

module.exports = router;
