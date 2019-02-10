#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

#include <deque>
#include <vector>
#include <functional>

namespace qz
{
	namespace threads
	{
		template <int ThreadCount = 4>
		class ThreadPool
		{
		public:
			ThreadPool()
			{
				for (std::size_t i = 0; i < ThreadCount; ++i)
				{
					m_threads.emplace_back([this]()
					{
						while (true)
						{
							std::function<void()> task;

							{
								std::unique_lock<std::mutex> lock(m_taskMutex);

								m_condition.wait(lock, [this]() { return !m_running || !m_scheduledTasks.empty(); });

								if (!m_running && m_scheduledTasks.empty())
									return;

								task = m_scheduledTasks.front();
								m_scheduledTasks.pop_front();
							}

							task();
						}
					}
					);
				}
			}

			~ThreadPool()
			{
				m_running = false;
				m_condition.notify_all();

				for (std::thread& taskWorker : m_threads)
					taskWorker.join();
			};

			void addWork(std::function<void()> fun)
			{
				{
					std::unique_lock<std::mutex> lock(m_taskMutex);
					m_scheduledTasks.emplace_back(fun);
				}

				m_condition.notify_one();
			}

		private:
			bool m_running;

			std::mutex m_taskMutex;
			std::condition_variable m_condition;

			std::vector<std::thread> m_threads;
			std::deque<std::function<void()>> m_scheduledTasks;
		};

	}
}
