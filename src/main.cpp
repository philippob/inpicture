#include <memory>

#include "inpicture/InPicture.h"

int main(int argc, char **argv) {
  auto inPicture = std::make_unique<InPicture>();
  return inPicture->run(argc, argv);
}