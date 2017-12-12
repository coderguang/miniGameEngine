#ifndef _FRAMEWORK_DESIGN_PATTERN_SINGLETON_H_
#define _FRAMEWORK_DESIGN_PATTERN_SINGLETON_H_


//normal singleton,not thread singleton
namespace csg
{

	template <typename T>
	class Singleton
	{
	public:
		static T* instance()
		{
			static T ins;
			return &ins;
		}

	protected:
		Singleton()
		{
		};
		~Singleton()
		{

		}
	private:
		Singleton(const Singleton<T>&)
		{
		}
		Singleton& operator=( const Singleton<T> &)
		{
		}
	};


}
#endif