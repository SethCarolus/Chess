#include "app.h"

int main() {
  App app = {
    .width = 850,
    .height = 850,
    .fps = 67,
    .title = "Chess"
  };

  init(&app);
  run(&app);
  shutdown(&app);

  return 0;
}
