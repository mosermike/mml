/**
 * @author Mike Moser
 * @name Thread.hpp
 * @brief Contains the class Thread which can be used for using threads
 * @details When you want to start a task, you need to use a lambda function. For instance, you can define a task like
 * @details         auto task = [arg1, arg2](int threadId) -> [return type of the function] {return exampleTask(threadId, arg1, arg2);};
 * @details         and then use this task as the parameter for the start function in this class. Note that the return type must be always the same
 * @details         to the initialised value. When you want to print something, then use the operator << with the instance of the class. Therefore it could be
 * @details         useful to use a reference to the class as an argument.
 */

#ifndef MML_INCLUDE_MML_THREAD_HPP
#define MML_INCLUDE_MML_THREAD_HPP

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>
#include <future>
#include <mutex>

namespace mml {
    namespace thread {
        template<typename result>
		/**
		 * @brief Class Threads
		 * @details This class provides functions which can be used to start a task with multiple threads
		 */
        class Threads {
        private:
            std::vector<std::thread> threads; // Vector with the threads
            std::vector<std::future<result>> futures; // Results from the threads
			std::mutex mtx; // Mutex for thread-safe output
        public:
			/**
			 * @brief Number of Threads
			 */
			int size = 0; // Number of threads

            /**
			 * @brief Initialize with a number of threads
			 * @param num Number of Threads
			 */
            Threads(int num) : threads(num), futures(num), mtx(), size(num) {}

            /**
			 * @brief Operator =
			 * @param thread to be copied
			 * @return Instance of this class
			 */
            Threads &operator=(const Threads &thread) noexcept {
                this->threads = thread.threads;
                size = thread.size;
                futures = thread.futures;
                return *this;
            }

            ~Threads() {
                join();
            }

			/**
			 * @brief Output a text while taking into account if another thread is writing
			 * @param threads Instance of the class used to print
			 * @param value to be printed
			 * @return ostream
			*/
			template<typename templ> friend Threads& operator<< (Threads& threads, const templ &value) noexcept {
				std::lock_guard<std::mutex> guard(threads.mtx);
				std::cout << value;
				return threads;
			}

			/**
			 * @brief Output special characters like std::endl
			 * @param threads Instance of the class used to print
			 * @param manip to be printed
			 * @return ostream
			*/
            friend Threads& operator<<(Threads& threads, std::ostream& (*manip)(std::ostream&)) noexcept {
                std::lock_guard<std::mutex> guard(threads.mtx);
                std::cout << manip;
                return threads;
            }
            /**
             * @brief Starts a function with a specific thread
             * @param task Function to be executed
             * @param id Thread id which should execute this function
             * @throw runtime_error : if id > number of threads
             * @note The first argument of the function must be the threadID
             * @note If task has parameters besides the thread id, one needs to create a lambda function: 
             *       auto task = [arg1, arg2](int threadId) -> [return type of the function] {return exampleTask(threadId, arg1, arg2);};
             */
            void start(const std::function<result(int)>& task, int id) {
                if (id >= size)
                    throw std::runtime_error("[Threads::start] Out of range (" + std::to_string(id) + " vs. " + std::to_string(size) + ")");
                
                std::packaged_task<result(int)> packagedTask(task);
                futures[id] = packagedTask.get_future();
                threads[id] = std::thread(std::move(packagedTask), id);
            }

			/**
			 * @brief Put a specific thread to sleep
			 */
            /**
             * @brief Starts a function for all threads
             * @param task Function to be executed
             * @note The first argument of the function must be the threadId
             * @note If task has parameters besides the thread id, one needs to create a lambda function: 
             *       auto task = [arg1, arg2](int threadId) -> [return type of the function] {return exampleTask(threadId, arg1, arg2);};
             */
            void start(const std::function<result(int)>& task) noexcept {
                for (int i = 0; i < size; ++i) {
                    std::packaged_task<result(int)> packagedTask(task); // Packaged Task for getting the result with std::future
                    futures[i] = packagedTask.get_future();
                    threads[i] = std::thread(std::move(packagedTask), i);
                }
            }

			/**
             * @brief Puts a specific thread to sleep. This is should be used inside a lambda function when the function start is started!
			 * @param threadId The threadId of the thread
             * @param id Thread id to sleep
             * @param seconds Duration in seconds to sleep
			 * @throw runtime_error : if id is bigger than the size
             */
			void sleep(int threadId, int id, double seconds) {
                if (id >= size)
                    throw std::runtime_error("[Threads::sleep] Out of range (" + std::to_string(id) + " vs. " + std::to_string(size) + ")");
				if (id == threadId)
                   	std::this_thread::sleep_for(std::chrono::milliseconds((int) seconds/1000));
				return;
            }


            /**
             * @brief Get the results from each thread
             * @return Vector with the results of each thread
             */
            std::vector<result> getResults() noexcept {
                std::vector<result> results;
                for (auto& future : futures) {
                    results.push_back(future.get());
                }
                return results;
            }

            /**
             * @brief Joins all threads and waits for unfinished threads
             */
            void join() noexcept {
                for (std::thread& thread : threads) {
                    if (thread.joinable()) {
                        thread.join();
                    }
                }
            }
        };

		/**
		 * @brief Stop actual thread for a specific time
		 * @param s Seconds to wait
		 */
		void sleep(float s) noexcept {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(s * 1000)));
		}
    }
}

#endif
