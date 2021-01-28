#pragma once
namespace Runtime {
	class DependencyContainer;
}
namespace Runtime {
	
	DependencyContainer* getDContainer() ;

	void initializeVM(int argc, char** argv);
	void handleLineArguments(int argc, char** argv);
	char* readBootstrapFile();
	void createBootstrapProcess(); 


	void start();
}