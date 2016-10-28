
class Console
{
public:
  Console();
  ~Console();

  //Display
  void show();
  void hide();
  void toggle();

  //Output
  void clear();

  //State
  bool isOpen();

  //Logic
  bool update();
  void draw();
  
private:
  bool _open;
  std::vector<std::string> _history;
};
