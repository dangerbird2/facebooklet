#include <facebooklet/face.h>

namespace fb {

FaceBooklet::FaceBooklet() { }

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

} // fb