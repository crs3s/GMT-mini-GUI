#include "new_ps_file.h"
#include "ui_new_ps_file.h"

#include <QMessageBox> //显示提示信息
#include <QValidator> // 正则表达式

new_ps_file::new_ps_file(QWidget *parent) :
    QDialog(parent,Qt::WindowTitleHint | Qt::CustomizeWindowHint), // 隐藏关闭按钮和帮助按钮
    ui(new Ui::new_ps_file)
{
    ui->setupUi(this);
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint); // 去除问号帮助按钮
    this->setWindowTitle("新建画布");

    gmt_cmd = ""; // 清空初始化
    psfilename = "";

    J_option = new GMT_J_option(this); // 添加-J选项
    J_option->show();
    R_option = new GMT_R_option(this); // 添加-R选项
    R_option->show();

    ui->J_Layout->addWidget(J_option);
    ui->R_Layout->addWidget(R_option);

    //限制只能输入正浮点数
    QRegExp regExp("^(?:[1-9]\\d*|0)?(?:\\.\\d+)?$");
    QRegExpValidator *pattern= new QRegExpValidator(regExp, this);
    ui->w_input->setValidator(pattern);
    ui->h_input->setValidator(pattern);
}

new_ps_file::~new_ps_file()
{
    delete ui;
}

void new_ps_file::on_ok_button_clicked()
{
    // 检查宽度
    QString w_input = ui->w_input->text();
    if  ( w_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("宽度不可为空");
        msgBox.exec();
        return;
    }
    // 检查高度
    QString h_input = ui->h_input->text();
    if  ( h_input.isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("高度不可为空");
        msgBox.exec();
        return;
    }
    // 检查文件名
    if ( ui->ps_fname->text().isEmpty() ){
        QMessageBox msgBox;
        msgBox.setText("文件名不可为空");
        msgBox.exec();
        return;
    }

    psfilename = ui->ps_fname->text()+".ps";
    w = w_input;
    h = h_input;

    //gmt_cmd = "gmt basemap -JX"+w_input+"c/"+h_input+"c -R0/"+w_input+"/0/"+h_input+" -B1/1 -P -K > tmp.ps";
    QString Jdata = J_option->sendData();
    QString Rdata = R_option->sendData();
    if (Jdata.length() == 2 || Rdata.length() == 2){
        gmt_cmd = "gmt psxy -JX1/1 -R0/1/0/1 -T -P -K ";
    }else{
        gmt_cmd = "gmt psxy -T -P -K ";
        gmt_cmd += J_option->sendData()+" ";
        gmt_cmd += R_option->sendData()+" ";
    }
    gmt_cmd += "--PS_MEDIA="+w_input+"ix"+h_input+"i ";
    gmt_cmd += "> "+psfilename;

    // 关闭窗口
    delete ui->w_input->validator();
    delete ui->h_input->validator();
    this->close();
}

void new_ps_file::on_w_input_textEdited()
{
    ui->w_cm->setText(" = "+QString::number( ui->w_input->text().toFloat() * 2.54 )+"厘米");
}

void new_ps_file::on_h_input_textEdited(const QString &arg1)
{
    ui->h_cm->setText(" = "+QString::number( ui->h_input->text().toFloat() * 2.54 )+"厘米");
}

void new_ps_file::on_bexit_clicked()
{
    gmt_cmd = "";
    psfilename = "";
    delete ui->w_input->validator();
    delete ui->h_input->validator();
    this->close();
}