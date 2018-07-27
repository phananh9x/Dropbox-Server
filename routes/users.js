'use strict';
var express = require('express');
var router = express.Router();
var	userHandlers = require('../controllers/userController.js');
 
/* GET users listing. */
router.get('/info', userHandlers.loginRequired, userHandlers.get);
router.post('/register', userHandlers.register);
router.post('/sign_in', userHandlers.sign_in);
router.post('/update', userHandlers.loginRequired, userHandlers.update);
router.post('/:userId/delete', userHandlers.loginRequired, userHandlers.delete);

module.exports = router;