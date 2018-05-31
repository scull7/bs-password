[![Build Status](https://travis-ci.com/scull7/bs-password.svg?branch=master)](https://travis-ci.com/scull7/bs-password)
[![Coverage Status](https://coveralls.io/repos/github/scull7/bs-password/badge.svg?branch=master)](https://coveralls.io/github/scull7/bs-password?branch=master)

# bs-password

A password hashing libarary for ReasonML

## How do I install it?

Inside of a BuckleScript project:

```sh
yarn add bs-password
```

Then add `bs-password` to your `bs-dependencies` in `bsconfig.json`

```json
{
  "bs-dependencies": [ "bs-password" ]
}
```

## Usage

### Basic Callback based interface.

1. Derive a hash

```reason
let password = "This is my password";
let algorithm = Password.Algorithm.Bcrypt;

Password.deriveKey(algorithm, password, (result) => {
  switch (result) {
  | Belt.Result.Error(e) => raise(e)
  | Belt.Result.Ok((salt, hash)) => Js.log3("Salt and Key", salt, hash)
  };
});
```

2. Verify a hash against a password.

```reason
let password = "This is my passsword";
let algorithm = Password.Algorithm.Bcrypt;

Password.deriveKey(algorithm, password, (result) => {
  switch (result) {
  | Belt.Result.Error(e) => raise(e)
  | Belt.Result.Ok((_, hash)) =>
    Password.verify(algorithm, hash, password, (result2) => {
    switch (result) {
    | Belt.Result.Error(e) => raise(e)
    | Belt.Result.Ok(isValid) => Js.log2("isValid: ", isValid)
    }
    });
  };
});
```

3. Generate a random token.

```reason
let algorithm = Password.Algorithm.Bcrypt;
let length = 8;

Password.token(algorithm, length, (result) => {
  switch(result) {
  | Belt.Result.Error(e) => raise(e)
  | Belt.Result.Ok(token) => Js.log2("Token: ", token)
  };
});
```

### [Future][reason-future] based interface.

1. Derive a hash.

```reason
let password = "This is my password";
let algorithm = Password.Algorithm.Bcrypt;

Password.Future.deriveKey(algorithm, password)
|. Future.mapOk(((salt, hash)) => Js.log3("Salt and Key: ", salt, hash))
|. Future.mapError(raise);
```

2. Verify a hash against a password.

```reason
let password = "This is my password";
let algo = Password.Algorithm.Bcrypt;

Password.Future.deriveKey(algo, password)
|. Future.flatMapOk(((_, hash)) => Password.Future.verify(algo, hash, password))
|. Future.mapOk(isValid => Js.log2("Is Valid: ", isValid))
|. Future.mapError(raise)
```

3. Generate a random token.

```reason
let algo = Password.Algorithm.Bcrypt;

Password.Future.token(algo, 16)
|. Future.mapOk(token => Js.log2("Token: ", token))
|. Future.mapError(raise)
```

### Promise based interface.

1. Derive a hash.

```reason
let password = "This is my password";
let algorithm = Password.Algorithm.Bcrypt;

Password.Promise.deriveKey(algorithm, password)
|> Js.Promise.then_(result =>
  switch (result) {
  | Belt.Result.Error(e) => raise(e)
  | Belt.Result.Ok((salt, hash)) => Js.log3("Salt and key: ", salt, hash)
  }
  |> Js.Promise.resolve
)
```

2. Verify a hash against a password.

```reason
let password = "This is my password";
let algo = Password.Algorithm.Bcrypt;

Password.Promise.deriveKey(algo, password)
|> Js.Promise.then_(result =>
  switch (result) {
  | Belt.Result.Error(e) => raise(e)
  | Belt.Result.Ok((_, hash)) => Js.Promise.resolve(hash)
  }
)
|> Js.Promise.then_(hash => Password.Promise.verify(algo, hash, password))
|> Js.Promise.then_(isValid =>
  Js.log2("Does Match: ", isValid) |> Js.Promise.resolve
) 
```

3. Generate a random token.

```reason
let algo = Password.Algorithm.Bcrypt;

Password.Promise.token(algo, 31)
|> Js.Promise.then_(token => Js.log2("Token: ", token) |> Js.Promise.resolve)
```


[reason-future]: https://github.com/RationalJS/future
[Js.Promise]: https://bucklescript.github.io/bucklescript/api/Js.Promise.html
