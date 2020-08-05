#ifndef DESOPERATE_H
#define DESOPERATE_H

#include <QObject>

class DesOperate
{
public:
    DesOperate(QString key);
    ~DesOperate();

private:
    QString m_key[16];  // 子密钥
    QString m_K;  // 密钥K，构造DesOperate类时给出

    QString Ik(QString K);  // 初始置换
    QString Lk(QString IkK, int lnum);  // 左循环移位
    QString Pk(QString X);  // 压缩置换
    QString IPmc(QString mc);  // 初始置换IP
    QString UnIPmc(QString mc);  // 逆初始置换IP-1
    QString dec2b(int n, int fl);  // 十进制数字转二进制字符串
    QString F(QString R, QString K);  // 替换函数F
    QString desC(QString M);  // 16轮加密迭代
    QString desM(QString C);  // 16轮解密迭代
    QString b2ct(QString b);  // 二进制字符串->明文
    QString ct2b(QString ct);  // 明文内容->二进制字符串
    QString key2b(QString key);  // 密钥->二进制字符串

    bool makeKey();  // 子密钥生成
    QString makeData(QString M);  // 64bit分组加密
    QString reData(QString M);  // 分组解密

public:
    QString msg_handle(QString msg);  // 供调用明文加密函数
    QString remsg(QString msg);  // 供调用密文解密函数
};

#endif // DESOPERATE_H
