type t =
  | Main
  | Posts
  | Post({slug: string})

let fromUrl = (url: ReasonReactRouter.url) =>
  switch url.path {
  | list{} => Main->Some
  | list{"posts"} => Posts->Some
  | list{"posts", slug} => Post({slug: slug})->Some
  | _ => None
  }

let toString = x =>
  switch x {
  | Main => "/"
  | Posts => "/posts"
  | Post({slug}) => j`/posts/$(slug)`
  }
