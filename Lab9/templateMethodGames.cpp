
// Games, Template Method example
// Mikhail Nesterenko
// 2/4/2014

#include <ctime>
#include <cstdlib>
#include <iostream>

using std::cout; using std::endl;

// template for any game where players take 
// turns to make moves
// and there is a winner
class Game{
public:
  Game():playersCount_(0), movesCount_(0), 
	 playerWon_(noWinner){}

  // template method
  void playGame(const int playersCount = 0) {
    playersCount_ = playersCount;
    movesCount_=0;

    initializeGame();

    for(int i=0; !endOfGame(); 
	i = (i+1) % playersCount_ ){
      makeMove(i);
      if (i==playersCount_-1) 
	++movesCount_; 
    }

    printWinner();
  }

  virtual ~Game(){}

protected:
  // primitive operations
  virtual void initializeGame() = 0;
  virtual void makeMove(int player) = 0;
  virtual void printWinner() = 0;
  virtual bool endOfGame() {
    return playerWon_ != noWinner;} // this is a hook
  // returns true if winner is decided
  static const int noWinner=-1;

  int playersCount_;
  int movesCount_;
  int playerWon_;
};

// Monopoly - a concrete game implementing primitive 
// operations for the template method
class Monopoly: public Game {
public:  
  // implementing concrete methods
  void initializeGame(){
    playersCount_ = rand() % numPlayers_ + 1 ; // initialize players
  }

  void makeMove(int player) {
    if (movesCount_ > minMoves_){ 
       const int chance = 
	 minMoves_ + rand() % (maxMoves_ - minMoves_);
       if (chance < movesCount_) playerWon_= player;
    }
  }

  void printWinner(){
    cout << "Monopoly, player "<< playerWon_<< " won in "
         << movesCount_<< " moves." << endl;
  }

private:
  static const int numPlayers_ = 8; // max number of players
  static const int minMoves_ = 20; // nobody wins before minMoves_
  static const int maxMoves_ = 200; // somebody wins before maxMoves_
};

// Chess - another game implementing
//  primitive operations
class Chess: public Game {
public:
  void initializeGame(){
    playersCount_ = numPlayers_; // initalize players
    for(int i=0; i < numPlayers_; ++i) 
      experience_[i] = rand() % maxExperience_ + 1 ; 
  }

  void makeMove(int player){
    if (movesCount_ > minMoves_){
      const int chance = (rand() % maxMoves_) / experience_[player];
      if (chance < movesCount_) playerWon_= player;
    }
  }

  void printWinner(){
    cout << "Chess, player " << playerWon_ 
         << " with experience " << experience_[playerWon_]
         << " won in "<< movesCount_ << " moves over"
         << " player with experience " << experience_[playerWon_== 0 ? 1:0] 
	 << endl;
  }

private:
  static const int numPlayers_ = 2;
  static const int minMoves_ = 2; // nobody wins before minMoves_
  static const int maxMoves_ = 100; // somebody wins before maxMoves_
  static const int maxExperience_ = 3; // player's experience
  // the higher, the greater probability of winning
  int experience_[numPlayers_]; 
};

class Dice: public Game {
public:
  void initializeGame(){
    playersCount_ = numPlayers_; // initalize players
  }

  void makeMove(int player){
    int diceArray[5];
    int sumScore = 0;
    int highScore = 0;
    char answer = 'y';

    static int cHigh = 0;
    static int pHigh = 0;
    static int cPrevHigh = 0;
    static int pPrevHigh = 0;
    static bool repeat = true;
    static int cHighest = 0;
    static int pHighest = 0;
    static bool cPass = false;
    static bool pPass = false;
    static int passCount = 0;
    bool endGame = false;

    if(movesCount_ < maxMoves_){
      cout << (player == 0 ? "Computer" : "You") << " rolled: ";
      if((player == 0 && cPass == true) || (player == 1 && pPass == true)) {
	cout << "pass, ";
	player == 0 ? (cPass = false) : (pPass = false);
	if(pPass == true && cPass == true) endGame = true;
      }
      else { 
	for(int i = 0; i < 5; ++i) {
	  diceArray[i] = (rand() % 6) + 1;
	  sumScore += diceArray[i];
	  cout << diceArray[i] << " ";
	}
	cout << "= " << sumScore << " ";
	if(sumScore > highScore) {
	  highScore = sumScore;
	}
	sumScore = 0;
	
	if(player == 0) {
	  cHigh = highScore;
	  if(cHigh > cPrevHigh){
	    cHighest = cHigh;
	  }
	}
	if(player == 1) {
	  pHigh = highScore;
	  if(pHigh > pPrevHigh){
	    pHighest = pHigh;
	  }
	}
	cPrevHigh = cHigh;
	pPrevHigh = pHigh;
      }
      cout << (player == 0 ? "computer's" : "your") << " highest score was: " << (player == 0 ? cHighest : pHighest) << endl;
    }

    if((movesCount_ < maxMoves_ - 1) && endGame == false) {
      if(player == 0){
	int randPick = 0;
	randPick = (rand() % 2);
	if(randPick == 0) answer = 'n';
	if(randPick == 1) answer = 'y';
	if(answer == 'n') {
	  cPass = true;
	}
      }
      if(player == 1){
	cout << "Roll again? [y/n]" << endl;
	std::cin >> answer;
	if(answer == 'y') repeat = true;
	if(answer == 'n') { 
	  pPass = true;
	}
      }
    }

    if(movesCount_ >= maxMoves_ || endGame == true){
      if(cHighest > pHighest || cHighest == pHighest){
	playerWon_ = 0;
      } else {
	playerWon_ = 1;
      }
    }
  }
  
  void printWinner(){
    cout << (playerWon_ == 0 ? "Computer" : "You") << " won! " <<endl; 
  }

private:
  static const int numPlayers_ = 2;
  static const int minMoves_ = 0; // nobody wins before minMoves_
  static const int maxMoves_ = 3; // somebody wins before maxMoves_
};

int main() {
  srand(time(nullptr));

  Game* gp = nullptr;

  // play chess 10 times
  for (int i = 0; i < 10; ++i){ 
    gp = new Chess;
    gp->playGame(); 
    delete gp;
  }
      
  // play monopoly 5 times
  for (int i = 0; i < 5; ++i){
    gp = new Monopoly;
    gp->playGame(); 
    delete gp;
  }

  // play dice once
  gp = new Dice;
  gp->playGame();
  delete gp;

}
