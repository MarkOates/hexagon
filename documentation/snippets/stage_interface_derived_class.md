```cpp
parent_classes:


  - class: 'StageInterface'
    scope: public
    init_with: "StageInterface::ADVANCED_CODE_EDITOR"


properties:


  - name: a_default_empty_event
    static: true
    type: ALLEGRO_EVENT
    init_with: "{}"
    getter_ref: true


functions:


  - name: render
    virtual: true
    override: true
    body: |
      return;
    body_dependency_symbols: []


  - name: process_local_event
    virtual: true
    override: true
    parameters:
      - name: event_name
        type: std::string
        default_argument: '""'
      - name: action_data
        type: ActionData
        default_argument: "ActionData()"
    body: |
      return;


  - name: process_event
    virtual: true
    override: true
    parameters:
      - name: event
        type: ALLEGRO_EVENT&
        default_argument: "get_a_default_empty_event_ref()"
    body: |
      return;


dependencies:


  - symbol: StageInterface
    headers: [ Hexagon/StageInterface.hpp ]
  - symbol: ALLEGRO_EVENT
    headers: [ allegro5/allegro.h ]
  - symbol: ALLEGRO_EVENT&
    headers: [ allegro5/allegro.h ]
  - symbol: ActionData
    headers: [ Hexagon/ActionData.hpp ]
```
