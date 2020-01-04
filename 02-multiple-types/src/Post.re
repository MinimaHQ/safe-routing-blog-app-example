type state =
  | Fetching
  | Ready(Api.post)
  | Error(error)
and error =
  | NotFound
  | Unknown;

type action =
  | SetData(option(Api.post))
  | Fail;

let reducer = (_state, action) =>
  switch (action) {
  | SetData(Some(post)) => Ready(post)
  | SetData(None) => Error(NotFound)
  | Fail => Error(Unknown)
  };

[@react.component]
let make = (~slug) => {
  let (state, dispatch) = reducer->React.useReducer(Fetching);

  React.useEffect0(() => {
    Api.getPostBySlug(~slug)
    ->Promise.wait(
        fun
        | Ok(data) => SetData(data)->dispatch
        | Error(_) => Fail->dispatch,
      );
    None;
  });

  switch (state) {
  | Fetching => "Fetching post..."->React.string
  | Ready(post) =>
    <>
      <h1> post.title->React.string </h1>
      <div> post.content->React.string </div>
      <Router.Link route=Route.posts>
        "Back to posts"->React.string
      </Router.Link>
    </>
  | Error(NotFound) => "Oops, can't find this post"->React.string
  | Error(Unknown) => "Oops, something went wrong"->React.string
  };
};
