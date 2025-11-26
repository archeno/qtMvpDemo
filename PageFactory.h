#pragma once
#include <QMap>
#include <QString>
#include <QWidget>
#include <functional>

enum class PageLifeCycle { AutoDestroy, Background, ManualClose };

struct PageInfo {
  std::function<QWidget *()> creator;
  PageLifeCycle lifeCycle;
};

class PageFactory {
public:
  void registerPage(const QString &name, std::function<QWidget *()> creator,
                    PageLifeCycle lifeCycle = PageLifeCycle::AutoDestroy);

  QWidget *getPage(const QString &name);
  PageLifeCycle getPageLifeCycle(const QString &name);
  void removePage(const QString &name);
  QStringList getPageNames() const;

  QWidget *getPageInstanceIfExists(const QString &name) {
    return m_pages.value(name, nullptr);
  }

private:
  QMap<QString, PageInfo> m_pagesInfo;
  QMap<QString, QWidget *> m_pages;
  QMap<QString, PageLifeCycle> m_pageLife;
};
