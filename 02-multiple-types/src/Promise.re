type t(+'a) = Js.Promise.t('a);
type error = Js.Promise.error;

type result('ok, 'error) = t(Result.t('ok, 'error));

[@bs.new]
external make:
  (
  [@bs.uncurry]
  ((~resolve: (. 'a) => unit, ~reject: (. exn) => unit) => unit)
  ) =>
  t('a) =
  "Promise";

[@bs.val] [@bs.scope "Promise"] external resolve: 'a => t('a) = "resolve";
[@bs.val] [@bs.scope "Promise"] external reject: exn => t('a) = "reject";

[@bs.send]
external andThen: (t('a), [@bs.uncurry] ('a => t('b))) => t('b) = "then";

[@bs.send]
external catch: (t('a), [@bs.uncurry] (error => t('a))) => t('a) = "catch";

let result = (x: t('ok)): result('ok, 'error) =>
  x
  ->andThen(x => Result.Ok(x)->resolve)
  ->catch(error => Result.Error(error)->resolve);

let wait = (x: result('ok, 'error), fn: Result.t('ok, 'error) => unit): unit =>
  x->andThen(x => x->fn->resolve)->ignore;
