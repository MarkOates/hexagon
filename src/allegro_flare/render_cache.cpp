



#include <allegro_flare/render_cache.h>

#include <allegro_flare/color.h> // for color::transparent




RenderCache::RenderCache()
   : render(nullptr)
   , padding(100)
   , previous_state()
   , previous_samples(0)
   , previous_depth(0)
   , dirty(true)
{}




RenderCache::~RenderCache()
{
   al_destroy_bitmap(render);
}




void RenderCache::setup_surface(int w, int h, int multisamples, int depth)
{
   previous_samples = al_get_new_bitmap_samples();
   previous_depth = al_get_new_bitmap_depth();

   al_store_state(&previous_state, ALLEGRO_STATE_BITMAP | ALLEGRO_STATE_TRANSFORM);

   int target_width = w + padding * 2;
   int target_height = h + padding * 2;

   // create a new render surface if the proper surface does not exist
   if (!render
       || al_get_bitmap_width(render) != target_width
       || al_get_bitmap_height(render) != target_height
       || al_get_bitmap_samples(render) != multisamples
       || al_get_bitmap_depth(render) != depth
      )
   {
      al_destroy_bitmap(render);
      al_set_new_bitmap_samples(multisamples);
      al_set_new_bitmap_depth(depth);

      render = al_create_bitmap(target_width, target_height);
   }

   al_set_target_bitmap(render);

   // set a projection on this surface that offsets drawing by (+padding, +padding)
   ALLEGRO_TRANSFORM transform;
   al_identity_transform(&transform);
   al_translate_transform(&transform, padding, padding);
   al_use_transform(&transform);

   al_clear_to_color(color::transparent);
}




void RenderCache::finish_surface()
{
   al_set_new_bitmap_depth(previous_depth);
   al_set_new_bitmap_samples(previous_samples);
   al_restore_state(&previous_state);

   mark_as_clean();
}




void RenderCache::draw(float origin_x, float origin_y)
{
   if (render) al_draw_bitmap(render, origin_x-padding, origin_y-padding, 0);
}




void RenderCache::mark_as_dirty()
{
   dirty = true;
}




void RenderCache::mark_as_clean()
{
   dirty = false;
}




bool RenderCache::is_dirty()
{
   return dirty;
}




