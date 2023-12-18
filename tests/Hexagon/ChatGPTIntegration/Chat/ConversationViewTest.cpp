
#include <gtest/gtest.h>

#include <Hexagon/ChatGPTIntegration/Chat/ConversationView.hpp>

#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


TEST(Hexagon_ChatGPTIntegration_Chat_ConversationViewTest, can_be_created_without_blowing_up)
{
   Hexagon::ChatGPTIntegration::Chat::ConversationView conversation_view;
}


TEST(Hexagon_ChatGPTIntegration_Chat_ConversationViewTest, VISUAL__render__renders_beautifully)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   al_init_image_addon();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   AllegroFlare::FontBin font_bin;
   AllegroFlare::BitmapBin bitmap_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");
   bitmap_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/bitmaps");

   Hexagon::ChatCPTIntegration::Conversation conversation;
   conversation.build_known_authors();

   conversation.append_text_message(1, "Hey! What's up? This is a first message.");
   conversation.append_text_message(1, "This is another message in the chat log.");
   conversation.append_text_message(2, "Finally, a third message. It's pretty alright.");
   conversation.append_text_message(3, "This is a fourth message.");

   Hexagon::ChatGPTIntegration::Chat::ConversationView conversation_view(&bitmap_bin, &font_bin, &conversation);
   conversation_view.render();

   al_flip_display();

   al_rest(1);

   al_destroy_display(display);
   al_uninstall_system();
}


