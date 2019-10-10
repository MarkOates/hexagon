#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

static void *entry(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "ABCdefghi" << std::endl;
}

class Thread
{
public:
   ALLEGRO_THREAD *thread;
   void *(*function)(ALLEGRO_THREAD*, void*);
};

int main(int argc, char **argv)
{
   std::vector<Thread> threads = {
     { nullptr, entry },
     { nullptr, entry },
   };

   al_init();

   int num_threads = 2;
   int i;

   for (auto &thread : threads)
   {
      thread.thread = al_create_thread(thread.function, NULL);
   }
   for (auto &thread : threads)
   {
      al_start_thread(thread.thread);
   }
   for (auto &thread : threads)
   {
      al_join_thread(thread.thread, NULL);
      al_destroy_thread(thread.thread);
      thread.thread = nullptr;
   }
}

