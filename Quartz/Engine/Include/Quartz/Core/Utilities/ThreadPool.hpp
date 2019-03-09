// Copyright 2019 Genten Studios
// 
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the 
// following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the 
// following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the 
// following disclaimer in the documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote 
// products derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED 
// WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A 
// PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY 
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
// OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
// DAMAGE.

#pragma once

#include <Quartz/Core/Core.hpp>

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
		namespace utils
		{
			template <int ThreadCount = 4>
			class QZ_API ThreadPool
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
}

