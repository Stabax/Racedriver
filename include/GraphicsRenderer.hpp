#ifndef GRAPHICSRENDERER_HPP_
#define GRAPHICSRENDERER_HPP_

#include <string>

class GraphicsRenderer
{
public:
  GraphicsRenderer(int posx, int posy, int fontSize)
  : x(posx), y(posy), fontsize(fontSize)
  {
  }

  virtual ~GraphicsRenderer() = 0;

  virtual void alert(const std::string &str);

  virtual void clear() = 0;

  virtual void drawString(const std::string &str, int x, int y) = 0;

  void getLineY(int line)
  {
    return (y + (line * fontsize));
  }

protected:
  int x, y, fontsize;
};

#endif /* !GRAPHICSRENDERER_HPP_ */