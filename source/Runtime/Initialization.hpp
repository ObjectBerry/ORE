#pragma once
namespace Runtime {
	class DependencyContainer;
}
namespace Runtime {
	DependencyContainer* _dependencyContainer;

	void initializeVM(int argc, char** argv);
	void handleLineArguments(int argc, char** argv);
	void parseResourceFile();
}