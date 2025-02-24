#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QLineEdit>
//添加int型输入限制
#include <QIntValidator>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    enum class Operation
    {
        None,//无操作
        Plus,
        Minus,
        Multiply,
        Divide
    };
    double m_lastNumber = 0;
    Operation m_operation = Operation::None;
public:
    MainWindow(QWidget* parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Qt计算器");
        setFixedSize(400, 300);

        setCentralWidget(new QWidget);
        QVBoxLayout* layout = new QVBoxLayout;
        centralWidget()->setLayout(layout);

        lineEdit = new QLineEdit(this);
        lineEdit->setFixedHeight(50);
        lineEdit->setAlignment(Qt::AlignRight);
        lineEdit->setText("0");
        //限制输入必须为整数，甚至可以限制输入范围
        lineEdit->setValidator(new QIntValidator);
        layout->addWidget(lineEdit);

        QPushButton* button = new QPushButton("确认");
        layout->addWidget(button);
        //连接信号与槽
        //如果使用lmbda表达式作为槽函数(回调函数)，不能随便使用引用捕获，会导致生命周期问题，最好使用值捕获
        connect(button, &QPushButton::clicked, this, &MainWindow::button_confirm);

        QPushButton* button2 = new QPushButton("取消");
        layout->addWidget(button2);
        //Qt智能的地方在于信号对象或槽对象，只要一方被析构，连接就会自动断开。
        //甚至可以在槽函数中主动释放槽对象,达到单次触发槽函数的目的
        //connect有五个参数的重载，第一个参数是信号对象，第二个参数是信号函数，第三个参数是槽对象，第四个参数是槽函数，第五个参数是连接类型
        connect(button2, &QPushButton::clicked, this, &MainWindow::button_cancel);

    }
private slots:
    void button_confirm()
    {
        //获取输入框中的值,并通过OK按钮来判断是否输入了数字
        bool ok = false;
        double value = lineEdit->text().toDouble(&ok);
        if (!ok)
        {
            QMessageBox::warning(this, u8"警告", u8"请输入数字");
        }
        else
        {
            QMessageBox::information(this, u8"确认", QString("输入的值为%1").arg(value));
        }
    }
    void button_cancel()
    {
        QMessageBox::information(this, "Button02", "Button02 clicked");
    }
    void press_plus()
    {
        //先暂存之前输入的值
        double temp = lineEdit->text().toDouble();
        lineEdit->clear();
        double temp2 = lineEdit->text().toDouble();
        m_lastNumber = temp + temp2;
    }
    void press_minus()
    {

    }
    void press_multiply()
    {

    }
    void press_divide()
    {
        lineEdit->setText(QString::number(m_lastNumber));
    }
    void press_equal()
    {
        //设置显示精度
        lineEdit->setText(QString::number(m_lastNumber, 'g', 10));
    }
private:
    QLineEdit* lineEdit = nullptr;
};

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.show();

    return app.exec();
}