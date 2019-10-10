#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

static void *main_thread_func(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "ABCdefghi" << std::endl;
}

int main(int argc, char **argv)
{
   std::vector<std::pair<ALLEGRO_THREAD *, void *(*)(ALLEGRO_THREAD*, void*)>> threads = {};

   al_init();

   int num_threads = 2;
   int i;

   for (auto &thread : threads) thread.first = al_create_thread(main_thread_func, NULL);
   for (auto &thread : threads) al_start_thread(thread.first);
   for (auto &thread : threads)
   {
      al_join_thread(thread.first, NULL);
      al_destroy_thread(thread.first);
   }
}

