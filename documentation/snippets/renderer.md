```yml
properties:

  - name: font_bin
    type: AllegroFlare::FontBin*
    init_with: nullptr
    constructor_arg: true
  - name: quote
    type: std::string
    init_with: '{}'

functions:

  - name: render
    type: void
    guards: [ al_is_system_installed(), al_is_font_addon_initialized() ]
    body: |
      return;

  - name: obtain_quote_font
    private: true
    type: ALLEGRO_FONT*
    guards: [ font_bin ]
    body: |
      return font_bin->auto_get("Purista Medium.otf -32");

dependencies:

  - symbol: AllegroFlare::FontBin*
    headers: [ AllegroFlare/FontBin.hpp ]
  - symbol: ALLEGRO_FONT*
    headers: [ allegro5/allegro_font.h ]
```

