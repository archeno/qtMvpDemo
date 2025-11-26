#include "PageFactory.h"

void PageFactory::registerPage(const QString &name,
                               std::function<QWidget *()> creator,
                               PageLifeCycle lifeCycle) {
  m_pagesInfo[name] = {creator, lifeCycle};
}

QWidget *PageFactory::getPage(const QString &name) {
  if (m_pages.contains(name))
    return m_pages[name];

  if (!m_pagesInfo.contains(name))
    return nullptr;

  auto page = m_pagesInfo[name].creator();
  page->setObjectName(name);
  m_pages[name] = page;
  m_pageLife[name] = m_pagesInfo[name].lifeCycle;
  return page;
}

PageLifeCycle PageFactory::getPageLifeCycle(const QString &name) {
  return m_pageLife.value(name, PageLifeCycle::AutoDestroy);
}

void PageFactory::removePage(const QString &name) {
  if (m_pages.contains(name)) {
    m_pages[name]->deleteLater();
    m_pages.remove(name);
    m_pageLife.remove(name);
  }
}

QStringList PageFactory::getPageNames() const { return m_pagesInfo.keys(); }
