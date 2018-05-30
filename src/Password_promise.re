let deriveKey = (algorithm, input) =>
  Js.Promise.make((~resolve, ~reject as _) =>
    Password_async.deriveKey(algorithm, input, x => resolve(. x))
  );

let verify = (algorithm, key, input) =>
  Js.Promise.make((~resolve, ~reject as _) =>
    Password_async.verify(algorithm, key, input, x => resolve(. x))
  );

let token = (algorithm, length) =>
  Js.Promise.make((~resolve, ~reject as _) =>
    Password_async.token(algorithm, length, x => resolve(. x))
  );
