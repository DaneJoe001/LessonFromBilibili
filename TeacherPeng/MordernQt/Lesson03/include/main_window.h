#pragma once

#include <QMainWindow>
#include <QTextEdit>
//用于存储配置文件
#include <QSettings>
#include <QString>

class MainWindow : public QMainWindow
{
    //要实现反射机制,必须使用Q_OBJECT
    //Q_OBJECT宏要求分离声明和实现,否则编译不过
    //当类中自定义信号时也需要使用Q_OBJECT
    //现代Qt槽不需要使用Q_OBJECT
    //旧版Qt信号与槽必须使用Q_OBJECT
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void set_edit_text();
    void set_menu_bar_1();
    void set_menu_bar_2();
    void on_open();
    void on_save();
    void on_save_as();
    //槽定义需要区分public和private
    //信号定义必须公开(不用带public)
    //添加Q_SLOTS宏才能使槽函数自动连接
    //slots对标Q_SLOTS宏,建议使用大写宏
public Q_SLOTS:
    //on+动作+triggered命名函数才符合自动连接条件
    //MOC编译器会处理以下函数以及可选参数
    //Qt的信号参数必须不少于槽参数
    //多余的信号参数会被忽略
    void on_open_triggered();
    void on_save_triggered();
    void on_save_as_triggered();
    void on_auto_wrap_triggered(bool checked);
    //Qt的事件虚函数都以protected声明
protected:
    //重载关闭事件
    virtual void closeEvent(QCloseEvent* event) override;
private:
    QTextEdit* m_text_edit = nullptr;
    QSettings* m_settings = nullptr;
    QString m_current_file_name;
    bool m_is_modified = false;
};