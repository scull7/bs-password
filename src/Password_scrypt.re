let notImplemented =
  Belt.Result.Error(Password_error.NotImplemented("scrypt"));

let deriveKey = (_, finished) => finished(notImplemented);

let verify = (_, _, finished) => finished(notImplemented);

let token = (_, finished) => finished(notImplemented);
