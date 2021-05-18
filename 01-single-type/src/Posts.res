type state =
  | Fetching
  | Ready(array<Api.post>)
  | Error

type action =
  | SetData(array<Api.post>)
  | Fail

let reducer = (_state, action) =>
  switch action {
  | SetData(posts) => Ready(posts)
  | Fail => Error
  }

@react.component
let make = () => {
  let (state, dispatch) = reducer->React.useReducer(Fetching)

  React.useEffect0(() => {
    Api.getPosts()->Promise.wait(x =>
      switch x {
      | Ok(data) => SetData(data)->dispatch
      | Error(_) => Fail->dispatch
      }
    )
    None
  })

  switch state {
  | Fetching => "Fetching post..."->React.string
  | Ready(posts) =>
    posts
    ->Array.map(post =>
      <div key=post.id>
        <Router.Link route=Post({slug: post.slug})> {post.title->React.string} </Router.Link>
      </div>
    )
    ->React.array
  | Error => "Oops, something went wrong"->React.string
  }
}
