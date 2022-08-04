``
TEST_F([YOUR_SUBJECT_UNDER_TEST]WithAllegroRenderingFixtureTest, INTERACTIVE__will_work_as_expected)
{
   al_install_keyboard();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   ALLEGRO_TIMER *primary_timer = al_create_timer(ALLEGRO_BPS_TO_SECS(60));
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_register_event_source(event_queue, al_get_keyboard_event_source());

   // TODO build subject here

   al_start_timer(primary_timer);
   bool abort = false;
   while(!abort)
   {
      ALLEGRO_EVENT current_event;
      al_wait_for_event(event_queue, &current_event);
      switch(current_event.type)
      {
         case ALLEGRO_EVENT_TIMER:
         {
            clear_display();
            // TODO: render subject here
            al_flip_display();
         }
         break;

         case ALLEGRO_EVENT_KEY_CHAR:
         {
            switch(current_event.keyboard.keycode)
            {
               case ALLEGRO_KEY_TAB:
               break;

               case ALLEGRO_KEY_R:
               break;

               case ALLEGRO_KEY_RIGHT:
               break;

               case ALLEGRO_KEY_LEFT:
               break;

               case ALLEGRO_KEY_UP:
               break;

               case ALLEGRO_KEY_DOWN:
               break;

               case ALLEGRO_KEY_PAD_PLUS:
               break;

               case ALLEGRO_KEY_PAD_MINUS:
               break;

               case ALLEGRO_KEY_ESCAPE:
                  abort = true;
               break;
            }
         }
         break;
      }
   }

   al_destroy_timer(primary_timer);
}

``
