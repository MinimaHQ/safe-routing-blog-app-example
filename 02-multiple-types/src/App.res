@react.component
let make = () => {
  let route = Router.useRouter()

  switch route {
  | Some(Main) => <Main />
  | Some(Posts) => <Posts />
  | Some(Post({slug})) => <Post slug />
  | None => <NotFound />
  }
}
