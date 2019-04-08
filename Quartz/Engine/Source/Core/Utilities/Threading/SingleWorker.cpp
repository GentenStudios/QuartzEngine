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

#include <Quartz/Core/Utilities/Threading/SingleWorker.hpp>

using namespace qz::utils::threading;

SingleWorker::SingleWorker(): m_running(true)
{
	std::thread t(&SingleWorker::threadHandle, this);
	m_thread.swap(t);
}

SingleWorker::~SingleWorker()
{
	m_running = false;
	m_condition.notify_all();

	if (m_thread.joinable())
		m_thread.join();
}

void SingleWorker::addWork(std::function<void()>&& function)
{
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_queue.emplace_back(std::move(function));
	}

	m_condition.notify_one();
}

void SingleWorker::threadHandle()
{
	while (true)
	{
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(m_mutex);

			m_condition.wait(lock, [this] { return !m_running || !m_queue.empty(); });

			if (!m_running && m_queue.empty())
				return;

			task = std::move(m_queue.front());
			m_queue.pop_front();
		}

		task();
	}
}
