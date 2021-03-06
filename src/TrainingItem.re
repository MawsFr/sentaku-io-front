open Model;

/**
* This module shows the training infos
*/
let component = ReasonReact.statelessComponent("TrainingItem");

let make = (~training, _children) => {
  ...component,
  render: _self =>
    <div className="col m12 card">
      <div className="col m2">
        <img src=training.logo className="responsive-img" />
      </div>
      <div className="col m10">
        <div className="row">
          <span className="formation-title">
            <Link 
            href=("/training/" ++ training.id) 
            className="">
                (str(training.title))
            </Link>
          </span>
          <span>
            <i className="material-icons rate-stars"> (str("star_half")) </i>
          </span>
          <span>
            <i className="material-icons rate-stars"> (str("star")) </i>
          </span>
          <span>
            <i className="material-icons rate-stars"> (str("star")) </i>
          </span>
          <span>
            <i className="material-icons rate-stars"> (str("star")) </i>
          </span>
          <span>
            <i className="material-icons rate-stars"> (str("star")) </i>
          </span>
        </div>
        <div className="row">
          <p className="formation-description">
            (str(training.description))
          </p>
        </div>
      </div>
    </div>
};