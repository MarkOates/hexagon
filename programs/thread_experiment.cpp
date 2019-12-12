#include <allegro5/allegro.h>

#include <vector>
#include <iostream>

#include <Blast/ShellCommandExecutorWithCallback.hpp>

ALLEGRO_MUTEX *special_result_string_mutex = nullptr;
std::string result_string = "";

static void *primary_thread(ALLEGRO_THREAD *thread, void *arg)
{
   ALLEGRO_MUTEX *mutex = (ALLEGRO_MUTEX *)arg;
   std::string result = "";

   std::cout << "primary" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor("echo 'Hello Primary World!'");
   result = executor.execute();

   al_lock_mutex(mutex);
   result_string = result;
   al_unlock_mutex(mutex);

   return nullptr;
}

static void *secondary_thread(ALLEGRO_THREAD *thread, void *arg)
{
   ALLEGRO_MUTEX *mutex = (ALLEGRO_MUTEX *)arg;
   std::string result = "";

   std::cout << "secondary" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor("echo 'Hello Secondary World!'");
   result = executor.execute();

   al_lock_mutex(mutex);
   result_string = result;
   al_unlock_mutex(mutex);

   return nullptr;
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

   special_result_string_mutex = al_create_mutex();

   for (auto &thread : threads)
   {
      thread.thread = al_create_thread(thread.function, special_result_string_mutex);
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

   std::cout << "Final string content:" << std::endl;
   std::cout << result_string << std::endl;

   return 0;
}

