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

let toString =
  fun
  | Main => "/"
  | Posts => "/posts"
  | Post({slug}) => {j|/posts/$(slug)|j};
