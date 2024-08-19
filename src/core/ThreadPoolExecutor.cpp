#include "ThreadPoolExecutor.h"
#include "../common/options.h"

namespace exec {

ThreadPoolExecutor::ThreadPoolExecutor(const common::Options& opts) noexcept
: m_contexts(opts.Cores) {
    auto cores = opts.Cores-1;
    m_workers.reserve(cores);
    for(unsigned i=0; i<cores; i++) {
        m_contexts[i].id = i;
        m_workers.emplace_back(&ThreadPoolExecutor::worker_loop_, this, std::ref(m_contexts[i]));
    }
}

ThreadPoolExecutor::~ThreadPoolExecutor() {
    m_active.store(false, std::memory_order_release);
    m_cv.notify_all();
}

void ThreadPoolExecutor::worker_loop_(exec::ThreadContext& ctx) noexcept {
    while (true) {
        typename decltype(m_jobs)::value_type job;
        {
            std::unique_lock lock(m_mtx);
            m_cv.wait(lock, [this]() { return !m_jobs.empty() || !m_active.load(std::memory_order_relaxed); });

            if (!m_active.load(std::memory_order_acquire))
                break;

            job.swap(m_jobs.front());
            m_jobs.pop();
        }
        std::invoke(job, ctx);
    }
}

std::size_t ThreadPoolExecutor::capacity() noexcept {
    return m_workers.size();
}

} // exec