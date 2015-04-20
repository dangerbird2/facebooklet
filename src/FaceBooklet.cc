#include "face.h"
#include <iostream>
#include <string>


using namespace std;
namespace fb {

FaceBooklet::~FaceBooklet() { }


FaceBooklet::FaceBooklet(Database const &db,
                         Prompter<std::istream> const &prompter):
    db(db), prompter(prompter) {}

FaceBooklet::FaceBooklet() : prompter(std::cin) {}

FaceBooklet::FaceBooklet(FaceBooklet & book) : db(book.db), prompter(book.prompter) {}

void FaceBooklet::run()
{
  string s;
  cout << "give me a string ->";
  prompter.in >> s;
  cout << endl << s << endl;
}



} // fb