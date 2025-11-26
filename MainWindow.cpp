#include "MainWindow.h"
#include <QHBoxLayout>
#include <QCloseEvent>

MainWindow::MainWindow(PageFactory* factory, QWidget *parent)
    : QMainWindow(parent), m_factory(factory)
{
    m_stack = new QStackedWidget;
    m_listWidget = new QListWidget;

    for (const QString &name : factory->getPageNames()) {
        m_listWidget->addItem(name);
    }

    connect(m_listWidget, &QListWidget::currentRowChanged,
            this, &MainWindow::onPageChanged);

    auto central = new QWidget;
    auto layout = new QHBoxLayout(central);
    layout->addWidget(m_listWidget);
    layout->addWidget(m_stack, 1);
    setCentralWidget(central);

    m_listWidget->setCurrentRow(0);
    QString lastPage = loadLastActivePage();
    if (!lastPage.isEmpty()) {
        QWidget* page = m_factory->getPage(lastPage);
        if (page && m_stack->indexOf(page) == -1)
            m_stack->addWidget(page);
        if (page)
            m_stack->setCurrentWidget(page);
    }
}

void MainWindow::onPageChanged(int index)
{
    QString newPageName = m_listWidget->item(index)->text();
    QWidget* newPage = m_factory->getPage(newPageName);
    if (m_stack->indexOf(newPage) == -1)
        m_stack->addWidget(newPage);
    m_stack->setCurrentWidget(newPage);

    for (int i = 0; i < m_stack->count(); ++i) {
        QWidget* w = m_stack->widget(i);
        QString oldPageName = w->objectName();
        if (w == newPage) continue;
        auto life = m_factory->getPageLifeCycle(oldPageName);
        if (life == PageLifeCycle::AutoDestroy) {
            m_stack->removeWidget(w);
            m_factory->removePage(oldPageName);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveLastActivePage();
    QMainWindow::closeEvent(event);
}

void MainWindow::saveLastActivePage()
{
    QSettings settings("MyCompany", "QtMVPDemo");
    QWidget* currentPage = m_stack->currentWidget();
    if (currentPage)
        settings.setValue("lastPage", currentPage->objectName());
}

QString MainWindow::loadLastActivePage()
{
    QSettings settings("MyCompany", "QtMVPDemo");
    return settings.value("lastPage", "").toString();
}

void MainWindow::closeCurrentPage()
{
    QWidget* currentPage = m_stack->currentWidget();
    if (!currentPage) return;
    QString pageName = currentPage->objectName();
    m_stack->removeWidget(currentPage);
    m_factory->removePage(pageName);
    if (m_stack->count() > 0)
        m_stack->setCurrentIndex(0);
}