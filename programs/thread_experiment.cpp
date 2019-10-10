#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

#include <Blast/ShellCommandExecutorWithCallback.hpp>

static void *primary_thread(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "primary" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor("echo 'Hello Primary World!'");
   executor.execute();
}

static void *secondary_thread(ALLEGRO_THREAD *thread, void *arg)
{
   std::cout << "secondary" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor("echo 'Hello Secondary World!'");
   executor.execute();
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
     { nullptr, primary_thread },
     { nullptr, secondary_thread },
   };

   al_init();

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

