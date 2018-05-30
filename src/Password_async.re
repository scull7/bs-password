let deriveKey = (algorithm, input, finished) =>
  switch (algorithm) {
  | Password_algorithm.Bcrypt => Password_bcrypt.deriveKey(input, finished)
  | Password_algorithm.Scrypt => Password_scrypt.deriveKey(input, finished)
  };

let verify = (algorithm, key, input, finished) =>
  switch (algorithm) {
  | Password_algorithm.Bcrypt => Password_bcrypt.verify(key, input, finished)
  | Password_algorithm.Scrypt => Password_scrypt.verify(key, input, finished)
  };

let token = (algorithm, length, finished) =>
  switch (algorithm) {
  | Password_algorithm.Bcrypt => Password_bcrypt.token(length, finished)
  | Password_algorithm.Scrypt => Password_scrypt.token(length, finished)
  };
