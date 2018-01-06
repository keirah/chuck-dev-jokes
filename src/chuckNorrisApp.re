type state = {joke: option(ChuckData.joke)};

type action =
  | LoadJoke(ChuckData.joke);

let component = ReasonReact.reducerComponent("ChuckNorrisApp");

let handleLoadingData = (joke, _self) =>
  ReasonReact.Update({joke: Some(joke)});

let handleClick = (_event, self) => {
  ChuckData.fetchJoke()
  |> Js.Promise.then_(joke => {
       (self.ReasonReact.reduce((_) => LoadJoke(joke)))(joke);
       Js.Promise.resolve();
     })
  |> ignore;
  ReasonReact.NoUpdate;
};

let make = _children => {
  ...component,
  reducer: (action, _state) =>
    switch action {
    | LoadJoke(joke) => ReasonReact.Update({joke: Some(joke)})
    },
  initialState: () => ({joke: None}: state),
  didMount: self => {
    ChuckData.fetchJoke()
    |> Js.Promise.then_(joke => {
         (self.reduce((_) => LoadJoke(joke)))(joke);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(error => {
         Js.log("I'm a caught error");
         Js.Promise.resolve(Js.log(error));
       })
    |> ignore;
    ReasonReact.NoUpdate;
  },
  render: ({state}) => {
    let chuckJoke =
      switch state.joke {
      | Some(joke) => <ChuckJoke joke />
      | None => <div> (ReasonReact.stringToElement("Loading")) </div>
      };
    <div className="App">
      <div className="App-header">
        <h1> (ReasonReact.stringToElement("Chuck Norris Dev Jokes")) </h1>
      </div>
      <button className="mainButton">
        (ReasonReact.stringToElement("Tell us a joke, Chuck"))
      </button>
      <div> chuckJoke </div>
    </div>;
  }
};