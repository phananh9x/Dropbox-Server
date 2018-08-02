'use strict';
var express = require('express');
var router = express.Router();
var	userHandlers = require('../controllers/userController.js');
var	groupHandlers = require('../controllers/groupController.js');
 
/* GET groups listing. */
router.get('/getgroups', userHandlers.loginRequired, groupHandlers.get);
router.post('/addgroup', userHandlers.loginRequired, groupHandlers.create);
router.post('/deletegroup', userHandlers.loginRequired, groupHandlers.deleteGroup);
router.post('/getmembers', userHandlers.loginRequired, groupHandlers.getMembers);
router.post('/addmember', userHandlers.loginRequired, groupHandlers.addMember);
router.post('/deletemember', userHandlers.loginRequired, groupHandlers.deleteMember);

module.exports = router;