#ifndef FACE_BOOKLET_H
#define FACE_BOOKLET_H

namespace fb {

class FaceBooklet {
public:
  FaceBooklet();

  ~FaceBooklet();

  // delete copy constructor
  FaceBooklet(FaceBooklet &) = delete;

  void run();
};

} // fb

#endif // FACE_BOOKLET_H
