#include <arken/image.h>
#include <QImage>

using namespace arken;


void Image::save(const char * path, int quality)
{
  QImage image(m_path.data());
  string format = string(path).suffix(".");
  image.save(path, format.data(), quality);
}
