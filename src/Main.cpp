/////////////////////////////////
/// @file Main.cpp
///
/// @brief Implementation of main
///
/// @author Luke Karavolis
/////////////////////////////////

// SYSTEM INCLUDES
// (None)

// C PROJECT INCLUDES
// (None)

// C++ PROJECT INCLUDES
#include <CLI/CLI.hpp>
#include "Process.hpp"  // For Process
#include "KeywordDict.hpp" // For KeywordDict class
#include "MemoryApi.hpp" // For Memory::MemoryApi
#include "Logger.hpp" // For Logger

////////////////////////////////
/// FUNCTION NAME: main
////////////////////////////////
int main(int argc, char* argv[])
{
    CLI::App app{"ARM Instruction Set Architecture Simulator"};

    std::string filename = "";
    CLI::Option* pFileOption = app.add_option("-f, --file", filename, "Main assembly code file");
    pFileOption->required();
    pFileOption->check(CLI::ExistingFile);

    bool debug = false;
    app.add_flag("-d, --debug", debug, "Runs the program in debug mode");

    CLI11_PARSE(app, argc, argv);

    // Initialize the keyword dictionary
    KeywordDict::GetInstance().Initialize();

    // Initialize the memory subsystem
    Memory::MemoryApi::Initialize();

    // Create empty Process in heap
    Process* pProcess = new Process();

    // Initalize the process using the given file
    pProcess->Initialize(filename.c_str());

    pProcess->Execute(debug);

    pProcess->PrintSummary(&std::hex);

    delete pProcess;

    // Close the memory file
    Memory::MemoryApi::Close();

    // Close the log file
    Logger::GetInstance().Close();

    return 0;
}