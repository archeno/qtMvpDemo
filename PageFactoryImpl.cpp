#include "PageFactoryImpl.h"
#include "pages/DataVisView.h"
#include "pages/DownloadView.h"
#include "pages/WebSocketView.h"

PageFactory *createFactory() {
  auto factory = new PageFactory();

  factory->registerPage(
      "Download", []() { return new DownloadView(); },
      PageLifeCycle::AutoDestroy);

  factory->registerPage(
      "WebSocket", []() { return new WebSocketView(); },
      PageLifeCycle::Background);

  factory->registerPage(
      "DataVis", []() { return new DataVisView(); },
      PageLifeCycle::ManualClose);

  return factory;
}
