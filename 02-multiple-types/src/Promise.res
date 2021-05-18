type t<+'a> = Js.Promise.t<'a>
type error = Js.Promise.error

type result<'ok, 'error> = t<Result.t<'ok, 'error>>

@new
external make: ((@uncurry ~resolve: (. 'a) => unit, ~reject: (. exn) => unit) => unit) => t<'a> =
  "Promise"

@val @scope("Promise") external resolve: 'a => t<'a> = "resolve"
@val @scope("Promise") external reject: exn => t<'a> = "reject"

@send
external andThen: (t<'a>, @uncurry ('a => t<'b>)) => t<'b> = "then"

@send
external catch: (t<'a>, @uncurry (error => t<'a>)) => t<'a> = "catch"

let result = (x: t<'ok>): result<'ok, 'error> =>
  x->andThen(x => Result.Ok(x)->resolve)->catch(error => Result.Error(error)->resolve)

let wait = (x: result<'ok, 'error>, fn: Result.t<'ok, 'error> => unit): unit =>
  x->andThen(x => x->fn->resolve)->ignore
