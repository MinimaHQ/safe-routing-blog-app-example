type t =
  | Main
  | Posts
  | Post({slug: string})

let fromUrl = (url: RescriptReactRouter.url) =>
  switch url.path {
  | list{} => Main->Some
  | list{"posts"} => Posts->Some
  | list{"posts", slug} => Post({slug: slug})->Some
  | _ => None
  }

type t'

external make: string => t' = "%identity"
external toString: t' => string = "%identity"

let main = "/"->make
let posts = "/posts"->make
let post = (~slug: string) => j`/posts/$(slug)`->make
