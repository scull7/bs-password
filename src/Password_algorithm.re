type t =
  | Bcrypt
  | Scrypt;

let fromString =
  fun
  | "bcrypt" => Bcrypt
  | "scrypt" => Scrypt
  | _ => failwith("invalid_algorithm");

let toString =
  fun
  | Bcrypt => "bcrypt"
  | Scrypt => "scrypt";
