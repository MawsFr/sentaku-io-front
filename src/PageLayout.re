/**
 * This component reprensents the main layout of the website. It contains the menu and its content changes depending on the url
 */
open Model;
open FirebaseConfig;
open RoleDecode;
open BsFirebase.ReasonFirebase.Auth;

type page =
  | Index
  | Trainings
  | Training(string)
  | Login
  | Register;

/* | NewTraining; */
type state = {
  nowShowing: page,
  connection: connectionState,
  userInfos: option(user)
};


type action =
  | Login(User.t, string, role)
  | ShowIndex
  | ShowTraining(string)
  | ShowTrainings;

/* | ShowNewTraining; */
let component = ReasonReact.reducerComponent("PageLayout");

let make = _children => {
  ...component,
  initialState: () => {nowShowing: Index, connection: NotLogged, userInfos: None},
  reducer: (action, state) => {
    switch action {
    /* router actions */
    | ShowIndex => ReasonReact.Update({...state, nowShowing: Index})
    | ShowTrainings => ReasonReact.Update({...state, nowShowing: Trainings})
    | ShowTraining(id) => ReasonReact.Update({...state, nowShowing: Training(id)})
    | Login(user, token, role) => 
      ReasonReact.UpdateWithSideEffects({...state, connection: Logged, 
          userInfos: Some({
            id: User.uid(user),
            email: switch(Js.Nullable.toOption(User.email(user))) {
            | Some(value) => value
            | None => ""
            },
            token: token,
            role: role
          })
        }, ((self) => {
            Js.log(self.state.userInfos);
            ReasonReact.Router.push("/trainings");
          })
<<<<<<< Updated upstream
=======
        }, ((_self) =>
            /*ReasonReact.Router.push("/trainings"))*/
            Js.log("yo"))
>>>>>>> Stashed changes
        )
    }
  },
    didMount: ( self ) => {
      onAuthStateChanged(FirebaseConfig.auth, 
        ~nextOrObserver = (user) => 
        {
          let opt = Js.Null.toOption(user);
          switch opt {
            | Some(value) => {
                Js.Promise.(User.getIdToken(value)
                |> then_(
                    token => {
                      let optToken = Js.Nullable.toOption(token);
                      switch optToken {
                      | Some(valueToken) => {
<<<<<<< Updated upstream
                        [%bs.debugger];
                          BsFirebase.ReasonFirebase.Database.Reference.once(
                            BsFirebase.ReasonFirebase.Database.ref(FirebaseConfig.db, ~path="users/" ++ User.uid(value), ()),
                            ~eventType="value",
                            ()
                          )
                          |> Js.Promise.then_(
                            (roleInfos) => {
                              [%bs.debugger];
                              BsFirebase.ReasonFirebase.Database.DataSnapshot.val_(roleInfos)
                              |> (role) => parseRole(role) |> getRole
                              |> (role) => {
                                Js.log(role);
                                self.send(Login(value, valueToken, role)) |> resolve
                              }
                            }
                          );
=======
                          self.send(Login(value, valueToken))
                          |> resolve
>>>>>>> Stashed changes
                        }
                        | None => Js.Promise.resolve()
                      }
                    }
                  ) |> ignore
                )
            }
            | None => Js.log();
          };
          
        },
        ~error = (err) => Js.log(err),
        ~completed = (u) => {
          Js.log("completed");
          Js.log(u);
        }
      );
      ReasonReact.NoUpdate;
    },
  render: ({state}) =>
    <div>
      <Header userInfos=state.userInfos connection=state.connection/>
      <div className="row content">
        <div className="">
          <ul id="slide-out" className="col m2 side-nav fixed">
            <div className="brand-sidebar">
              <h1 className="logo-wrapper">
                <a className="brand-logo">
                  <img src="images/logo.png" className="responsive-img" />
                  <span className="logo-text" />
                </a>
              </h1>
            </div>
            <li> <div className="divider" /> </li>
            <li className="no-padding">
              <a href="/trainings" className="waves-effect waves-teal">
                (str("Formations"))
              </a>
            </li>
            <li>
              <a className="waves-effect waves-teal" href="#newtrainings">
                (str("Creer une formation"))
              </a>
            </li>
            <li>
              <a className="waves-effect waves-teal" href="#roles">
                (str("Liste des contacts"))
              </a>
            </li>
          </ul>
          (
            ReasonReact.cloneElement(
              <a href="#" className="button-collapse">
                <i className="material-icons"> (str("menu")) </i>
              </a>,
              ~props={"data-activates": "slide-out"},
              [||]
            )
          )
        </div>
        /***
         * Here add the component to show depending on the state of the current layout
         */
        <div className="col m8 offset-m2">
          <Router>
            ...(
                 (url: ReasonReact.Router.url) =>
                   <div>
                     (
                       switch url.path {
                       | ["training", id] => <Training id />
                       | ["login"] => <Login />
                       | ["disconnect"] => <Disconnect />
                       | ["register"] => <Register />
                       | ["admin"] => <Administration />
                       | _ => <Trainings />
                       }
                     )
                   </div>
               )
          </Router>
        </div>
        <div className="col m2">
          <div className="col m12 pub">
            <img src="images/pub1.jpg" className="responsive-img" />
          </div>
          <div className="col m12 pub">
            <img src="images/pub2.jpg" className="responsive-img" />
          </div>
        </div>
      </div>
    </div>
};