#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

static void *main_thread_func(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "ABCdefghi" << std::endl;
}

int main(int argc, char **argv)
{
   std::vector<ALLEGRO_THREAD *> threads;

   al_init();
   ALLEGRO_THREAD *main_thread = al_create_thread(main_thread_func, nullptr);

   int num_threads = 2;
   int i;

   for (auto &thread : threads) thread = al_create_thread(main_thread_func, NULL);
   for (auto &thread : threads) al_start_thread(thread);
   for (auto &thread : threads)
   {
      al_join_thread(thread, NULL);
      al_destroy_thread(thread);
   }
}

