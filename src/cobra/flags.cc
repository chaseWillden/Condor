#include "flags.h"

namespace Cobra {
namespace internal{

	void Flags::SetCommandLineFlags(int argc, const char* argv[]){
		for (int i = 0; i < argc; i++){
			std::string arg = argv[i];
			if (arg == "--trace-parser") Flags::traceParser = true;
			else if (arg == "--trace-check") Flags::traceCheck = true;
			else if (arg == "--print-variables") Flags::printVariables = true;
			else if (arg == "--print-exported") Flags::exportedNodes = true;
			else if (arg == "--parsing-time") Flags::parsingTime = true;
			else if (arg == "--heap-insert") Flags::heapInsert = true;
			else if (arg == "--heap-delete") Flags::heapDelete = true;
			else if (arg == "--memory-audit") Flags::memoryAudit = true;
			else if (arg == "--memory-request") Flags::memoryRequest = true;
			else if (arg == "--expand-ast") Flags::expandAST = true;
			else if (arg == "--allow-native") Flags::allowNative = true;
			else if (arg == "--print-asm") Flags::printAsm = true;
			else if (arg == "-h" || arg == "--help"){
				printf("\n\nCobraLang\n=========\n(C) 2015 Cobra Authors\n\n");
				printf("--trace-parser\t\t%s\n", "Trace the path of the parser");
				printf("--trace-check\t\t%s\n", "Trace the path of the ast checker");
				printf("--print-variables\t%s\n", "Prints the variables inside each scope");
				printf("--print-exported\t%s\n", "Prints the exported nodes in the context");
				printf("--parsing-time\t\t%s\n", "Prints the time it took to parse");
				printf("--heap-insert\t\t%s\n", "Tracks what is being inserted into the heap");
				printf("--heap-delete\t\t%s\n", "Tracks what is being deleted out of the heap");
				printf("--memory-audit\t\t%s\n", "Audits the memory used and whats free");
				printf("--memory-request\t%s\n", "Tracks the memory requested");
				printf("--expand-ast\t\t%s\n", "Expand the abstract syntax tree");
				printf("--allow-native\t\t%s\n", "Allow native functions in code");
				printf("--print-asm\t\t%s\n", "Print the asembly generated");
			}
			else if (arg.find("-") != std::string::npos || arg.find("-") != std::string::npos){
				printf("Unidentified flag\nExiting...\n");
				exit(0);
			}
		}
	}

	bool Flags::traceParser = false;
	bool Flags::traceCheck = false;
	bool Flags::printVariables = false;
	bool Flags::parsingTime = false;
	bool Flags::heapInsert = false;
	bool Flags::heapDelete = false;
	bool Flags::exportedNodes = false;
	bool Flags::memoryAudit = false;
	bool Flags::memoryRequest = false;
	bool Flags::expandAST = false;
	bool Flags::allowNative = false;
	bool Flags::printAsm = false;

} // namespace internal
} // namespace Cobra