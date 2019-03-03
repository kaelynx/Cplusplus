#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){
  //check for enough arguments
  if(argc != 3) {
    std::cerr << argv[0] << " invalid number of arguments." << '\n';
    return 1;
  }
  //open file1
  std::ifstream in(argv[1]);
  if(!in) { std::cerr << "Couldn't open " << argv[1] << "\n"; exit(1); }  
  //open file2
  std::ifstream in2(argv[2]);
  if(!in2) { std::cerr << "Couldn't open " << argv[2] << "\n"; exit(1); }

  std::string line, line2;
  std::string fileName = argv[1];
  std::string fileName2 = argv[2];
  int countLine = 0, countChar = 0;

  //  while(std::getline(in, line) != std::getline(in2, line2)){ works on wasp but not os high sierra??
  while(!in.eof() || !in2.eof()){
    std::getline(in, line);
    std::getline(in2, line2);
    ++countLine;
    //if lines aren't the same
    if(line.compare(line2) != 0){
      int max = line.size() > line2.size() ? line.size() : line2.size(); 
      int temp = 0;
      for(int i = 0; i < max; ++i){
	  if(line[i] == line2[i]){
	  ++countChar;
	}
	if(line[i] != line2[i]){
	  //exit once different character is found, reset counter
	  temp = countChar;
	  countChar = 0;
	  i = max;
	}
      }
      std::string l = std::to_string(countLine);
      std::string tmpString = ": " + l + ": ";
      std::cout<< fileName << tmpString << line << std::endl; 
      std::cout<< fileName2 << tmpString << line2 << std::endl; 
      int length = fileName.size() + tmpString.size() + temp;
      std::string spaceString(length, ' ');
      std::cout<< spaceString;
      std::cout<< "^" << std::endl;
    }
  }
  in.close();
  in2.close();
}
