```
  - name: font_bin
    type: AllegroFlare::FontBin*
    init_with: nullptr
    constructor_arg: true



  - name: obtain_text_font
    private: true
    type: ALLEGRO_FONT*
    guards: [ font_bin ]
    body: |
      return font_bin->auto_get("Menlo-Regular.ttf -20");



  - symbol: AllegroFlare::FontBin*
    headers: [ AllegroFlare/FontBin.hpp ]
```
