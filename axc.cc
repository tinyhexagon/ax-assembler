#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

char currentCharacter;
std::string buffer;
std::vector<std::string>binaryCode;

void pushBinary(std::string binary)
{
  binaryCode.push_back(binary);
  buffer.clear();
}

void pushLangToken(std::string token, std::string binary)
{
  if (buffer == token)
  {
    pushBinary(binary);
  }
}

void lexFile(std::ifstream &sourceFile)
{
  while (sourceFile.get(currentCharacter))
  {

    if (!std::isspace(currentCharacter))
    {
      buffer.push_back(currentCharacter);
    }

    int nextChar = sourceFile.peek();

    pushLangToken("nop", "00000");
    pushLangToken("mov", "00001");
    pushLangToken("add", "00010");
    pushLangToken("sub", "00011");
    pushLangToken("and", "00100");
    pushLangToken("or", "00101");
    pushLangToken("xor", "00110");
    pushLangToken("not", "00111");
    pushLangToken("lsh", "01000");
    pushLangToken("rsh", "01001");
    pushLangToken("in", "01010");
    pushLangToken("out", "01011");
    pushLangToken("jmp", "01100");
    pushLangToken("call", "01101");
    pushLangToken("ret", "01110");
    pushLangToken("halt", "11111");
    pushLangToken("ax", "0000");
    pushLangToken("bx", "0001");
    pushLangToken("cx", "0010");
    pushLangToken("dx", "0011");
    pushLangToken("ex", "0100");
    pushLangToken("fx", "0101");
    pushLangToken("gx", "0110");
    pushLangToken("hx", "0111");

    if (isdigit(buffer.front()) && !isdigit(nextChar))
    {
      int number = std::stoi(buffer);
      pushBinary(std::bitset<8>(number).to_string());
    }

    std::cout << buffer << '\n';
  }
}

int main(int argc, char **argv)
{
  std::ifstream sourceFile(argv[1], std::ios::in);
  std::ofstream outFile(argv[2], std::ios::out);

  lexFile(sourceFile);

  for (const auto& binary : binaryCode)
  {
    outFile << binary << '\n';
  }

  sourceFile.close();
  outFile.close();
}