# 使用帮助

## 如何获取RSA签名

开个店API接口使用RSA_SHA265获取数字签名

C++可以使用 OPENSSL 库来获取签名和验签，DEMO也是基于 OPENSSL 实现

## 快速开始

| 文件 | 备注 |
| -- | -- |
| RSATool.hpp | 工具类依赖OPENSSL, 提供获取签名和验签的静态方法, 直接引用即可 |
| TestRSATool.cc | 签名和验签示例代码 |
| Lib	| 包含编译好的OPENSSL库相关依赖 |
