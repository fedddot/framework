#ifndef	__ITASK_HPP__
#define	__ITASK_HPP__

namespace task {
	class ITask {
	public:
		virtual ~ITask() noexcept = 0;
		virtual void execute() = 0;
	}; // ITask
} // namespace task

#endif // __ITASK_HPP__