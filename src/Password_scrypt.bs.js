// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Password_error = require("./Password_error.bs.js");

var notImplemented = /* Error */Block.__(1, [[
      Password_error.NotImplemented,
      "scrypt"
    ]]);

function deriveKey(_, finished) {
  return Curry._1(finished, notImplemented);
}

function verify(_, _$1, finished) {
  return Curry._1(finished, notImplemented);
}

function token(_, finished) {
  return Curry._1(finished, notImplemented);
}

exports.notImplemented = notImplemented;
exports.deriveKey = deriveKey;
exports.verify = verify;
exports.token = token;
/* No side effect */
