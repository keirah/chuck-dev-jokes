type componentState = { 
  joke: option ChuckData.joke,
};

let component = ReasonReact.statefulComponent "ChuckNorrisApp";

let handleLoadingData joke _self => {
  ReasonReact.Update {
    joke: Some joke
  };
};
let handleClick _event self => {
  ChuckData.fetchJoke()
    |> Js.Promise.then_ (fun joke => {
      (self.ReasonReact.update handleLoadingData) joke;
      Js.Promise.resolve ();
    })
    |> ignore;
  ReasonReact.NoUpdate;
};

let make _children => {
  ...component,
  initialState: fun () :componentState => {
    joke: None
  },
  didMount: fun self => {
    ChuckData.fetchJoke ()
      |> Js.Promise.then_ (fun joke => {
        (self.update handleLoadingData) joke;
        Js.Promise.resolve ();
      })
      |> ignore;
    ReasonReact.NoUpdate;
  },
  render: fun ({state} as self) => {
    let chuckJoke = switch (state.joke) {
      | Some joke => <ChuckJoke joke=joke />
      | None => <div> (ReasonReact.stringToElement "Loading") </div>
    };
    <div className="App">
      <div className="App-header"> <h1> (ReasonReact.stringToElement "Chuck Norris Dev Jokes") </h1> </div>
      <button className="mainButton" onClick=(self.update handleClick)> (ReasonReact.stringToElement "Tell us a joke, Chuck" ) </button>
      chuckJoke
    </div> 
  }
};