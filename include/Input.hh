#ifndef INPUT_HH_
#define INPUT_HH_

#include <InputManager.hpp>

class Input : public InputManager
{
public:
  Input();
  ~Input();

  virtual Key getInput();
protected:
};

#endif /* !INPUT_HH_ */