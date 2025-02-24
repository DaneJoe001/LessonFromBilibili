#include <string>
#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QLabel>
//V为垂直布局，H为水平布局
#include <QVBoxLayout>
#include <QHBoxLayout>
//网格布局
#include <QGridLayout>

#define TEACHING_MODE
#ifdef TEACHING_MODE
void func();
void check_QString();
#endif

class Label :public QLabel
{
public:
    //使用explicit关键字，防止隐式转换
    explicit Label(QWidget* parent = nullptr)
        :QLabel(parent)
    {
        setText("Minecraft");
        //设置对齐方式(可组合使用)
        setAlignment(Qt::AlignCenter);
        //label->setAlignment(Qt::AlignHTop | Qt::AlignLeft);
        //label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        //设置样式，推荐使用R原始字符串(会保留换行等原始信息)
        setStyleSheet(R"(
                    QLabel{
                        background-color:black;
                        color:white;
                        font-size:40px;
                        //设置边界
                        Margin:20px;
                        font-weight:bold;})");
    }
};

class MainWindow :public QMainWindow
{
public:
    MainWindow(QMainWindow* parent = nullptr)
        :QMainWindow(parent)
    {
        //设置窗口标题，会自动构造QString
        setWindowTitle("Lesson01");
        //content01();
        //content02();
        content03();
    }
private:
    void content01()
    {
        //设置窗口大小
        //win.setFixedSize(QSize(800, 600));
        //设置窗口初始位置及大小
        setGeometry(400, 400, 800, 600);
        //设置窗口内容
        Label* label = new Label(this);

        //设置主窗口的中心控件，同时成为了子对象
        //必须指定父对象或设置为对象的空间，否则new的对象会泄露
        //Qt会自动处理label在内存中的位置，不用担心new和直接创建实例的区别
        setCentralWidget(label);
    }
    void content02()
    {
        setGeometry(500, 500, 600, 400);
        QWidget* central_widget = new QWidget(this);
        setCentralWidget(central_widget);

        //创建布局
        QVBoxLayout* layout = new QVBoxLayout();
        central_widget->setLayout(layout);

        Label* label1 = new Label(this);
        label1->setText("label1");
        //添加到布局中
        layout->addWidget(label1);
        Label* label2 = new Label(this);
        label2->setText("label2");
        layout->addWidget(label2);
        //可以通过循环添加
        for (int i = 3;i < 5;i++)
        {
            Label* label = new Label(this);
            label->setText(QString("label%1").arg(i));
            //label->setText("label")+QString::number(i));
            layout->addWidget(label);
        }
    }
    void content03()
    {
        setGeometry(500, 500, 600, 400);
        QWidget* central_widget = new QWidget(this);
        setCentralWidget(central_widget);

        //创建布局
        QGridLayout* layout = new QGridLayout();
        central_widget->setLayout(layout);

        //绘制一个乘法表
        for (int i = 0;i <= 9;i++)
        {
            for (int j = 0;j <= 9;j++)
            {
                Label* label = new Label(this);
                label->setText(QString("%1*%2=%3").arg(i).arg(j).arg(i * j));
                //label->setText("label")+QString::number(i));
                //表格布局中可以指定行号和列号
                layout->addWidget(label, i, j);
            }
        }
    }
};

int main(int argc, char* argv[])
{
    //QApplication维持一个全局实例
    QApplication app(argc, argv);
    //内部会自动调用单例获取实例
    MainWindow main_win;
    qDebug() << "win is hidden:" << main_win.isHidden();
    //show可以显示不同大小的窗口
    main_win.show();
    //win.showFullScreen();
    //exec()中处理事件主循环
    return app.exec();
}

#ifdef TEACHING_MODE

//所有Qt类都继承自QObject
void func()
{
    //通过instance获取实例
    QApplication::instance();
    //所有的Qt类都继承自QObject
    //创建QObject并包含父子关系，会自动析构
    //对象树析构，不包含的才需要手动delete
    QObject* obj = new QObject();
    QObject* obj2 = new QObject(obj);
    QObject* obj3 = new QObject();
    //设置父子关系
    obj3->setParent(obj2);
    //Qt中获取父对象等属性都是小写方法
    obj3->parent();
}

void check_QString()
{
    //QDebug输出QString会输出引号以及转义字符本身
    QString check_str = "1 2 3\n\t1212";
    qDebug() << check_str;
    //split()会返回QStringList 打印结果：QList("1", "2", "3\n\t1212")
    qDebug() << check_str.split(' ');
    //splite支持中文文本
    QString check_str2 = "1中2中3\n\t1212";
    qDebug() << check_str2.split(u'中');
    //std::string转QString
    std::string std_str = "std::string";
    QString qstr = QString::fromStdString(std_str);
    //QString转std::string
    std::string std_str2 = qstr.toStdString();
}
#endif