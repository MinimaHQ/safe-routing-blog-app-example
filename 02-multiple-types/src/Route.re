type t =
  | Main
  | Posts
  | Post({slug: string});

let fromUrl = (url: ReasonReactRouter.url) =>
  switch (url.path) {
  | [] => Main->Some
  | ["posts"] => Posts->Some
  | ["posts", slug] => Post({slug: slug})->Some
  | _ => None
  };

type t';

external make: string => t' = "%identity";
external toString: t' => string = "%identity";

let main = "/"->make;
let posts = "/posts"->make;
let post = (~slug: string) => {j|/posts/$(slug)|j}->make;
