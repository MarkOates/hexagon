#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

static void *main_thread_func(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "ABCdefghi" << std::endl;
}

struct thread_type {
   ALLEGRO_THREAD *thread;
   void *(*function)(ALLEGRO_THREAD*, void*);
};

int main(int argc, char **argv)
{
   std::vector<thread_type> threads = {};

   al_init();

   int num_threads = 2;
   int i;

   for (auto &thread : threads) thread.thread = al_create_thread(thread.function, NULL);
   for (auto &thread : threads) al_start_thread(thread.thread);
   for (auto &thread : threads)
   {
      al_join_thread(thread.thread, NULL);
      al_destroy_thread(thread.thread);
      thread.thread = nullptr;
   }
}

