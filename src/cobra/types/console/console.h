#ifndef CONSOLE_H_
#define CONSOLE_H_

#include "cobra/types/script/script.h"
#include "cobra/mem/isolate.h"
#include "console-bytes.h"

namespace Cobra {
namespace internal{

	class Console
	{
	public:
		static void CB(Isolate* isolate, std::string sub);
	};

} // namespace internal
}

#endif // CONSOLE_H_
