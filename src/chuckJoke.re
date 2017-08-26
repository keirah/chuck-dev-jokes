let component = ReasonReact.statelessComponent "ChuckJoke";

let make joke::(joke: ChuckData.joke) _children => {
  ...component,
  render: fun _self =>
    <div className="ChuckJoke" >
      <img src=joke.icon_url /> 
      <h2> (ReasonReact.stringToElement joke.value) </h2> 
    </div>
};