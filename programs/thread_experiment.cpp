#include <allegro5/allegro.h>

#include <iostream>

static void *main_thread_func(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "ABCdefghi" << std::endl;
}

int main(int argc, char **argv)
{
   ALLEGRO_THREAD *thread[128];

   al_init();
   ALLEGRO_THREAD *main_thread = al_create_thread(main_thread_func, nullptr);

   int num_threads = 2;
   int i;

   for (i = 0; i < num_threads; i++) {
      thread[i] = al_create_thread(main_thread_func, NULL);
   }
   for (i = 0; i < num_threads; i++) {
      al_start_thread(thread[i]);
   }
   for (i = 0; i < num_threads; i++) {
      al_join_thread(thread[i], NULL);
      al_destroy_thread(thread[i]);
   }

}

