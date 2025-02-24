#include <QMainWindow>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
#include <QMenuBar>
#include <QFile>
#include <QString>
// 文件对话框
#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>

#include <main_window.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    setGeometry(600, 500, 800, 600);
    set_edit_text();
    set_menu_bar_2();
    connect(m_text_edit, &QTextEdit::textChanged, this, [this]
        {
            m_is_modified = true;
        });
}
MainWindow::~MainWindow()
{
    delete m_settings;
}
void MainWindow::set_edit_text()
{
    m_text_edit = new QTextEdit;
    //设置滚轮策略
    //按需开启
    //Qt命名空间包含各种枚举
    m_text_edit->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
    setCentralWidget(m_text_edit);
}
void MainWindow::set_menu_bar_1()
{
    //设置菜单栏
    auto menu_bar = new QMenuBar;
    setMenuBar(menu_bar);
    //添加菜单文件模块
    QMenu* menu = menu_bar->addMenu("文件");
    //添加打开动作（文件子模块）
    QAction* open = menu->addAction("打开");
    //在文件子模块添加分割线
    menu->addSeparator();
    QAction* save = menu->addAction("保存");
    menu->addSeparator();
    QAction* save_as = menu->addAction("另存为");

    //open->trigger();在代码中触发
    //triggered是信号，connect是连接，&QAction::triggered是信号，this是接收者，&MainWindow::on_open是槽函数
    //手动连接信号与槽
    connect(open, &QAction::triggered, this, &MainWindow::on_open);
    connect(save, &QAction::triggered, this, &MainWindow::on_save);
    connect(save_as, &QAction::triggered, this, &MainWindow::on_save_as);
}
void MainWindow::set_menu_bar_2()
{
    //设置菜单栏
    auto menu_bar = new QMenuBar;
    setMenuBar(menu_bar);
    //添加菜单文件模块
    QMenu* menu = menu_bar->addMenu("文件");
    //添加打开动作（文件子模块）
    QAction* open = menu->addAction("打开");
    //Qt特色，getter方法无get，setter方法有set
    //action->objectName();
    //设置动作名称与槽函数命名对应
    open->setObjectName("open");
    menu->addSeparator();
    QAction* save = menu->addAction("保存");
    save->setObjectName("save");
    menu->addSeparator();
    QAction* save_as = menu->addAction("另存为");
    save_as->setObjectName("save_as");

    auto menu_edit = menu_bar->addMenu("编辑");
    auto auto_wrap = menu_edit->addAction("自动换行");
    auto_wrap->setObjectName("auto_wrap");
    //设置动作可选状态
    auto_wrap->setCheckable(true);

    //setting可以看成json数组，win下会进入注册表，linux会进入config
    m_settings = new QSettings("DaneJone", "Lesson03_notepad");

    //setting全局共享，未创建默认时设置默认值true，已创建则读取值
    bool enable_auto_wrap = m_settings->value("auto_wrap", true).toBool();
    qDebug() << "enable_auto_wrap:" << enable_auto_wrap;

    //主动调用槽函数切换状态
    //on_auto_wrap_triggered(enable_auto_wrap);
    auto_wrap->setChecked(enable_auto_wrap);

    //利用反射自动根据名称连接槽函数
    //只能连接子对象
    QMetaObject::connectSlotsByName(this);
}
void MainWindow::on_open()
{
    qDebug() << "open";
}
void MainWindow::on_save()
{
    qDebug() << "save";
}
void MainWindow::on_save_as()
{
    qDebug() << "save as";
}
void MainWindow::on_open_triggered()
{
    if (!m_text_edit->toPlainText().isEmpty())
    {
        auto btn = QMessageBox::question(this, "提示", "文件未保存，是否保存？", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (btn)
        {
        case QMessageBox::Save:
            on_save_as_triggered();
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            break;
        }
    }
    //打开文件对话框
    //第一个参数指定父对象
    //第二个参数指定标题
    //第三个参数指定过滤器
    QString path = QFileDialog::getOpenFileName(this, u8"打开文件", "", "");
    if (path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if (!file.open(QFile::ReadOnly))
    {
        qWarning() << "open file failed";
        return;
    }
    //默认以utf8读取文件
    QString text = QString::fromUtf8(file.readAll());
    m_text_edit->setPlainText(text);
    file.close();
    m_current_file_name = path;
}
void MainWindow::on_save_triggered()
{
    if (m_current_file_name.isEmpty())
    {
        on_save_as_triggered();
        return;
    }
    QFile file(m_current_file_name);
    if (!file.open(QFile::WriteOnly))
    {
        return;
    }
    file.write(m_text_edit->toPlainText().toUtf8());
    file.close();
    m_is_modified = false;
}
void MainWindow::on_save_as_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, u8"另存为", "", "");
    if (path.isEmpty())
    {
        return;
    }
    QFile file(path);
    if (!file.open(QFile::WriteOnly))
    {
        return;
    }
    file.write(m_text_edit->toPlainText().toUtf8());
    file.close();
    m_is_modified = false;
}
void MainWindow::on_auto_wrap_triggered(bool checked)
{
    //开启按窗口换行
    m_text_edit->setLineWrapMode(checked ? QTextEdit::LineWrapMode::WidgetWidth : QTextEdit::LineWrapMode::NoWrap);
    m_settings->setValue("auto_wrap", checked);

}

void MainWindow::closeEvent(QCloseEvent* event)
{
    //忽略关闭事件
    event->ignore();
    if (m_is_modified)
    {
        auto btn = QMessageBox::question(this, "提示", "文件未保存，是否保存？", QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        switch (btn)
        {
        case QMessageBox::Save:
            if (m_current_file_name.isEmpty())
            {
                on_save_as_triggered();
            }
            else
            {
                on_save_triggered();
            }
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            return;
            break;
        default:
            break;
        }
    }
    QMainWindow::closeEvent(event);
}