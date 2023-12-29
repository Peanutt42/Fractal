#pragma once

#include <thread>
#include <functional>
#include <mutex>
#include <queue>
#include <vector>

class ThreadPool {
public:
	ThreadPool() {
		size_t count = std::thread::hardware_concurrency();
		threadsFinished.resize(count);
		for (size_t i = 0; i < count; i++) {
			threadsFinished[i] = std::make_shared<std::atomic_bool>(true);
			m_Threads.emplace_back([this, i] {
				while (true) {
					if (stop.load())
						return;

					std::function<void()> task;
					{
						std::scoped_lock lock(mutex);
						if (!workQueue.empty()) {
							threadsFinished[i]->store(false);
							{
								task = workQueue.front();
								workQueue.pop();
							}
						}
					}

					if (task) {
						task();
						threadsFinished[i]->store(true);
					}
				}
			});
		}
	}

	~ThreadPool() {
		stop.store(true);
		for (auto& thread : m_Threads)
			thread.join();
	}

	void add(const std::function<void()>& work) {
		std::scoped_lock lock(mutex);
		workQueue.push(work);
	}

	void wait() {
		while (true) {
			bool allDone = true;
			for (const auto& threadFinished : threadsFinished) {
				if (!threadFinished->load()) {
					allDone = false;
					break;
				}
			}
			if (allDone)
				break;
		}
	}

private:
	std::mutex mutex;
	std::queue<std::function<void()>> workQueue;
	std::vector<std::thread> m_Threads;
	std::vector<std::shared_ptr<std::atomic_bool>> threadsFinished;
	std::atomic_bool stop = false;

};