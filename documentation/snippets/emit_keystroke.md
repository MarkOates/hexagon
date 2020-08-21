```cpp
   ALLEGRO_EVENT keyboard_key_event;
   keyboard_key_event.type = ALLEGRO_EVENT_KEY_DOWN;
   keyboard_key_event.keyboard.keycode = ALLEGRO_KEY_ESCAPE;
   al_emit_user_event(al_get_keyboard_event_source(), &keyboard_key_event, nullptr);
```
