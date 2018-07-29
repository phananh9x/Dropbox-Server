var express = require('express');
var	userHandlers = require('../controllers/userController.js');
var	fileHandlers = require('../controllers/fileController.js');
var multer  = require('multer');

var storage = multer.diskStorage({
    destination: function (req, file, cb) {

        cb(null, './public/uploads/')
    },
    filename: function (req, file, cb) {
        // cb(null, file.fieldname + '-' + Date.now() + '.jpeg')
        cb(null, file.originalname)


    }
});

var upload = multer({storage:storage});
var router = express.Router();

router.get('/:fileId',userHandlers.loginRequired, fileHandlers.get);
router.post('/upload', upload.single('file'),userHandlers.loginRequired, fileHandlers.create);
router.post('/delete',userHandlers.loginRequired, fileHandlers.delete);
router.post('/makefolder',userHandlers.loginRequired, fileHandlers.makefolder);
router.post('/:folderId',userHandlers.loginRequired, fileHandlers.getFiles);

module.exports = router;
