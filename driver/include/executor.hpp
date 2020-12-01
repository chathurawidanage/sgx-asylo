#ifndef C9841B2A_9FFB_49B0_A051_9D2CA20A8674
#define C9841B2A_9FFB_49B0_A051_9D2CA20A8674
#include <list>
#include <mutex>
#include <queue>

#include "job.hpp"
#include "worker_handler.hpp"

namespace tasker {

class Driver;

class JobExecutor {
   private:
    std::unordered_map<std::string, std::shared_ptr<Job>> jobs{};
    std::mutex jobs_lock{};

    std::queue<std::shared_ptr<tasker::WorkerHandler>> available_workers{};
    std::mutex workers_lock{};

    std::unordered_map<std::string, std::string> worker_assignment{};  // <worker_id, job_id>

    tasker::Driver &driver;

    void Progress();

   public:
    JobExecutor(tasker::Driver &driver);

    void AddJob(std::shared_ptr<Job> job);

    void AddWorker(std::string &worker_id, std::string &worker_type);

    /**
     * This function will be called by Job to get a worker allocated for the job
     **/
    std::shared_ptr<tasker::WorkerHandler> AllocateWorker(Job &to, std::string worker_type);

    void ReleaseWorker(Job &of, std::shared_ptr<tasker::WorkerHandler> worker);

    void ForwardMsgToJob(std::string &from, std::string &msg);

    void Start();
};
}  // namespace tasker
#endif /* C9841B2A_9FFB_49B0_A051_9D2CA20A8674 */
