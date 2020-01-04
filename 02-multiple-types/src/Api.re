type post = {
  id: string,
  title: string,
  slug: string,
  content: string,
};

let posts = [|
  {id: "1", title: "Post #1", slug: "post-1", content: "Foo"},
  {id: "2", title: "Post #2", slug: "post-2", content: "Bar"},
|];

let delay = fn => {
  fn->Js.Global.setTimeout(2000)->ignore;
};

let getPosts = () =>
  Promise.make((~resolve, ~reject as _) => delay(() => resolve(. posts)))
  ->Promise.result;

let getPostBySlug = (~slug) =>
  Promise.make((~resolve, ~reject as _) =>
    delay(() => {
      let post = posts->Array.getBy(post => post.slug == slug);
      resolve(. post);
    })
  )
  ->Promise.result;
