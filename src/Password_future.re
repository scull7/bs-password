let deriveKey = (algorithm, input) =>
  Future.make(resolve =>
    Password_async.deriveKey(algorithm, input, x => resolve(x))
  );

let verify = (algorithm, key, input) =>
  Future.make(resolve =>
    Password_async.verify(algorithm, key, input, x => resolve(x))
  );

let token = (algorithm, length) =>
  Future.make(resolve =>
    Password_async.token(algorithm, length, x => resolve(x))
  );
