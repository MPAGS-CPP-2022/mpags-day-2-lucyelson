#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Our project headers
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "runCaesarCipher.hpp"

//! Transliterate char to string
std::string transformChar(const char in);

std::string runCaesarCipher(const std::string& inputText, const size_t key, const bool encrypt );

bool processCommandLine(const std::vector<std::string>& args,
                        bool& helpRequested,
                        bool& versionRequested,
                        std::string& inputFileName,
                        std::string& outputFileName, 
                        std::string& cipherKey, 
                        bool& encrypt);

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};
    //const std::size_t nCmdLineArgs{cmdLineArgs.size()};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    std::string cipherKey{""};
    bool encrypt{true};

    if (!processCommandLine( cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, cipherKey, encrypt)){

        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  -k KEY           Select the cipher Key\n"
            << "  --encrypt        Will use the caesar cipher to encrypt the text \n\n"
            << "  --decrypt        Will use the caesar cipher to decrypt the text\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;}

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

     // Read in user input
    if (!inputFile.empty()) {
        // Open the file and check that we can read from it
        std::ifstream inputStream{inputFile};
        if (!inputStream.good()) {
            std::cerr << "[error] failed to create istream on file '"
                      << inputFile << "'" << std::endl;
            return 1;
        }

        // Loop over each character from input file
        while (inputStream >> inputChar) {
            inputText += transformChar(inputChar);
        }

    } else {
        // Loop over each character from terminal input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }

    // Add in Caesar cipher 
    std::size_t caesarkey{0};
    if (!cipherKey.empty()) {
        
        for (const auto& elem : cipherKey) {
            if (!std::isdigit(elem)) {
                std::cerr
                    << "[error] cipher key must be an unsigned long integer,\n"
                    << "        the key (" << cipherKey
                    << ") could not be converted" << std::endl;
                return 1;
            }
        }
        caesarkey = std::stoul(cipherKey);
    }

    // Run the Caesar cipher function
    std::string outputText{runCaesarCipher(inputText, caesarkey, encrypt)};

    // Output the text
    if (!outputFile.empty()) {
        // Open the file and check that we can write to it
        std::ofstream outputStream{outputFile};
        if (!outputStream.good()) {
            std::cerr << "[error] failed to create ostream on file '"
                      << outputFile << "'" << std::endl;
            return 1;
        }

        // Print text to file
        outputStream << outputText << std::endl;

    } else {
        // Print text to terminal
        std::cout << outputText << std::endl;
    }

    return 0;
}


