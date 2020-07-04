#pragma once

#include <mutex>
#include <condition_variable>

namespace threading {

    class Semaphore {
    public:
        Semaphore(int init = 1): mValue(init) { }

        void acquire() {
            std::unique_lock guard(mMutex);

            // Check the mutex value, and wait if need be.
            if(--mValue < 0) {
                // Make us wait.  When we wait, the mutex is unlocked until the
                // wait ends.
                mConditionVar.wait(guard);
            }
        }

        void release() {
            std::unique_lock guard(mMutex);

            // Start a waiting thread if required.
            if(++mValue <= 0) mConditionVar.notify_one();
        }

    private:
        int mValue;                             // Value of semaphore.
        std::mutex mMutex;                      // Controls access.
        std::condition_variable mConditionVar;  // Controls waiting and restart
    };

} // namespace threading
