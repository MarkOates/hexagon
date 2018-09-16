#ifndef __AF_GENERATE_TEXTURES_HEADER
#define __AF_GENERATE_TEXTURES_HEADER




#include <allegro_flare/allegro_flare.h>




// shapes

ALLEGRO_BITMAP *generate_circle_bitmap(float size=512, ALLEGRO_COLOR col=color::white, int padding=0);
ALLEGRO_BITMAP *generate_triangle_bitmap(float x1, float y1, float x2, float y2, float x3, float y3, ALLEGRO_COLOR col=color::white);

// gradients

ALLEGRO_BITMAP *generate_gradient_bitmap(float size=512, ALLEGRO_COLOR top_color=color::transparent, ALLEGRO_COLOR bottom_color=color::black, int padding=0);

ALLEGRO_BITMAP *generate_circle_gradient_bitmap(float size=512, ALLEGRO_COLOR top_color=color::transparent, ALLEGRO_COLOR bottom_color=color::black, int padding=0);

// textures

ALLEGRO_BITMAP *generate_noise_bitmap(float w, float h, float min_intensity=0.5, float max_intensity=0.7);
ALLEGRO_BITMAP *generate_wood_grain_bitmap(float w, float h, ALLEGRO_COLOR base_color=al_color_name("sienna"));
ALLEGRO_BITMAP *generate_brush_metal_bitmap(float w, float h, ALLEGRO_COLOR base_color=al_color_name("white"));

// graphs

ALLEGRO_BITMAP *generate_interpolator_graph_bitmap(float (*interpolator_func)(float), float size=512, ALLEGRO_COLOR col=color::white, float thickness=5, float padding=0);

// pixel patterns

ALLEGRO_BITMAP *create_pixel_pattern_1(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int checker_size=4);
ALLEGRO_BITMAP *create_pixel_pattern_2(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int dot_distance=4);
ALLEGRO_BITMAP *create_pixel_pattern_3(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int x_distance=6, int y_distance=3);
ALLEGRO_BITMAP *create_pixel_pattern_4(ALLEGRO_COLOR pixel1_color, ALLEGRO_COLOR pixel2_color, int x_distance=5, float slope=-1);




#endif
