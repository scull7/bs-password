let fromJsError = e => {
  let exn =
    switch (e |. Js.Exn.message) {
    | Some(message) => Password_error.EncryptionFailure(message)
    | None => Password_error.UknownFailure("bcrypt_unknown_failure")
    };
  Belt.Result.Error(exn);
};

let deriveKey = (input, finished) =>
  Bcrypt.genSalt(
    10,
    fun
    | Belt.Result.Error(e) => fromJsError(e) |> finished
    | Belt.Result.Ok(salt) =>
      Bcrypt.hash(
        input,
        `Salt(salt),
        fun
        | Belt.Result.Error(e) => fromJsError(e) |> finished
        | Belt.Result.Ok(key) => Belt.Result.Ok((salt, key)) |> finished,
      ),
  );

let verify = (key, input, finished) =>
  Bcrypt.compare(
    input,
    key,
    fun
    | Belt.Result.Error(e) => fromJsError(e) |> finished
    | Belt.Result.Ok(isMatch) => Belt.Result.Ok(isMatch) |> finished,
  );

let token = (length, finished) =>
  Bcrypt.genSalt(
    length,
    fun
    | Belt.Result.Error(e) => fromJsError(e) |> finished
    | Belt.Result.Ok(salt) => Belt.Result.Ok(salt) |> finished,
  );
