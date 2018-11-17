open Jest;

let failTest = (finished, e) => Js.String.make(e) |> fail |> finished;

describe("Bcrypt", () => {
  testAsync("derive and verify key - PASS", finished => {
    let input = "this is a test";
    let algo = Password.Algorithm.Bcrypt;

    Password.deriveKey(algo, input, result =>
      switch (result) {
      | Belt.Result.Error(e) => failTest(finished, e)
      | Belt.Result.Ok((_, key)) =>
        Password.verify(
          algo,
          key,
          input,
          fun
          | Belt.Result.Error(e) => failTest(finished, e)
          | Belt.Result.Ok(valid) =>
            Expect.expect(valid) |> Expect.toBe(true) |> finished,
        )
      }
    );
  });

  testAsync("derive and verify key - FAIL", finished => {
    let input = "this is a failing test";
    let bad = "this is not a failing test";
    let algo = Password.Algorithm.Bcrypt;

    Password.deriveKey(algo, input, result =>
      switch (result) {
      | Belt.Result.Error(e) => failTest(finished, e)
      | Belt.Result.Ok((_, key)) =>
        Password.verify(
          algo,
          key,
          bad,
          fun
          | Belt.Result.Error(e) => failTest(finished, e)
          | Belt.Result.Ok(valid) =>
            Expect.expect(valid) |> Expect.toBe(false) |> finished,
        )
      }
    );
  });

  testAsync("Generate a token of a given length", finished => {
    let algo = Password.Algorithm.Bcrypt;
    let re = [%re "/^\\$2a\\$08\\$/"];

    Password.token(algo, 8, result =>
      switch (result) {
      | Belt.Result.Error(e) => failTest(finished, e)
      | Belt.Result.Ok(token) =>
        Expect.expect(token) |> Expect.toMatchRe(re) |> finished
      }
    );
  });
});

describe("Bcrypt - Future", () => {
  testAsync("Derive and verify a key - PASS", finished => {
    let algo = Password.Algorithm.Bcrypt;
    let input = "The future is now!";

    Password.Future.deriveKey(algo, input)
    |. Future.flatMapOk(((_, key)) =>
         Password.Future.verify(algo, key, input)
       )
    |. Future.mapOk(valid => Expect.expect(valid) |> Expect.toBe(true))
    |. Future.mapOk(finished)
    |. Future.mapError(failTest(finished))
    |. ignore;
  });

  testAsync("Derive and verify a key - PASS", finished => {
    let algo = Password.Algorithm.Bcrypt;
    let input = "The future is now!";
    let bad = "The future is the past";

    Password.Future.deriveKey(algo, input)
    |. Future.flatMapOk(((_, key)) =>
         Password.Future.verify(algo, key, bad)
       )
    |. Future.mapOk(valid => Expect.expect(valid) |> Expect.toBe(false))
    |. Future.mapOk(finished)
    |. Future.mapError(failTest(finished))
    |. ignore;
  });

  testAsync("Generate a token of a given length", finish => {
    let algo = Password.Algorithm.Bcrypt;
    let re = [%re "/^\\$2a\\$16\\$/"];
    Password.Future.token(algo, 16)
    |. Future.mapOk(token => Expect.expect(token) |> Expect.toMatchRe(re))
    |. Future.mapOk(x => finish(x))
    |. Future.mapError(failTest(finish))
    |. ignore;
  });
});

describe("Bcrypt - Promise", () => {
  let algo = Password.Algorithm.Bcrypt;
  let input = "The future is now!";

  testPromise("Derive and verify a key - PASS", () =>
    Password.Promise.deriveKey(algo, input)
    |> Js.Promise.then_(result =>
         switch (result) {
         | Belt.Result.Error(e) => Belt.Result.Error(e) |> Js.Promise.resolve
         | Belt.Result.Ok((_, key)) =>
           Password.Promise.verify(algo, key, input)
         }
       )
    |> Js.Promise.then_(result =>
         (
           switch (result) {
           | Belt.Result.Error(e) => Js.String.make(e) |> fail
           | Belt.Result.Ok(v) => Expect.expect(v) |> Expect.toBe(true)
           }
         )
         |> Js.Promise.resolve
       )
  );

  testPromise("Derive and verify a key - FAIL", () => {
    let bad = "I promise this works.";

    Password.Promise.deriveKey(algo, input)
    |> Js.Promise.then_(result =>
         switch (result) {
         | Belt.Result.Error(e) => Belt.Result.Error(e) |> Js.Promise.resolve
         | Belt.Result.Ok((_, key)) =>
           Password.Promise.verify(algo, key, bad)
         }
       )
    |> Js.Promise.then_(result =>
         (
           switch (result) {
           | Belt.Result.Error(e) => Js.String.make(e) |> fail
           | Belt.Result.Ok(v) => Expect.expect(v) |> Expect.toBe(false)
           }
         )
         |> Js.Promise.resolve
       );
  });

  testPromise("Generate a token of a given length", () => {
    let re = [%re "/^\\$2a\\$31\\$/"];

    Password.Promise.token(algo, 42)
    |> Js.Promise.then_(result =>
         (
           switch (result) {
           | Belt.Result.Error(e) => Js.String.make(e) |> fail
           | Belt.Result.Ok(v) => Expect.expect(v) |> Expect.toMatchRe(re)
           }
         )
         |> Js.Promise.resolve
       );
  });
});
