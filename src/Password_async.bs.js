// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Password_bcrypt = require("./Password_bcrypt.bs.js");
var Password_scrypt = require("./Password_scrypt.bs.js");

function deriveKey(algorithm, input, finished) {
  if (algorithm) {
    return Password_scrypt.deriveKey(input, finished);
  } else {
    return Password_bcrypt.deriveKey(input, finished);
  }
}

function verify(algorithm, key, input, finished) {
  if (algorithm) {
    return Password_scrypt.verify(key, input, finished);
  } else {
    return Password_bcrypt.verify(key, input, finished);
  }
}

function token(algorithm, length, finished) {
  if (algorithm) {
    return Password_scrypt.token(length, finished);
  } else {
    return Password_bcrypt.token(length, finished);
  }
}

exports.deriveKey = deriveKey;
exports.verify = verify;
exports.token = token;
/* Password_bcrypt Not a pure module */
