type joke = {
  icon_url: string,
  value: string,
};
let parseChuckJokeJson json :joke =>
  Json.Decode.{
    icon_url: field "icon_url" string json,
    value: field "value" string json
  };

let chuckApi = "https://api.chucknorris.io/jokes/random?category=dev";

let fetchJoke () =>
  Bs_fetch.fetch chuckApi
    |> Js.Promise.then_ Bs_fetch.Response.json
    |> Js.Promise.then_ (fun json =>
    Js.Promise.resolve (parseChuckJokeJson json )
    );
