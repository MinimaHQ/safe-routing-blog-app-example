type t =
  | Main
  | Posts
  | Post({slug: string})

let fromUrl: RescriptReactRouter.url => option<t>

type t'

external toString: t' => string = "%identity"

let main: t'
let posts: t'
let post: (~slug: string) => t'
