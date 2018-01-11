let component = ReasonReact.statelessComponent("ChuckJoke");

let make = (~joke: ChuckData.joke, _children) => {
  ...component,
  render: _self =>
    <div className="ChuckJoke">
      <img src=joke.icon_url />
      <h2> (ReasonReact.stringToElement(joke.value)) </h2>
    </div>
};
