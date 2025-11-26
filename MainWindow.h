#pragma once
#include "PageFactory.h"
#include <QListWidget>
#include <QMainWindow>
#include <QSettings>
#include <QStackedWidget>

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(PageFactory *factory, QWidget *parent = nullptr);

protected:
  void closeEvent(QCloseEvent *event) override;
private slots:
  void onPageChanged(int index);

private:
  void saveLastActivePage();
  QString loadLastActivePage();
  void closeCurrentPage();
  PageFactory *m_factory;
  QStackedWidget *m_stack;
  QListWidget *m_listWidget;
};