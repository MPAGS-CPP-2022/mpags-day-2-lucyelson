#include <cctype>
#include <iostream>
#include <string>
#include <vector>

std::string runCaesarCipher( const std::string& inputText, const size_t key, const bool encrypt ){

    // Create the alphabet container and output string
    std::string outputText;

    const std::vector<char> alphabet = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
        'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
        'U', 'V', 'W', 'X', 'Y', 'Z'};

    const std::size_t alphabetSize{alphabet.size()};

    // We need to make sure that the key can only be selected between 0 and 25
    const std::size_t KeyRange{key % alphabetSize};

    // Loop over the input text
    char processedChar{'x'};
    for (const auto& startChar : inputText) {
        // For each character find the corresponding position in the alphabet
        for (size_t i{0}; i < alphabetSize; ++i) {
            if (startChar == alphabet[i]) {
                // Apply the shift 
                if (encrypt) {
                    // encrypt the message
                    processedChar = alphabet[(i + KeyRange) % alphabetSize];} 
                else{
                    // decrypt the message
                    processedChar = alphabet[(i + alphabetSize - KeyRange) % alphabetSize];}
                break;
            }
        }

        // Add the new character to the output text
        outputText += processedChar;    
    }   

    // Finally (after the loop), return the output string
    return outputText;
    
}