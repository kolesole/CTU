#pragma once

#include <condition_variable>
#include <cstddef>
#include <list>
#include <vector>
#include <thread>

template<typename JobT, typename WorkerT>
class ThreadPool {
private:
    /** Fronta uloh. */
    std::list<JobT> job_queue{};
    /** Vlakna konzumentu zpracovavajicich ulohy. */
    std::vector<std::thread> worker_threads{};

    /** Funkce, kterou maji konzumenti vykonavat. */
    WorkerT worker_fn;

    std::mutex job_mutex;
    std::condition_variable cond_var;


public:
    ThreadPool(size_t thread_count, WorkerT worker) : worker_fn(worker) {
        for (size_t i = 0; i < thread_count; i++) {
            worker_threads.push_back(std::thread([this]() {
                worker_loop();
            }));
        }
    }

    void process(const JobT job) {
        // Bezpecne vlozte ulohu "job" do fronty uloh "job_queue"
        {
            auto lock_prod = std::unique_lock(job_mutex);
            job_queue.push_back(job);
        }
        cond_var.notify_one();
    }

    /** Tato metoda nam umozni volajici funkci v main.cpp pockat na vsechna spustena vlakna konzumentu. */
    void join() {
        // Proiterujeme pres vsechna vlakna a pockame nez skonci.
        for (auto& worker_thread : worker_threads) {
            worker_thread.join();
        }
    }

private:
    void worker_loop() {
        while (true) {
            JobT job;
            {
                auto lock= std::unique_lock(job_mutex);
                if (job_queue.empty()) {
                    cond_var.wait(lock, [&] { return !job_queue.empty(); });
                }
                job = job_queue.front(); // Precteme prvni ulohu ve fronte
                job_queue.pop_front(); // A ulohu odstranime
            }

            if (!job) {
                break; // Pokud je "zpracovana" uloha 0, skoncime
            }

            // Na zaver zavolame "worker_fn" funkci, ktera ulohu vykona
            worker_fn(job);
        }
    }
};
