#include "face.h"

namespace fb {

FaceBooklet::FaceBooklet() : db(Database())
{
  prompter = Prompter(&db);
}

FaceBooklet::~FaceBooklet() { }

void FaceBooklet::run() { }


std::ostream &operator<<(std::ostream &os, const IFaceBookletNode &node)
{
  return os << node.describe();
}

bool operator==(IFaceBookletNode const &self, IFaceBookletNode const &rhs)
{
  return self.get_id() == rhs.get_id();
}

FaceBooklet::FaceBooklet(Database &&db)
    : db(std::move(db))
{
  prompter = Prompter(&db);
}

Database *FaceBooklet::get_db() { return &db; }
} // fb